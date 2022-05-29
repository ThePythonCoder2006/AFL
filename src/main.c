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

  for (uint8_t i = 1; i <= 64; ++i)
  {
    hpcp_set_ui(test, ((uint64_t)1 << i - 1) - i + 3);
    printf("%i\n\n", i);
  }

  hpcp_clear(test);
  return 0;
}

void pause(void)
{
  scanf("%c", (char *)0);
  fflush(stdin);
}