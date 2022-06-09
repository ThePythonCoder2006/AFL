
#include <stdio.h>
#include <stdint.h>

#ifndef HPCP
#define HPCP

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
/* --- end macros --- */

#define HPCP_LIMB_SIZE 10

#define HPCP_MINUS 0x01     // 0b00000001
#define HPCP_ZERO 0x02      // 0b00000010
#define HPCP_INF 0x04       // 0b00000100
#define HPCP_NAN 0x08       // 0b00001000
#define HPCP_EXP_MINUS 0x10 // 0b00010000
#define HPCP_INT 0x20       // 0b00100000

#define HPCP_IS_ZERO (op->head | HPCP_ZERO) == op->head
#define HPCP_IS_NAN (op->head | HPCP_NAN) == op->head
#define HPCP_IS_INF (op->head | HPCP_INF) == op->head

#define SET_BIT(n, N) ((n) |= ((uint64_t)1 << (N)))
#define CLR_BIT(n, N) ((n) &= ~((uint64_t)(1ll << (N))))
#define TOGGLE_BIT(n, N) ((n) ^= ((uint64_t)1 << (N)))
#define NTH_BIT(n, N) (((n) >> (N)) & (uint64_t)1)

typedef uint64_t hpcp_limb_t[HPCP_LIMB_SIZE];
typedef uint8_t hpcp_head_t;

typedef struct HPCP_T
{
  hpcp_head_t head;
  uint64_t prec;
  uint64_t real_prec_dec;
  uint64_t exp;
  uint64_t line;
  hpcp_limb_t *start;
} hpcp_t;

int hpcp_init(hpcp_t **rop, uint64_t prec);
int hpcp_set_ui(hpcp_t *rop, uint64_t op);
size_t hpcp_printf(const char *format, ...);
int hpcp_printf_bin(hpcp_t *op);
void hpcp_clear(hpcp_t *rop);

void rek_mkdir(char *path);
FILE *fopen_mkdir(char *path, char *mode);
void rm_dir(const char *const path);

#endif // HPCP