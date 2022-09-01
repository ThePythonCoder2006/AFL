#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#include "DAFL.h"

int main(int argc, char **argv)
{
  (void)argc;
  (void)argv;

  daf_ref_t num = daf_init(200);

  printf("Hello DAF !! %" PRIu64 ", %" PRIu64 ", %" PRIu64 "\n", DAF_GET(num, prec), (uint64_t)DAF_GET(num, real_prec_dec), (uint64_t)(DAF_GET(num, prec) + (uint64_t)DAF_GET(num, real_prec_dec)) % DAF_LIMB_DECIMAL_SIZE);

  uint30_t rop;

  daf_ten_9_add(&rop, (TEN_9_MAX), 1);
  printf(PRINTF_BINARY_PATTERN_INT32 "\n", PRINTF_BYTE_TO_BINARY_INT32(rop));
  printf("%i + %i = %i carry %i\n", 34, 35, rop & ~(1 << 30), rop >> 30);

  daf_clear(num);

  return 0;
}