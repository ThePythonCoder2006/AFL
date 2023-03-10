#include "DAFL_add.h"
#include "DAFL.h"

daf_ret_t daf_limb_copy(daf_limb_t *rop, daf_limb_t op)
{
	for (uint8_t i = 0; i < DAF_LIMB_SIZE; ++i)
		(*rop)[i] = op[i];

	return DAF_RET_SUCESS;
}

uint8_t daf_limb_is_max(daf_limb_t op)
{
	uint8_t is_max = 1;

	for (uint8_t i = 0; i < DAF_LIMB_SIZE; ++i)
	{
		if (op[i] < TEN_9_MAX)
		{
			is_max = 0;
			break;
		}
	}

	return is_max;
}

daf_ret_t daf_ten_9_add(uint30_t *const rop, const uint30_t op1, const uint30_t op2)
{
#define DAF_ADD_GET_CARRY(op) (op >> 30)
	*rop = op1 + op2;
	if (*rop > TEN_9_MAX)
	{
		*rop -= (TEN_9_MAX + 1);
		*rop |= 1 << 30;
	}
	return DAF_RET_SUCESS;
}

daf_ret_t daf_limb_pp(daf_limb_t *rop) // adds one to the limb
{
	for (int8_t i = DAF_LIMB_SIZE; i >= 0; --i)
	{
		if ((*rop)[i] < TEN_9_MAX)
		{
			(*rop)[i]++;
			break;
		}

		if ((*rop)[i] == TEN_9_MAX)
		{
			(*rop)[i] = 0;
			continue;
		}

		// error, value is unreable
		printf("  " PRINTF_BINARY_PATTERN_INT32 "\n& " PRINTF_BINARY_PATTERN_INT32 "\n= " PRINTF_BINARY_PATTERN_INT32 "\n", PRINTF_BYTE_TO_BINARY_INT32((*rop)[i]), PRINTF_BYTE_TO_BINARY_INT32(~(1 << 31)), PRINTF_BYTE_TO_BINARY_INT32((*rop)[i] & ~(1 << 31)));
		fprintf(stderr, PRINTF_ERROR "the ten_9 at index %" PRIu8 " had a value higher than the maximum accepted value  (rop[%" PRIu8 "] = %u > %u\n", i, i, (*rop)[i], (uint32_t)TEN_9_MAX);
		return DAF_RET_ERR_INVALID_FLOAT;
	}

	return DAF_RET_SUCESS;
}

daf_ret_t daf_limb_add(uint8_t *const carry,
											 daf_limb_t *const rop,
											 const daf_limb_t op1,
											 const daf_limb_t op2_bott,
											 const daf_limb_t op2_top,
											 const uint8_t uint30_dec)
{
	// helper macros for the daf_add functions for keeping the remaiders
	// #define DAF_ADD_GET_REM_BIT(rem_var, N) (((rem_var)[(uint64_t)((N) / 8)] >> ((((N)-1) % 8))) & 1)
	// #define DAF_ADD_SET_REM_BIT(rem_var, N) (((rem_var)[(uint64_t)((N) / 8)]) |= (1 << (((N)-1) % 8)))
	// #define DAF_ADD_CLR_REM_BIT(rem_var, N) (((rem_var)[(uint64_t)((N) / 8)]) &= ~(1 << (((N)-1) % 8)))

	// using an array as bitfield to store all of the carrys of the sums
	uint8_t arrcarry1_[DAF_LIMB_SIZE] = {0},
					arrcarry2_[DAF_LIMB_SIZE] = {0};

	uint8_t *arrcarry1 = arrcarry1_,
					*arrcarry2 = arrcarry2_;

	const uint8_t max_ten_9_start = DAF_LIMB_SIZE - 1;

	// summing each pair of uint30_t individually
	for (size_t i = 0; i < DAF_LIMB_SIZE; ++i)
	{

		if (i < uint30_dec)
		{
			(*rop)[i] = op1[i] + op2_bott[DAF_LIMB_SIZE - uint30_dec + i];
		}
		else
		{
			(*rop)[i] = op1[i] + op2_top[i - uint30_dec];
		}

		if ((*rop)[i] > TEN_9_MAX)
		{
			(*rop)[i] -= TEN_9_MAX + 1;
			if (i > 0)
				arrcarry1[i - 1] = 1;
			else
				*carry = 1;
		}
	}

	uint8_t run = 1;
	while (run)
	{
		// the (i + 1) are because the i's start from 0 and not from 1
		for (size_t i = 0; i < (DAF_LIMB_SIZE); ++i)
		{
			if (arrcarry1[i])
			{
				// if there will not be an owerflow then apply the carry
				if ((*rop)[i] < TEN_9_MAX)
					++(*rop)[i];
				else // else set the carry for the next value and reset the uint64_t to 0
				{
					(*rop)[i] = 0;
					if (i > 0)
						arrcarry2[i - 1] = 1;
					else
						*carry = 1;
				}

				arrcarry1[i] = 0;
			}
		}

		// suppose that there is no more carry
		run = 0;

		// reset the carry array n°1 that has allready been used to 0 and check if the second array contains any non zero value
		for (uint8_t i = 0; i < DAF_LIMB_SIZE + 1; ++i)
		{
			arrcarry1[i] = 0;
			if (arrcarry2[i])
			// if the second carry array does contain non-zero element(s) then keep running and skip the swaping of the arrays
			{
				run = 1;
				break;
			}
		}

		swap_ptr_uint8((&arrcarry1), &arrcarry2);
	}

	return DAF_RET_SUCESS;
}

