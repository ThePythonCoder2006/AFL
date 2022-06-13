#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <string.h>
#include <HPCP.h>
#include <time.h>

#ifdef WIN32
#include <io.h>
#define F_OK 0
#define access _access
#endif

#define TMPPATH "bin/tmp"

uint64_t numb_vars = 1;

int hpcp_set_file_mantissa_zero(hpcp_t *op)
{
  if (op->prec < sizeof(hpcp_limb_t))
    return 0;

  const uint64_t binmax = (op->prec - sizeof(hpcp_limb_t)) + op->real_prec_dec;

  printf("binmax : %" PRIu64 "\n", binmax);

  char filename[64];
  sprintf(filename, TMPPATH "/HPCP-%" PRIu64 ".bin", op->line);

  FILE *bin = fopen_mkdir(filename, "wb");
  if (bin == NULL)
    return -1;

  const hpcp_limb_t buff = {0x00};

  for (uint64_t i = 0; i < binmax / sizeof(hpcp_limb_t); ++i)
    fwrite(&buff, sizeof(buff), 1, bin);

  fclose(bin);
  return 0;
}

/* - init functions -----------------------------------------------------------------------------*/

int hpcp_init(hpcp_t **rop, uint64_t prec)
{
  // sprintf("%i\n", sizeof((*rop)->line));

  // printf("prec = %" PRIu64 " buff = 0x%" PRIx64 "\n", prec, buff);
  *rop = malloc(sizeof(hpcp_t));
  if (*rop == NULL)
    return -1;
  (*rop)->start = calloc(HPCP_LIMB_SIZE, sizeof(uint64_t));
  if ((*rop)->start == NULL)
    return -1;
  (*rop)->line = numb_vars;
  (*rop)->exp = 0;
  (*rop)->prec = prec;
  (*rop)->head = HPCP_ZERO | HPCP_INT;
  (*rop)->real_prec_dec = (sizeof(hpcp_limb_t)) - ((uint64_t)((prec) % sizeof(hpcp_limb_t)));
  if (prec <= sizeof(hpcp_limb_t))
    (*rop)->real_prec_dec = 0;

  ++numb_vars;

  return hpcp_set_file_mantissa_zero(*rop);
}

/* - end init functions -----------------------------------------------------------------------------*/

/* - setting functions -----------------------------------------------------------------------------*/

int hpcp_set_ui(hpcp_t *rop, uint64_t op)
{
  if (op == 0)
    rop->head = HPCP_ZERO | HPCP_INT;
  else
    rop->head = HPCP_INT;

  uint64_t v = op;
  uint8_t val = 0;

  while (v >>= 1) // unroll for more speed...
  {
    val++;
  }

  rop->exp = val;

  // printf("%" PRIu64 ", %" PRIu64 ", " PRINTF_BINARY_PATTERN_INT64 "\n", op, NTH_BIT(op, val), PRINTF_BYTE_TO_BINARY_INT64(op));
  CLR_BIT(op, val);

  op <<= (64 - val);
  // printf("%" PRIu64 ", %" PRIu64 "\n", (uint64_t)(64 - val), (uint64_t)val);
  // printf(PRINTF_BINARY_PATTERN_INT64 "\n", PRINTF_BYTE_TO_BINARY_INT64(op));
  (*(rop->start))[0] = op;

  return hpcp_set_file_mantissa_zero(rop);
}

int hpcp_set_plus_zero(hpcp_t *rop)
{
  rop->head = HPCP_ZERO | HPCP_INT;
  rop->exp = 0;

  for (uint8_t i = 0; i < HPCP_LIMB_SIZE; ++i)
    (*(rop->start))[i] = 0;

  return hpcp_set_file_mantissa_zero(rop);
}

int hpcp_set_minus_zero(hpcp_t *rop)
{
  rop->head = HPCP_ZERO | HPCP_INT | HPCP_MINUS;
  rop->exp = 0;

  for (uint8_t i = 0; i < HPCP_LIMB_SIZE; ++i)
    (*(rop->start))[i] = 0;

  return hpcp_set_file_mantissa_zero(rop);
}

int hpcp_set_NaN(hpcp_t *rop)
{
  rop->head = HPCP_NAN;
  rop->exp = 0;

  for (uint8_t i = 0; i < HPCP_LIMB_SIZE; ++i)
    (*(rop->start))[i] = 0;

  return hpcp_set_file_mantissa_zero(rop);
}

int hpcp_set_plus_inf(hpcp_t *rop)
{
  rop->head = HPCP_INF;
  rop->exp = UINT64_MAX;

  for (uint8_t i = 0; i < HPCP_LIMB_SIZE; ++i)
    (*(rop->start))[i] = 0;

  return hpcp_set_file_mantissa_zero(rop);
}

int hpcp_set_minus_inf(hpcp_t *rop)
{
  rop->head = HPCP_INF | HPCP_MINUS;
  rop->exp = UINT64_MAX;

  for (uint8_t i = 0; i < HPCP_LIMB_SIZE; ++i)
    (*(rop->start))[i] = 0;

  return hpcp_set_file_mantissa_zero(rop);
}

/* - end setting functions -----------------------------------------------------------------------------*/
/* - print functions -----------------------------------------------------------------------------*/

int hpcp_printf_bin(hpcp_t *op)

