#include <stdlib.h>
#include <stdio.h>

#include <DAFL.h>

int main(int argc, char **argv)
{
  (void)argc;
  (void)argv;

  int num = MYRIAGIT_MAX + 1;

  printf("hello DAFL !!!, %i, %i, %i\n", num, TRC(num, 0), TRC_PRT(num, 0));

  printf("%" PRIu32 ", %" PRIu32 ", %" PRIu32 "\n", MYRIAGIT_DEC, (0 * MYRIAGIT_DEC), (MYRIAGIT_MAX - (0U * MYRIAGIT_DEC)));

  return 0;
}