// function that add two const hpcp_t passed as refs (op1_ref and op2_ref) and sets the result into an another hpcp_t ref (rop_ref)
daf_ret_t daf_add(daf_ref_t rop_ref, daf_ref_t op1_ref, daf_ref_t op2_ref)
{
	// assert(0);
	DAF_GET_PTR(rop);
	daf_t *op1, *op2;
	if (DAF_GET(op1_ref, exp) >= DAF_GET(op2_ref, exp))
	{
		op1 = all_daf[op1_ref];
		op2 = all_daf[op2_ref];
	}
	else
	{
		op2 = all_daf[op1_ref];
		op1 = all_daf[op2_ref];
	}

	rop->head = 0;

	if (DAF_IS_INT(op1_ref) && DAF_IS_INT(op2_ref))
	{
		rop->head |= DAF_HEAD_INT;

		if (DAF_IS_ZERO(op1_ref) && DAF_IS_ZERO(op2_ref))
		{
			if (DAF_IS_POS(op1_ref) && DAF_IS_POS(op2_ref))
			{
				daf_set_plus_zero(rop_ref);
				return DAF_RET_SUCESS;
			}
		}
	}

	if (DAF_IS_NaN(op1_ref) || DAF_IS_NaN(op2_ref))
	{
		daf_set_NaN(rop_ref);
		return DAF_RET_SUCESS;
	}

	if (DAF_IS_INF(op1_ref) || DAF_IS_INF(op2_ref))
	{
		if (DAF_IS_POS(op1_ref) && DAF_IS_POS(op2_ref))
		{
			daf_set_plus_inf(rop_ref);
			return DAF_RET_SUCESS;
		}
		else if (!DAF_IS_POS(op1_ref) && !DAF_IS_POS(op2_ref))
		{
			daf_set_minus_inf(rop_ref);
			return DAF_RET_SUCESS;
		}
		daf_set_plus_zero(rop_ref);
		return DAF_RET_SUCESS;
	}

	rop->exp = op1->exp > op2->exp ? op1->exp : op2->exp;

	// the number of limbs used by the return operand (rop)
	uint64_t max_limb_numb = ((rop->prec + rop->real_prec_dec)) / DAF_LIMB_SIZE;

	uint8_t arrcarry1_[DAF_LIMB_SIZE] = {0};
	uint8_t arrcarry2_[DAF_LIMB_SIZE] = {0};

	uint8_t *arrcarry1 = arrcarry1_;
	uint8_t *arrcarry2 = arrcarry2_;

	const uint64_t dec = op1->exp - op2->exp;							// the number of uint30_t that the two operands are offseted by to each other
	const uint64_t limb_dec = dec / DAF_LIMB_SIZE;				// the number of limbs that the two operands are offseted by to each other
	const uint64_t uint30_limb_dec = dec % DAF_LIMB_SIZE; // the number of uint30_t in a limbs that the two operands are offseted by to each other

	// add the limbs in pair for the start of both op's
	uint8_t carry;

	for (size_t i = 0; i < max_limb_numb; ++i)
	{
		if (i <= limb_dec) // op2->loaded_mtsa[i] doesn't exist
		{
			daf_limb_copy((*rop->loaded_mtsa)[i], (*op1->loaded_mtsa)[i]);
			continue;
		}

		if (i > DAF_GET_PREC(op1_ref) || i > DAF_GET_PREC(op2_ref) + limb_dec)
		{
		}
	}

	uint8_t run = 1;

	uint8_t limb_i_is_max = 1;

	while (run)
	{
		for (uint64_t i = 0; i < max_limb_numb; ++i)
		{
			if (arrcarry1[i] == 0)
				continue;

			if (!daf_limb_is_max((*rop->loaded_mtsa)[i]))
			{
				daf_limb_set_zero(&((*rop->loaded_mtsa)[i]));
				if (i > 0)
					arrcarry2[i - 1] = 1;
				else
					TODO;
			}
			else
				daf_limb_pp(&((*rop->loaded_mtsa)[i]));

			arrcarry1[i] = 0;
		}

		// suppose that there is no more carry
		run = 0;

		// check if the second array contains any non zero value
		for (uint8_t i = 0; i < max_limb_numb; ++i)
			if (arrcarry2[i]) // if the second carry array contains any non-zero elements, keep going
				run = 1;

		swap_ptr_uint8(&arrcarry1, &arrcarry2);
	}

	return DAF_RET_SUCESS;

	// #undef DAF_ADD_GET_REM_BIT
	// #undef DAF_ADD_SET_REM_BIT
	// #undef DAF_ADD_CLR_REM_BIT
}
