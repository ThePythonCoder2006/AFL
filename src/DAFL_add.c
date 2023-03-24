#include "DAFL_add.h"
#include "DAFL.h"

uint8_t daf_limb_is_max(daf_limb_t op)
{
	for (uint8_t i = 0; i < DAF_LIMB_SIZE; ++i)
	{
		if (op[i] <= TEN_9_MAX)
			return 0;
	}
	return 1;
}

daf_ret_t daf_limb_copy_aligned(daf_limb_t *rop, daf_limb_t op)
{
	for (uint8_t i = 0; i < DAF_LIMB_SIZE; ++i)
		(*rop)[i] = op[i];

	return DAF_RET_SUCESS;
}

daf_ret_t daf_limb_copy_misaligned(daf_limb_t *rop, daf_limb_t op_bott, daf_limb_t op_top, uint8_t dec)
{
	for (uint8_t i = 0; i < DAF_LIMB_SIZE; ++i)
	{
		if (i < dec)
			(*rop)[i] = op_bott[DAF_LIMB_SIZE - dec + i];
		else
			(*rop)[i] = op_top[i - dec];
	}

	return DAF_RET_SUCESS;
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
	for (uint8_t i = 0; i < DAF_LIMB_SIZE; ++i)
	{
		if ((*rop)[i] < TEN_9_MAX)
		{
			(*rop)[i]++;
			break;
		}
		else if ((*rop)[i] == TEN_9_MAX)
		{
			(*rop)[i] = 0;
			continue;
		}

		// error, value is unreable
		printf("  " PRINTF_BINARY_PATTERN_INT32 "\n& " PRINTF_BINARY_PATTERN_INT32 "\n= " PRINTF_BINARY_PATTERN_INT32 "\n", PRINTF_BYTE_TO_BINARY_INT32((*rop)[i]), PRINTF_BYTE_TO_BINARY_INT32(~(1ULL << 31)), PRINTF_BYTE_TO_BINARY_INT32((*rop)[i] & ~(1ULL << 31)));
		fprintf(stderr, PRINTF_ERROR "the ten_9 at index %" PRIu8 " had a value higher than the maximum accepted value  (rop[%" PRIu8 "] = %u > %u\n", i, i, (*rop)[i], (uint32_t)TEN_9_MAX);
		return DAF_RET_ERR_INVALID_FLOAT;
	}

	return DAF_RET_SUCESS;
}

daf_ret_t daf_limb_add_full(uint8_t *const carry,
														daf_limb_t *const rop,
														const daf_limb_t op1,
														const daf_limb_t op2_bott,
														const daf_limb_t op2_top,
														const uint8_t uint30_dec,
														const uint8_t is_bott)
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

	// summing each pair of uint30_t individually
	for (uint8_t i = 0; i < DAF_LIMB_SIZE; ++i)
	{

		if (i < uint30_dec)
		{
			if (is_bott)
				(*rop)[i] = op1[i] + op2_bott[DAF_LIMB_SIZE - uint30_dec + i];
			else
				(*rop)[i] = op1[i];
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
		for (uint8_t i = 0; i < (DAF_LIMB_SIZE); ++i)
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
		for (uint8_t i = 0; i < DAF_LIMB_SIZE; ++i)
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
daf_ret_t daf_add_restrict(daf_ref_t rop_ref, daf_ref_t op1_ref, daf_ref_t op2_ref)
{
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
	const uint64_t max_limb_numb = ((rop->prec + rop->real_prec_dec)) / DAF_LIMB_SIZE;

	uint8_t *arrcarry1 = calloc(max_limb_numb, 1);
	uint8_t *arrcarry2 = calloc(max_limb_numb, 1);

	const uint64_t dec = op1->exp - op2->exp;							// the number of uint30_t that the two operands are offseted by to each other
	const uint64_t limb_dec = dec / DAF_LIMB_SIZE;				// the number of limbs that the two operands are offseted by to each other
	const uint64_t uint30_limb_dec = dec % DAF_LIMB_SIZE; // the number of uint30_t in a limbs that the two operands are offseted by to each other

	// add the limbs in pair for the start of both op's
	uint8_t carry = 0;

	for (uint64_t i = 0; i < max_limb_numb; ++i)
	{
		carry = 0; // reset carry;

		if (i < limb_dec) // op2->loaded_mtsa[i] doesn't exist
		{
			daf_limb_copy_aligned((rop->loaded_mtsa)[i], *(op1->loaded_mtsa)[i]);
			continue;
		}

		if (i > DAF_GET_PREC(op1_ref) || i > DAF_GET_PREC(op2_ref) + limb_dec)
		{
			if (i > DAF_GET_PREC(op1_ref)) // op1->loaded_mtsa[i] doesn't exist
				daf_limb_copy_misaligned((rop->loaded_mtsa)[i],
																 *(op2->loaded_mtsa)[i - limb_dec],
																 *(op2->loaded_mtsa)[i],
																 uint30_limb_dec);
			else // op2->loaded_mtsa[i] doesn't exist
				daf_limb_copy_aligned((rop->loaded_mtsa)[i], *(op1->loaded_mtsa)[i]);
			continue;
		}

		if (i == limb_dec)
			daf_limb_add_full(&carry,
												(rop->loaded_mtsa)[i],
												*(op1->loaded_mtsa)[i],
												(daf_limb_t){0},
												*(op2->loaded_mtsa)[0],
												uint30_limb_dec, 0);
		else
			daf_limb_add(&carry,
									 (rop->loaded_mtsa)[i],
									 *(op1->loaded_mtsa)[i],
									 *(op2->loaded_mtsa)[i - limb_dec - 1],
									 *(op2->loaded_mtsa)[i - limb_dec],
									 uint30_limb_dec);
		if (!carry) // if there is no carry, add the next limb
			continue;

		if (i > 0)
			arrcarry1[i - 1] = carry;
		else
		{
			daf_ror(rop_ref, rop_ref);
			(*(rop->loaded_mtsa)[i])[0] = 1;
			++rop->exp;
		}
	}

	uint8_t run = 1;

	while (run)
	{
		for (uint64_t i = 0; i < max_limb_numb; ++i)
		{
			if (arrcarry1[i])
			{
				if (!daf_limb_is_max(*(rop->loaded_mtsa)[i]))
				{
					daf_limb_set_zero(&(*(rop->loaded_mtsa)[i]));
					if (i != max_limb_numb - 1)
						arrcarry2[i - 1] = 1;
					else
						TODO;
				}
				else
					++(*(rop->loaded_mtsa)[i][DAF_LIMB_SIZE - 1]);

				arrcarry1[i] = 0;
			}
		}

		// suppose that there is no more carry
		run = 0;

		// reset the carry array n°1 that has allready been used to 0 and check if the second array contains any non zero value
		for (uint8_t i = 0; i < max_limb_numb + 1; ++i)
		{
			arrcarry1[i] = 0;
			if (arrcarry2[i]) // if the second carry array does contain non-zero element(s) then keep running and skip the swaping of the arrays
			{
				run = 1;
				continue;
			}
		}
		swap_ptr_uint8(&arrcarry1, &arrcarry2);
	}

	return DAF_RET_SUCESS;

	// #undef DAF_ADD_GET_REM_BIT
	// #undef DAF_ADD_SET_REM_BIT
	// #undef DAF_ADD_CLR_REM_BIT
}

daf_ret_t daf_add(daf_ref_t rop_ref, daf_ref_t op1_ref, daf_ref_t op2_ref) { SAFE_CALL(daf_add, rop_ref, op1_ref, op2_ref); }
