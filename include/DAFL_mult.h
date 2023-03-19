#pragma once
#ifndef __DAFL_MULT__
#define __DAFL_MULT__

#include "DAFL.h"

daf_ret_t daf_mult_pow_ten_9(daf_ref_t rop_ref, daf_ref_t op_ref, uint64_t n);
daf_ret_t daf_mult_pow_ten_9_in_place(daf_ref_t rop_ref, uint64_t n);

#endif // __DAFL_MULT__