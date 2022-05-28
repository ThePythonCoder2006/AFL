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

  printf("%" PRId64 "\n", test->head);

  hpcp_set_ui(test, 8);

  hpcp_clear(test);
  return 0;
}

void pause(void)
{
  scanf("%c", (char *)0);
  fflush(stdin);
}