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

#define PREC 200

void pause(void);

int main(int argc, char **argv)
{
  // header so I can see the start of my program
  printf(PRINTF_YELLOW "|-----------------------------------------------------------------|\n|                     START OF MAIN.C                             |\n|-----------------------------------------------------------------|\n\n" PRINTF_RESET);

  printf("hpcp_t: %i\nhpcp_limb_t: %i\nuint64_t: %i\n", sizeof(hpcp_t), sizeof(hpcp_limb_t), sizeof(uint64_t));
  hpcp_ref_t test = hpcp_init(PREC);

  printf("%" PRIu64 "\n", test);

  hpcp_set_ui(test, UINT64_MAX);

  printf("printf_bin(test) : ");
  hpcp_printf_bin_sci(test);

  // hpcp_limb_t rop, op1, op2 = {1};

  // for (size_t i = 0; i < HPCP_LIMB_SIZE; ++i)
  //   op1[i] = UINT64_MAX;

  // hpcp_add_limb(&rop, op1, op2);

  // uint64_t rop, op1 = UINT64_MAX, op2 = UINT64_MAX;

  // uint8_t rem = hpcp_add_uint64(&rop, op1, op2);

  // printf("%i, %" PRIu64 ", 0000000%i " PRINTF_BINARY_PATTERN_INT64 "\n", rem, rop, rem, PRINTF_BYTE_TO_BINARY_INT64(rop));

  hpcp_add(test, test, test);

  printf("\nprintf_bin(test) : ");
  hpcp_printf_bin_sci(test);

  pause();

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