#include <stdio.h>
#include <stdlib.h>
#include "HPCP.h"

void pause(void);

int main(int argc, char **argv)
{
  printf("hpcp_t: %i\nhpcp_limb_t: %i\n", sizeof(hpcp_t), sizeof(hpcp_limb_t));
  hpcp_t test;
  hpcp_init(test, 200);
  return 0;
}

void pause(void)
{
  scanf("%c", (char *)0);
  fflush(stdin);
}