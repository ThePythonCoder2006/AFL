#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#include "DAFL.h"

#define PREC 51

int main(int argc, char **argv)
{
  // remove the first element of the call (the name of the program)
  --argc, argv++;

  daf_ref_t op1 = daf_init(PREC), op2 = daf_init(PREC), rop = daf_init(PREC);
  daf_set_ui(op2, 1);

  daf_set_ui(op1, TEN_9_MAX + 2);

  for (uint64_t i = 0; i < 3; ++i)
  {
    daf_set_ui(op1, (TEN_9_MAX + 1) * i + TEN_9_MAX);

    daf_add(rop, op1, op2);

    daf_printf("%DF + %DF = %DF\n", op1, op2, rop);
  }

  daf_debug_out(op1, "op1");

  daf_clear(op1);
  daf_clear(op2);
  daf_clear(rop);

  return EXIT_SUCCESS;
}