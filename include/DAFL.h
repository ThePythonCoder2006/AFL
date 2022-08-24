#ifndef __DAFL__
#define __DAFL__

#include <stdint.h>
#include <inttypes.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>

#include "../../../C/useful_macros.h"

#ifdef _WIN32
#include <io.h>
#define F_OK 0
#define access _access
#endif

/*-------------------------------start constants-------------------------------*/

#define DAF_HEAD_MINUS (0x01)     // 0b00000001
#define DAF_HEAD_ZERO (0x02)      // 0b00000010
#define DAF_HEAD_INF (0x04)       // 0b00000100
#define DAF_HEAD_NaN (0x08)       // 0b00001000
#define DAF_HEAD_EXP_MINUS (0x10) // 0b00010000
#define DAF_HEAD_INT (0x20)       // 0b00100000

#define FLOAT_UNIT_BIN_SIZE (30)
#define FLOAT_UNIT_DECIMAL_SIZE (9)
#define TEN_9_BIN_SIZE (FLOAT_UNIT_BIT_SIZE)
#define TEN_9_DECIMAL_SIZE (FLOAT_UNIT_DECIMAL_SIZE)
#define DAF_LIMB_DECIMAL_SIZE (DAF_LIMB_SIZE * TEN_9_DECIMAL_SIZE)
#define DAF_LIMB_BIN_SIZE (DAF_LIMB_SIZE * sizeof(uint30_t))
#define UINT30_MAX ((1ULL << 30) - 1)
#define TEN_9_MAX (999999999ULL)
#define TEN_9_DEC ((UINT30_MAX) - (TEN_9_MAX))

#define TMPPATH "./tmp"

#define DAF_LIMB_SIZE (50)

#define UINT64_TO_UINT30_MASK UINT30_MAX

/*-------------------------------end constants-------------------------------*/
/*-------------------------------start inline functions-------------------------------*/

#define DIV_CEIL(p, q) ((p) / (q) + ((p) % (q) != 0))

#define DAF_IS_ZERO(ref) (((all_daf[ref])->head | (DAF_HEAD_ZERO)) == (all_daf[ref])->head)
#define DAF_IS_NaN(ref) (((all_daf[ref])->head | (DAF_HEAD_NaN)) == (all_daf[ref])->head)
#define DAF_IS_INF(ref) (((all_daf[ref])->head | (DAF_HEAD_INF)) == (all_daf[ref])->head)
#define DAF_IS_INT(ref) (((all_daf[ref])->head | (DAF_HEAD_INT)) == (all_daf[ref])->head)

#define DAF_GET_PTR(op) daf_t *op = all_daf[op##_ref]

#define DAF_GET(ref, key) (all_daf[(ref)]->key)

#define DAF_MTSA_LIMB_AT_NTH_UINT30(ref, n) ((*(all_daf[ref])).loaded_mtsa[(n - (n % DAF_LIMB_SIZE)) / DAF_LIMB_SIZE])
#define DAF_MTSA_NTH(ref, n) ((*DAF_MTSA_LIMB_AT_NTH_UINT30(ref, n))[n % DAF_LIMB_SIZE])

/*-------------------------------end inline functions-------------------------------*/
/*-------------------------start PRINTF_BYTE_TO_BINARY--------------------------*/

#define PRINTF_BINARY_PATTERN_INT8 "%c%c%c%c%c%c%c%c "
#define PRINTF_BYTE_TO_BINARY_INT8(i) \
  (((i)&0x80ll) ? '1' : '0'),         \
      (((i)&0x40ll) ? '1' : '0'),     \
      (((i)&0x20ll) ? '1' : '0'),     \
      (((i)&0x10ll) ? '1' : '0'),     \
      (((i)&0x08ll) ? '1' : '0'),     \
      (((i)&0x04ll) ? '1' : '0'),     \
      (((i)&0x02ll) ? '1' : '0'),     \
      (((i)&0x01ll) ? '1' : '0')

#define PRINTF_BINARY_PATTERN_INT16 \
  PRINTF_BINARY_PATTERN_INT8 PRINTF_BINARY_PATTERN_INT8
#define PRINTF_BYTE_TO_BINARY_INT16(i) \
  PRINTF_BYTE_TO_BINARY_INT8((i) >> 8), PRINTF_BYTE_TO_BINARY_INT8(i)
