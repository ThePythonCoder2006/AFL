#ifndef __DAFL_TYPES__
#define __DAFL_TYPES__

#include "DAFL.h"

typedef uint64_t daf_ret_ref_t;
typedef const daf_ret_ref_t daf_ref_t;

typedef uint32_t uint30_t;
typedef uint8_t daf_head_t;
typedef uint30_t daf_limb_t[(DAF_LIMB_SIZE)];

typedef enum daf_ret_t
{
	DAF_RET_SUCESS,
	DAF_RET_ERR_ALLOC,
	DAF_RET_ERR_READ_FILE,
	DAF_RET_ERR_INVALID_FLOAT,
	DAF_RET_ERR_NOT_IMPLEMENTED,
	DAF_ERR_COUNT
} daf_ret_t;

typedef enum daf_head_commponants_exp
{
	DAF_HEAD_EXP_MINUS_COMP,
	DAF_HEAD_EXP_ZERO_COMP,
	DAF_HEAD_EXP_INF_COMP,
	DAF_HEAD_EXP_NaN_COMP,
	DAF_HEAD_EXP_EXP_MINUS_COMP,
	DAF_HEAD_EXP_INT_COMP
} daf_head_commponants_exp;

/* a decimal floating point number of the form : ((10^9)^exp) * mantissa */
typedef struct daf
{
	daf_head_t head;					// the "head" of the number, it contains metadata of the number (ex: the sign, the sign of the exponent or denormalized values like zero, infinity or NaN)
	uint64_t exp;							// the exponent of the float
	uint64_t prec;						// the number of myriagit asked
	uint8_t real_prec_dec;		// the number of myriagit actually used (an offset to the prec)
	daf_limb_t **loaded_mtsa; // the mantissa of the float if it had already load before for calculations
} daf_t;

#endif //__DAFL_TYPES__