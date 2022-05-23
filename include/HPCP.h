#include <stdint.h>

#ifndef HPCP
#define HPCP

#define HPCP_LIMB_SIZE 10

typedef uint64_t hpcp_limb_t[10];

typedef struct HPCP_T
{
  uint64_t line;
  hpcp_limb_t *start;
} hpcp_t;

int hpcp_init(hpcp_t *rop, uint64_t prec);

void rek_mkdir(char *path);
FILE *fopen_mkdir(char *path, char *mode);
void rm_dir(const char *const path);

#endif // HPCP