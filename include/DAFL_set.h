#ifndef __DAFL_SET__
#define __DAFL_SET__

#include "DAFL.h"

daf_ret_t daf_limb_set_zero(daf_limb_t *rop);
daf_ret_t daf_set_mtsa_zero(daf_ref_t rop_ref);

daf_ret_t daf_set_plus_zero(daf_ref_t op_ref);
daf_ret_t daf_set_minus_zero(daf_ref_t op_ref);
daf_ret_t daf_set_NaN(daf_ref_t op_ref);
daf_ret_t daf_set_plus_inf(daf_ref_t op_ref);
daf_ret_t daf_set_minus_inf(daf_ref_t op_ref);

daf_ret_t daf_set_ui(daf_ref_t rop_ref, uint64_t op);

#endif // __DAFL_SET__