#include <stdio.h>
#include <HPCP.h>

hpcp_t num;
int main(int argc, char **argv)
{
  hpcp_init(num, 20);
  return 0;
}

int hpcp_init(hpcp_t rop, uint64_t prec)
{
  for (size_t i = 0; i < prec; i += 8)
  {
    printf("created limb number %i\n", i / 8 + 1);
  }
}