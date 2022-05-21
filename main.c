#include <stdio.h>
#include "HPCP.h"

int main(int argc, char **argv)
{
  printf("%i\n", sizeof(hpcp_t));
  hpcp_t test;
  hpcp_init(test, 20);
  FILE *f = fopen_mkdir("tmp/tmp.bin", "w");
  fclose(f);
  return 0;
}