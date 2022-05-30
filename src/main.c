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

  // printf("%" PRIu64 "\n", (uint64_t)test->head);

  hpcp_set_ui(test, 9);
  printf("%" PRIu64 "\n", test->exp);

  // pause();

  hpcp_clear(test);

  (void)argc;
  (void)argv;
  return 0;
}

void pause(void)
{
  scanf("%c", (char *)0);
  fflush(stdin);
}