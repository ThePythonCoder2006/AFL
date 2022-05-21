#include <stdint.h>

#ifndef HPCP
#define HPCP

typedef struct HPCP
{
  char head;
  uint64_t limbs[];
} hpcp_t;

int hpcp_init(hpcp_t rop, uint64_t prec);

void rek_mkdir(char *path);
FILE *fopen_mkdir(char *path, char *mode);
int remove_recursive(const char *const path)

#endif // HPCP