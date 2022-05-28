#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include "HPCP.h"

void pause(void);

#define PREC 200

int main(int argc, char **argv)
{
  printf("hpcp_t: %i\nhpcp_limb_t: %i\nuint64_t: %i\n", sizeof(hpcp_t), sizeof(hpcp_limb_t), sizeof(uint64_t));
  hpcp_t *test;
  if (hpcp_init(&test, PREC) == -1)
    fprintf(stderr, "error while initing test\n");

  printf("%" PRId64 "\n", test->prec);

  hpcp_set_ui(test, 8);

  printf("%i\n", HPCP_PLUS);
  printf("%i\n", HPCP_MINUS);
  printf("%i\n", HPCP_PLUS_ZERO);
  printf("%i\n", HPCP_MINUS_ZERO);
  printf("%i\n", HPCP_PLUS_INF);
  printf("%i\n", HPCP_PLUS_INF);

  hpcp_clear(test);
  return 0;
}

void pause(void)
{
  scanf("%c", (char *)0);
  fflush(stdin);
}