{
  if (HPCP_IS_NAN)
  {
    printf("NaN");
    return 0;
  }

  printf("%c", (op->head | HPCP_MINUS) == op->head ? '-' : 0);

  if (HPCP_IS_INF)
  {
    printf("Infinity");
    return 0;
  }

  if (HPCP_IS_ZERO)
  {
    printf("0");
    return 0;
  }

  printf("2^%c%" PRIu64 " x 1.", (op->head | HPCP_EXP_MINUS) == op->head ? '-' : 0, op->exp);
  for (uint8_t i = 0; i < HPCP_LIMB_SIZE; ++i)
    printf(PRINTF_BINARY_PATTERN_INT64, PRINTF_BYTE_TO_BINARY_INT64(((*(op->start))[i])));

  if (op->prec <= sizeof(hpcp_limb_t))
    return 0;

  char filename[64];
  sprintf(filename, TMPPATH "/HPCP-%" PRIu64 ".bin", op->line);
  FILE *bin = fopen(filename, "rb");
  uint64_t data;
  for (size_t i = 0; i < (((op->prec - sizeof(hpcp_limb_t)) + op->real_prec_dec) / sizeof(uint64_t)); ++i)
  {
    fread(&data, sizeof(data), 1, bin);
    printf(PRINTF_BINARY_PATTERN_INT64, PRINTF_BYTE_TO_BINARY_INT64(data));
  }
  fclose(bin);
  return 0;
}

/* - end print functions -----------------------------------------------------------------------------*/
/* - arthrimetrics functions -----------------------------------------------------------------------------*/

uint8_t hpcp_add_uint64(uint64_t *rop, const uint64_t op1, const uint64_t op2)
{
  *rop = (op1 & ~(1ll << 63)) + (op2 & ~(1ll << 63));

  return ((uint8_t)((op1 & op2) >> 63));
}

void *hpcp_add_limb(hpcp_limb_t *rop, const hpcp_limb_t op1, const hpcp_limb_t op2)
{
#define HPCP_ADD_LIMB_GET_REM_BIT(N) (rem[(size_t)(((N) + 1) / 8)] >> ((((N) + 1) % 8) - 1)) & 1
#define HPCP_ADD_LIMB_SET_REM_BIT(N) rem[(size_t)(((N) + 1) / 8)] |= 1 << ((((N) + 1) % 8) - 1)

  uint8_t *rem = calloc(1, ((HPCP_LIMB_SIZE / 8)) + 1);
  if (rem == NULL)
    return (void *)-1;

  for (size_t i = 0; i < HPCP_LIMB_SIZE; ++i)
  {
    if (hpcp_add_uint64(&(*rop)[i], op1[i], op2[i]))
    {
      HPCP_ADD_LIMB_SET_REM_BIT(i);
    }
  }

  for (int64_t i = 1; i >= 0; --i)
    printf(PRINTF_BINARY_PATTERN_INT8, PRINTF_BYTE_TO_BINARY_INT8(rem[i]));
  printf("\n");
  return rem;

#undef HPCP_ADD_LIMB_GET_REM_BIT
}

int hpcp_add(hpcp_t *rop, hpcp_t *op1, hpcp_t *op2)
{
  (void)rop;
  (void)op1;
  (void)op2;
  return 0;
}

inline int hpcp_negate(hpcp_t *rop, hpcp_t *op)
{
  rop->head = op->head ^ HPCP_MINUS;

  return 0;
}

/* - end arthrimetrics functions -----------------------------------------------------------------------------*/

void hpcp_clear(hpcp_t *rop)
{
  free(*(rop->start));
  char filename[64];
  hpcp_get_filename(filename, rop);
  printf("%s\n", filename);
  remove(filename);
  free((void *)rop);
  return;
}

int hpcp_copy(hpcp_t *dst, hpcp_t *src)
{
  dst->exp = src->exp;
  dst->prec = src->prec;
  dst->head = src->head;
  dst->start = src->start;
  dst->real_prec_dec = src->real_prec_dec;

  char filename[64];
  hpcp_get_filename(filename, src);
  FILE *srcbin = fopen(filename, "rb");
  hpcp_get_filename(filename, dst);
  FILE *dstbin = fopen(filename, "wb");

  if (srcbin == NULL || dstbin == NULL)
    return -1;

  hpcp_limb_t tmp;

  for (size_t i = 0; i < ((src->prec - sizeof(hpcp_limb_t)) + src->real_prec_dec) / sizeof(hpcp_limb_t); ++i)
  {
    fread(&tmp, sizeof(tmp), 1, srcbin);
    fwrite(&tmp, sizeof(tmp), 1, dstbin);
  }

  fclose(srcbin);
  fclose(dstbin);
  return 0;
}

size_t hpcp_get_filename(char filename[64], hpcp_t *op)
{
  return sprintf(filename, TMPPATH "/HPCP-%" PRIu64 ".bin", op->line);
}

// file stuff ------------------------------------------------------

void rek_mkdir(char *path)
{
  char *sep = strrchr(path, '/');
  if (sep != NULL)
  {
    *sep = 0;
    rek_mkdir(path);
    *sep = '/';
  }
  if (mkdir(path) && errno != EEXIST)
    printf("error while trying to create '%s'\n", path);
}

FILE *fopen_mkdir(char *path, char *mode)
{
  char *sep = strrchr(path, '/');
  if (sep)
  {
    char *path0 = strdup(path);
    path0[sep - path] = 0;
    rek_mkdir(path0);
    free(path0);
  }
  return fopen(path, mode);
}

// general purpuse stuff -------------------------------------------------

inline int64_t abs2(int64_t op)
{
  int const mask = op >> ((sizeof(int) * 8) - 1);

  return (op + mask) ^ mask;
}