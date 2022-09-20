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
#include <float.h>

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

#define TMPPATH "./bin/tmp"

#define DAF_LIMB_SIZE (50)

#define UINT64_TO_UINT30_MASK UINT30_MAX

/*-------------------------------end constants-------------------------------*/
/*-------------------------------start inline functions-------------------------------*/

#define DIV_CEIL(p, q) ((p) / (q) + ((p) % (q) != 0))

#define DAF_IS_ZERO(ref) (((all_daf[ref])->head | (DAF_HEAD_ZERO)) == (all_daf[ref])->head)
#define DAF_IS_NaN(ref) (((all_daf[ref])->head | (DAF_HEAD_NaN)) == (all_daf[ref])->head)
#define DAF_IS_INF(ref) (((all_daf[ref])->head | (DAF_HEAD_INF)) == (all_daf[ref])->head)
#define DAF_IS_INT(ref) (((all_daf[ref])->head | (DAF_HEAD_INT)) == (all_daf[ref])->head)
#define DAF_IS_POS(ref) (((all_daf[ref])->head | (DAF_HEAD_MINUS)) != (all_daf[ref])->head)

#define DAF_GET_PTR(op) daf_t *op = all_daf[op##_ref]

#define DAF_GET(ref, key) (all_daf[(ref)]->key)

#define DAF_MTSA_LIMB_AT_NTH_UINT30(ref, n) ((*(all_daf[ref])).loaded_mtsa[(n - (n % DAF_LIMB_SIZE)) / DAF_LIMB_SIZE])
#define DAF_MTSA_NTH(ref, n) ((*DAF_MTSA_LIMB_AT_NTH_UINT30(ref, n))[n % DAF_LIMB_SIZE])

#define SMOD_2x(op, m) (op - (op > m) * (m))
#define SMOD_4x(op, m) SMOD_2x(SMOD_2x(op, 2 * m), m)
#define SMOD_8x(op, m) SMOD_4x(SMOD_4x(op, 4 * m), m)

#define OPEN_FILE_OR_PANIC(path, mode, var)                          \
  if (((var) = fopen((path), (mode))) == NULL)                       \
  {                                                                  \
    fprintf(stderr, PRINTF_ERROR " could not open file %s", (path)); \
    return DAF_RET_ERR_READ_FILE;                                    \
  }

#define PPCAT_NX(A, B) A##B
#define PPCAT(A, B) PPCAT_NX(A, B)

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

#define PRINTF_NaN "NaN"
#define PRITNF_NaN_len sizeof(PRINTF_NaN)

#define PRINTF_INF "Inf"
#define PRITNF_INF_len sizeof(PRINTF_INF)

#define PRINTF_0 "0"
#define PRITNF_0_len sizeof(PRINTF_0)

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
daf_ret_t daf_primitive_out_file_string(FILE *stream, char *buff, const uint64_t n, daf_ref_t op_ref, uint64_t prec);
daf_ret_t daf_primitive_vnprint(FILE *stream, char *const buff, const uint64_t n, const char *fmt, va_list args);

static inline daf_ret_t daf_vfprintf(FILE *stream, const char *fmt, va_list args) { return daf_primitive_vnprint(stream, NULL, UINT64_MAX, fmt, args); }
static inline daf_ret_t daf_vprintf(const char *fmt, va_list args) { return daf_vfprintf(stdout, fmt, args); }
static inline daf_ret_t daf_fprintf(FILE *stream, const char *fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  return daf_vfprintf(stream, fmt, args);
}
static inline daf_ret_t daf_eprintf(const char *fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  return daf_vfprintf(stderr, fmt, args);
}
static inline daf_ret_t daf_printf(const char *fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  return daf_vprintf(fmt, args);
}

static inline daf_ret_t daf_vsnprintf(char *buff, const uint64_t n, const char *fmt, va_list args) { return daf_primitive_vnprint(NULL, buff, n, fmt, args); }
static inline daf_ret_t daf_vsprintf(char *buff, const char *fmt, va_list args) { return daf_vsnprintf(buff, UINT64_MAX, fmt, args); };
static inline daf_ret_t daf_snprintf(char *buff, const uint64_t n, const char *fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  return daf_vsnprintf(buff, n, fmt, args);
};
static inline daf_ret_t daf_sprintf(char *buff, const char *fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  return daf_vsnprintf(buff, UINT64_MAX, fmt, args);
};

size_t daf_get_filename(char filename[64], daf_ref_t op_ref);

daf_ret_t daf_debug_out(daf_ref_t op_ref, const char *const name);

// set functions ------------------------------------------------------
daf_ret_t daf_set_plus_zero(daf_ref_t op_ref);
daf_ret_t daf_set_minus_zero(daf_ref_t op_ref);
daf_ret_t daf_set_NaN(daf_ref_t op_ref);
daf_ret_t daf_set_plus_inf(daf_ref_t op_ref);
daf_ret_t daf_set_minus_inf(daf_ref_t op_ref);

daf_ret_t daf_set_ui(daf_ref_t rop_ref, uint64_t op);

// arthimetric functions ------------------------------------------------------
daf_ret_t daf_negate(daf_ref_t rop_ref, daf_ref_t op_ref);

daf_ret_t daf_ten_9_add(uint30_t *rop, uint30_t op1, uint30_t op2);
daf_ret_t daf_limb_add(uint8_t *const carry, daf_limb_t *const rop, const daf_limb_t op1_top, const daf_limb_t op1_bott, const daf_limb_t op2, const uint8_t uint30_dec);
daf_ret_t daf_limb_pp(daf_limb_t *rop); // adds one to the limb
daf_ret_t daf_add(daf_ref_t rop_ref, daf_ref_t op1_ref, daf_ref_t op2_ref);

// file functions
void rek_mkdir(const char *const path);
FILE *fopen_mkdir(const char *const path, const char *const mode);

void swap_ptr_uint8(uint8_t **const a, uint8_t **const b);

/*-------------------------------end functions-------------------------------*/

#endif //__DAFL__