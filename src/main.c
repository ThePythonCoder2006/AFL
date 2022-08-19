#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#include <DAFL.h>

int main(int argc, char **argv)
{
  (void)argc;
  (void)argv;

  uin64_t num = (ten_9_MAX - 30);

  printf("hello DAFL !!!, %" PRIu64 ", %" PRIu64 ", %" PRIu64 "\n", num, (TRC(num, 0)), (TRC_PRT(num, 0)));

  return 0;
}