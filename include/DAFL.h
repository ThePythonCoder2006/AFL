#ifndef __DAFL__
#define __DAFL__

#include <stdint.h>
#include <inttypes.h>
#include <math.h>

#include "../../../C/useful_macros.h"

#define DAF_RET_SUCESS (0)
#define DAF_RET_ERR_ALLOC (-1)
#define DAF_RET_ERR_READ_FILE (-2)
#define DAF_RET_ERR_INVALID_FLOAT (-3)

#define DAF_HEAD_MINUS (0x01)     // 0b00000001
#define DAF_HEAD_ZERO (0x02)      // 0b00000010
#define DAF_HEAD_INF (0x04)       // 0b00000100
#define DAF_HEAD_NaN (0x08)       // 0b00001000
#define DAF_HEAD_EXP_MINUS (0x10) // 0b00010000
#define DAF_HEAD_INT (0x20)       // 0b00100000

#define TEN_9_BITS_SIZE (30)
#define TEN_9_DECIMAL_SIZE (9)
#define UINT30_MAX (1023ULL * 1023ULL * 1023ULL)
#define TEN_9_MAX (999999999ULL)
#define TEN_9_DEC (UINT10_MAX - TEN_9_MAX)

#define DIV_CEIL(p, q) ((p) / (q) + ((p) % (q) != 0))

#define DAF_LIMB_SIZE 50

#define DAF_IS_ZERO(op) (((op)->head | DAF_ZERO) == (op)->head)
#define DAF_IS_NAN(op) (((op)->head | DAF_NAN) == (op)->head)
#define DAF_IS_INF(op) (((op)->head | DAF_INF) == (op)->head)

typedef uint64_t daf_ret_ref_t;
typedef const daf_ret_ref_t daf_ref_t;

typedef uint32_t ten_9_t;
typedef uint8_t daf_head_t;
typedef uint8_t daf_limb_t[DAF_LIMB_SIZE];

typedef uint8_t daf_ret_t;

/* a decimal floating point number of the form : ((10^9)^exp) * mantissa */
typedef struct daf
{
  daf_head_t head;              // the "head" of the number, it contains metadata of the number (ex: the sign, the sign of the exponent or denormalized values like zero, infinity or NaN)
  uint64_t exp;                 // the exponent of the float
  uint64_t prec;                // the number of myriagit asked
  uint8_t real_prec_dec;        // the number of myriagit actually used (an offset to the prec)
  daf_limb_t *start;            // the first limb of the mantissa (to be used to start calculations before the rest would be loaded)
  daf_limb_t **loaded_mantissa; // the mantissa of the float if it had already load before for calculations
} daf_t;

daf_ref_t daf_init(uint64_t prec);

#endif //__DAFL__