#include <stdint.h>

#ifndef HPCP
#define HPCP

#define HPCP_LIMB_SIZE 10
#define HPCP_PLUS 0x00
#define HPCP_MINUS 0x01
#define HPCP_PLUS_ZERO 0x02
#define HPCP_MINUS_ZERO 0x04
#define HPCP_PLUS_INF 0x08
#define HPCP_MINUS_INF 0x00

typedef uint64_t hpcp_limb_t[10];
typedef uint8_t hpcp_head_t;

typedef struct HPCP_T
{
  hpcp_head_t head;
  uint64_t prec;
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