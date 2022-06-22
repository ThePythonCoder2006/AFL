
#include <stdio.h>
#include <stdint.h>

#ifndef __HPCP
#define __HPCP

/* --- PRINTF_BYTE_TO_BINARY macro's --- */
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
/* --- end printf binary macros --- */

#define PRINTF_BLACK "\033[0;30m"
#define PRINTF_RED "\033[0;31m"
#define PRINTF_GREEN "\033[0;32m"
#define PRINTF_YELLOW "\033[0;33m"
#define PRINTF_BLUE "\033[0;34m"
#define PRINTF_PURPLE "\033[0;35m"
#define PRINTF_CYAN "\033[0;36m"
#define PRINTF_WHITE "\033[0;37m"
#define PRINTF_RESET "\033[0m"

#define OPEN_FILE_OR_PANIC(path, mode, var)                                   \
  if (((var) = fopen((path), (mode))) == NULL)                                \
  {                                                                           \
    printf(PRINTF_RED "[ERROR] could not open file %s" PRINTF_RESET, (path)); \
    return HPCP_ERR_RET_READ_FILE;                                            \
  }

#define HPCP_LIMB_SIZE 10

#define HPCP_MINUS 0x01     // 0b00000001
#define HPCP_ZERO 0x02      // 0b00000010
#define HPCP_INF 0x04       // 0b00000100
#define HPCP_NAN 0x08       // 0b00001000
#define HPCP_EXP_MINUS 0x10 // 0b00010000
#define HPCP_INT 0x20       // 0b00100000

#define HPCP_ERR_RET_READ_FILE -1
#define HPCP_ERR_RET_ALLOC -2

#define HPCP_IS_ZERO(op) ((op)->head | HPCP_ZERO) == (op)->head
#define HPCP_IS_NAN(op) ((op)->head | HPCP_NAN) == (op)->head
#define HPCP_IS_INF(op) ((op)->head | HPCP_INF) == (op)->head

#define SET_BIT(n, N) ((n) |= ((uint64_t)1 << (N)))
#define CLR_BIT(n, N) ((n) &= ~((uint64_t)(1ll << (N))))
#define TOGGLE_BIT(n, N) ((n) ^= ((uint64_t)1 << (N)))
#define NTH_BIT(n, N) (((n) >> (N)) & (uint64_t)1)

#define PRINT_LIMB                                                                 \
  for (size_t i = 0; i < HPCP_LIMB_SIZE; ++i)                                      \
  {                                                                                \
    printf(PRINTF_BINARY_PATTERN_INT64, PRINTF_BYTE_TO_BINARY_INT64(limb_tmp[i])); \
  }                                                                                \
  printf(PRINTF_BLUE "| \n" PRINTF_RESET);

typedef uint64_t hpcp_limb_t[HPCP_LIMB_SIZE];
typedef uint8_t hpcp_head_t;

typedef struct HPCP_T
{
  hpcp_head_t head;
  uint64_t prec;
  uint8_t real_prec_dec;
  uint64_t exp;
  uint64_t line;
  hpcp_limb_t *start;
  hpcp_limb_t **tmp_store;
} hpcp_t;

int hpcp_init(hpcp_t **rop, const uint64_t prec);
int hpcp_limb_set_ui(hpcp_limb_t rop, const uint64_t op);
int hpcp_set_ui(hpcp_t *rop, const uint64_t op);
size_t hpcp_printf(const char *const format, ...);
int hpcp_printf_bin(const hpcp_t *const op);
int hpcp_copy(hpcp_t *dst, const hpcp_t *const src);
size_t hpcp_get_filename(char filename[64], const hpcp_t *const op);
uint8_t hpcp_add_uint64(uint64_t *rop, const uint64_t op1, const uint64_t op2);
int8_t hpcp_add_limb(hpcp_limb_t *rop, const hpcp_limb_t op1, const hpcp_limb_t op2);
int hpcp_add(hpcp_t *rop, const hpcp_t *const op1, const hpcp_t *const op2);

int hpcp_negate(hpcp_t *rop, const hpcp_t *const op);
void hpcp_clear(hpcp_t *rop);

void swap_ptr_uint8(uint8_t **const a, uint8_t **const b);

void rek_mkdir(const char *const path);
FILE *fopen_mkdir(const char *const path, const char *const mode);
void rm_dir(const char *const path);

#endif // __HPCP