#include "DAFL_mult.h"

daf_ret_t daf_mult_pow_ten_9(daf_ref_t rop_ref, daf_ref_t op_ref, uint64_t n)
{
	daf_copy(rop_ref, op_ref);

	daf_mult_pow_ten_9_in_place(rop_ref, n);

	return DAF_RET_SUCESS;
}

daf_ret_t daf_mult_pow_ten_9_in_place(daf_ref_t rop_ref, uint64_t n)
{
	DAF_GET_PTR(rop);
	rop->exp += n;

	return DAF_RET_SUCESS;
}