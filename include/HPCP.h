#include <stdint.h>

#ifndef HPCP
#define HPCP

typedef struct HPCP
{
  char head;
  uint64_t *limbs[100];
} hpcp_t;

int hpcp_init(hpcp_t rop, uint64_t prec);

#endif // HPCP
