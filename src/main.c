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

  printf("Hello DAF !! %" PRIu64 ", %" PRIu64 ", %" PRIu64 "\n", DAF_GET(num, prec), (uint64_t)DAF_GET(num, real_prec_dec), (uint64_t)(DAF_GET(num, prec) + (uint64_t)DAF_GET(num, real_prec_dec)) % TEN_9_DECIMAL_SIZE);

  return 0;
}