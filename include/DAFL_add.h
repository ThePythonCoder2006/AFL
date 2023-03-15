#pragma once
#ifndef __DAFL_ADD__
#define __DAFL_ADD__

#include "DAFL.h"

daf_ret_t daf_ten_9_add(uint30_t *rop, uint30_t op1, uint30_t op2);
daf_ret_t daf_limb_add_full(uint8_t *const carry, daf_limb_t *const rop, const daf_limb_t op1, const daf_limb_t op2_bott, const daf_limb_t op2_top, const uint8_t uint30_dec, const uint8_t is_bott);
static inline daf_ret_t daf_limb_add(uint8_t *const carry, daf_limb_t *const rop, const daf_limb_t op1, const daf_limb_t op2_bott, const daf_limb_t op2_top, const uint8_t uint30_dec) { return daf_limb_add_full(carry, rop, op1, op2_bott, op2_top, uint30_dec, 1); }
daf_ret_t daf_limb_pp(daf_limb_t *rop); // adds one to the limb
daf_ret_t daf_add_restrict(daf_ref_t rop_ref, daf_ref_t op1_ref, daf_ref_t op2_ref);
daf_ret_t daf_add(daf_ref_t rop_ref, daf_ref_t op1_ref, daf_ref_t op2_ref);

#endif // __DAFL_ADD__