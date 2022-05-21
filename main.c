#include <stdio.h>
#include <stdlib.h>
#include "HPCP.h"

int main(int argc, char **argv)
{
  printf("%i\n", sizeof(hpcp_t));
  hpcp_t test;
  hpcp_init(test, 20);
<<<<<<< HEAD
  fopen_mkdir("tmp/tmp.bin", "w");
  char tmp;
  scanf("%c", &tmp);
  fflush(stdin);
  remove_recursive("tmp");
=======
  FILE *f = fopen_mkdir("tmp/tmp.bin", "w");
  fclose(f);
>>>>>>> 03d6b43408a939942c5844ee2bf46d00bd602acb
  return 0;
}