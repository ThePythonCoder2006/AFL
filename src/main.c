#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#include "DAFL.h"

int main(int argc, char **argv)
{
  // remove the first element of the call (the name of the program)
  --argc, argv++;

  daf_ref_t op1 = daf_init(200), op2 = daf_init(200), rop = daf_init(200);

  daf_set_ui(op1, (TEN_9_MAX + 1) * 2 + TEN_9_MAX);
  daf_set_ui(op2, 1);

  daf_add(rop, op1, op2);

  daf_printf("%DF + %DF = %DF\n", op1, op2, rop);

  daf_clear(op1);
  daf_clear(op2);
  daf_clear(rop);

  return 0;
}