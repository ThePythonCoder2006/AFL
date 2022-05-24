#include <stdio.h>
#include <stdlib.h>
#include "HPCP.h"

void pause(void);

#define PREC 200

int main(int argc, char **argv)
{
  printf("hpcp_t: %i\nhpcp_limb_t: %i\nuint64_t: %i\n", sizeof(hpcp_t), sizeof(hpcp_limb_t), sizeof(uint64_t));
  hpcp_t test;
  hpcp_init(&test, PREC);
  printf("%x\n", *(*(test.start) + (sizeof(hpcp_limb_t) * 2)));
  printf("ok boomer\n");
  pause();
  return 0;
}

void pause(void)
{
  scanf("%c", (char *)0);
  fflush(stdin);
}