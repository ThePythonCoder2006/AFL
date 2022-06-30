#include <stdio.h>
#include <stdlib.h>
#include "HPCP.h"

int main(int argc, char **argv)
{
  // setting tests
  hpcp_limb_t set, res = {};
  hpcp_limb_set_ui(set, 37);

  uint8_t diff = 0;

  for (size_t i = 0; i < HPCP_LIMB_SIZE; ++i)
    if (set[i] != res[i])
      diff = 1;

  return 0;
}