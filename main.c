#include <stdio.h>
#include <stdlib.h>
#include "HPCP.h"

int main(int argc, char **argv)
{
  printf("%i\n", sizeof(hpcp_t));
  hpcp_t test;
  hpcp_init(test, 20);
  fopen_mkdir("tmp/tmp.bin", "w");
  char tmp;
  scanf("%c", &tmp);
  fflush(stdin);
  remove_recursive("tmp");
  return 0;
}