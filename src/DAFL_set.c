#include "DAFL_set.h"

daf_ret_t daf_set_mtsa_zero(daf_ref_t rop_ref)
{
	DAF_GET_PTR(rop);

	for (uint64_t i = 0; i < DAF_GET_PREC(rop_ref) / DAF_LIMB_SIZE; ++i)
		memset((rop->loaded_mtsa)[i], 0, sizeof(daf_limb_t));

	return DAF_RET_SUCESS;
}

daf_ret_t daf_limb_set_zero(daf_limb_t *rop)
{
	memset(rop, 0, sizeof(*rop));
	return DAF_RET_SUCESS;
}

daf_ret_t daf_set_plus_zero(daf_ref_t op_ref)
{
	DAF_GET_PTR(op);

	op->head = DAF_HEAD_ZERO | DAF_HEAD_INT;
	op->exp = 0;

	return daf_set_mtsa_zero(op_ref);
}

daf_ret_t daf_set_minus_zero(daf_ref_t op_ref)
{
	DAF_GET_PTR(op);

	op->head = DAF_HEAD_ZERO | DAF_HEAD_INT | DAF_HEAD_MINUS;
	op->exp = 0;

	return daf_set_mtsa_zero(op_ref);
}

daf_ret_t daf_set_NaN(daf_ref_t op_ref)
{
	DAF_GET_PTR(op);

	op->head = DAF_HEAD_NaN;
	op->exp = 0;

	return daf_set_mtsa_zero(op_ref);
}

daf_ret_t daf_set_plus_inf(daf_ref_t op_ref)
{
	DAF_GET_PTR(op);

	op->head = DAF_HEAD_INF;
	op->exp = UINT64_MAX;

	return daf_set_mtsa_zero(op_ref);
}

daf_ret_t daf_set_minus_inf(daf_ref_t op_ref)
{
	DAF_GET_PTR(op);

	op->head = DAF_HEAD_INF | DAF_HEAD_MINUS;
	op->exp = UINT64_MAX;

	return daf_set_mtsa_zero(op_ref);
}

daf_ret_t daf_set_ui(daf_ref_t rop_ref, uint64_t op)
{
	if (op == 0)
	{
		daf_set_plus_zero(rop_ref);
		return DAF_RET_SUCESS;
	}

	uint30_t p1, p2, p3;
	uint64_t tmp;

	p1 = op % (TEN_9_MAX + 1);
	tmp = (op - p1);
	p2 = ((tmp / (TEN_9_MAX + 1))) % (TEN_9_MAX + 1);
	p3 = (((tmp / (TEN_9_MAX + 1)) - p2) / (TEN_9_MAX + 1)) % (TEN_9_MAX + 1);

	DAF_GET_PTR(rop);
	rop->head = DAF_HEAD_INT;

	daf_set_mtsa_zero(rop_ref);

	if (p3 == 0)
	{
		if (p2 == 0)
		{
			rop->exp = 0;
			DAF_MTSA_NTH(rop_ref, 0) = p1;
			return DAF_RET_SUCESS;
		}
		rop->exp = 1;
		DAF_MTSA_NTH(rop_ref, 1) = p1;
		DAF_MTSA_NTH(rop_ref, 0) = p2;
		return DAF_RET_SUCESS;
	}

	rop->exp = 2;
	DAF_MTSA_NTH(rop_ref, 2) = p1;
	DAF_MTSA_NTH(rop_ref, 1) = p2;
	DAF_MTSA_NTH(rop_ref, 0) = p3;

	return DAF_RET_SUCESS;
}