#define PRINTF_BINARY_PATTERN_INT32 \
  PRINTF_BINARY_PATTERN_INT16 PRINTF_BINARY_PATTERN_INT16
#define PRINTF_BYTE_TO_BINARY_INT32(i) \
  PRINTF_BYTE_TO_BINARY_INT16((i) >> 16), PRINTF_BYTE_TO_BINARY_INT16(i)
#define PRINTF_BINARY_PATTERN_INT64 \
  PRINTF_BINARY_PATTERN_INT32 PRINTF_BINARY_PATTERN_INT32
#define PRINTF_BYTE_TO_BINARY_INT64(i) \
  PRINTF_BYTE_TO_BINARY_INT32((i) >> 32), PRINTF_BYTE_TO_BINARY_INT32(i)

/*-------------------------end PRINTF_BYTE_TO_BINARY--------------------------*/

/*------------------------------start-printf colors-------------------------------*/

#define PRINTF_BLACK "\033[0;30m"
#define PRINTF_RED "\033[0;31m"
#define PRINTF_GREEN "\033[0;32m"
#define PRINTF_YELLOW "\033[0;33m"
#define PRINTF_BLUE "\033[0;34m"
#define PRINTF_PURPLE "\033[0;35m"
#define PRINTF_CYAN "\033[0;36m"
#define PRINTF_WHITE "\033[0;37m"
#define PRINTF_RESET "\033[0m"

#define PRINTF_ERROR PRINTF_RED "[ERROR]" PRINTF_RESET
#define PRINTF_SUCESS PRINTF_GREEN "[SUCESS]" PRINTF_RESET
#define PRINTF_WARNING PRINTF_YELLOW "[WARNING]" PRINTF_RESET

/*-------------------------------end printf colors-------------------------------*/
/*-------------------------------start custom types-------------------------------*/

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

/* a decimal floating point number of the form : ((10^9)^exp) * mantissa */
typedef struct daf
{
  daf_head_t head;          // the "head" of the number, it contains metadata of the number (ex: the sign, the sign of the exponent or denormalized values like zero, infinity or NaN)
  uint64_t exp;             // the exponent of the float
  uint64_t prec;            // the number of myriagit asked
  uint8_t real_prec_dec;    // the number of myriagit actually used (an offset to the prec)
  daf_limb_t *start;        // the first limb of the mantissa (to be used to start calculations before the rest would be loaded)
  daf_limb_t **loaded_mtsa; // the mantissa of the float if it had already load before for calculations
} daf_t;

/*-------------------------------end custom types-------------------------------*/

extern uint64_t nb_daf;

extern uint8_t all_daf_already_init;
extern daf_t **all_daf;

extern char *(err_message)[DAF_ERR_COUNT];

/*-------------------------------start functions-------------------------------*/

daf_ret_t daf_load_mantissa(daf_ref_t ref);

// init functions
daf_ret_ref_t daf_init(uint64_t prec);

// clear functions
daf_ret_t daf_clear(daf_ref_t op_ref);

// print functions
daf_ret_t daf_out_str(daf_ref_t ref, uint64_t prec);
static inline daf_ret_t daf_all_out_str(daf_ref_t ref) { return daf_out_str(ref, 0); }
daf_ret_t daf_printf(const char *fmt, ...);

size_t daf_get_filename(char filename[64], daf_ref_t op_ref);

// set functions ------------------------------------------------------
daf_ret_t daf_set_plus_zero(daf_ref_t op_ref);
daf_ret_t daf_set_minus_zero(daf_ref_t op_ref);
daf_ret_t daf_set_NaN(daf_ref_t op_ref);
daf_ret_t daf_set_plus_inf(daf_ref_t op_ref);
daf_ret_t daf_set_minus_inf(daf_ref_t op_ref);

daf_ret_t daf_set_ui(daf_ref_t rop_ref, uint64_t op);

// arthimetric functions ------------------------------------------------------
daf_ret_t
daf_negate(daf_ref_t rop_ref, daf_ref_t op_ref);

// file functions
void rek_mkdir(const char *const path);
FILE *fopen_mkdir(const char *const path, const char *const mode);

/*-------------------------------end functions-------------------------------*/

#endif //__DAFL__