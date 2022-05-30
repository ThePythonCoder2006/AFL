
#include <stdio.h>
#include <stdint.h>

#ifndef HPCP
#define HPCP

#define HPCP_LIMB_SIZE 10

#define HPCP_MINUS 0x01     // 0b00000001
#define HPCP_0 0x02         // 0b00000010
#define HPCP_INF 0x04       // 0b00000100
#define HPCP_NAN 0x08       // 0b00001000
#define HPCP_EXP_MINUS 0x10 // 0b00010000

#define SET_BIT(n, N) (n |= (0x01 << (N - 1)))
#define UNSET_BIT(n, N) (n &= (0x01 << (N - 1)))
#define SWAP_BIT(n, N) (n ^= (0x01 << (N - 1)))
#define NTH_BIT(n, N) ((n >> N) & 0x01)

typedef uint64_t hpcp_limb_t[10];
typedef uint8_t hpcp_head_t;

typedef struct HPCP_T
{
  hpcp_head_t head;
  uint64_t exp;
  uint64_t line;
  hpcp_limb_t *start;
} hpcp_t;

int hpcp_init(hpcp_t **rop, uint64_t prec);
void hpcp_set_ui(hpcp_t *rop, uint64_t op);
void hpcp_clear(hpcp_t *rop);

void rek_mkdir(char *path);
FILE *fopen_mkdir(char *path, char *mode);
void rm_dir(const char *const path);

#endif // HPCP