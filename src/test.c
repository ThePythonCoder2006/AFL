
#define HPCP_GET_PTR(op) int *op = ALL_HPCP_FLOAT_NAME[op##_ref]

int main(void)
{
  int *ALL_HPCP_FLOAT_NAME[100];
  HPCP_GET_PTR(dst);
  return 0;
}