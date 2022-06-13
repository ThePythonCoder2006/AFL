#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include "HPCP.h"

/*
colors:
Black  \033[0;30m
Red    \033[0;31m
Green  \033[0;32m
Yellow \033[0;33m
Blue   \033[0;34m
Purple \033[0;35m
Cyan   \033[0;36m
White  \033[0;37m
reset  \033[0m
*/

void pause(void);
void yellow(void);
void reset(void);

#define PREC 20

int main(int argc, char **argv)
{
  // header so I can see the start of my program
  yellow();
  printf("|-----------------------------------------------------------------|\n|                     START OF MAIN.C                             |\n|-----------------------------------------------------------------|\n\n");
  reset();

  printf("hpcp_t: %i\nhpcp_limb_t: %i\nuint64_t: %i\n", sizeof(hpcp_t), sizeof(hpcp_limb_t), sizeof(uint64_t));
  hpcp_t *test;
  if (hpcp_init(&test, PREC) == -1)
    fprintf(stderr, "error while initing test\n");

  printf("%" PRIu64 "\n", (uint64_t)test->real_prec_dec);

  hpcp_set_ui(test, UINT8_MAX);

  // printf("printf_bin(test) : ");
  // hpcp_printf_bin(test);

  // printf("\nprintf_bin(test) : ");
  // hpcp_printf_bin(test);

  pause();

  hpcp_limb_t rop = {0}, op1 = {UINT64_MAX, UINT64_MAX}, op2 = {UINT64_MAX, UINT64_MAX};

  uint8_t *rem = hpcp_add_limb(&rop, op1, op2);

  free(rem);

  hpcp_clear(test);

  (void)argc;
  (void)argv;
  return 0;
}

void pause(void)
{
  char tmp;
  scanf("%c", &tmp);
  fflush(stdin);
}

void yellow(void)
{
  printf("\033[0;33m");
}

void reset(void)
{
  printf("\033[0m");
}