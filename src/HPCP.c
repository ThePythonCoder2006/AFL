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

int hpcp_init(hpcp_t **rop, uint64_t prec)
{
  char filename[64];
  sprintf(filename, TMPPATH "/HPCP-%" PRIu64 ".bin", numb_vars);

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
  (*rop)->head = HPCP_0 | HPCP_INT;

  ++numb_vars;

  uint64_t binmax;

  if (prec < sizeof(hpcp_limb_t))
    return 0;

  binmax = prec - sizeof(hpcp_limb_t);

  printf("%" PRIu64 "\n", binmax);

  const uint8_t buff = 0x00;

  FILE *bin = fopen_mkdir(filename, "wb");
  if (bin == NULL)
    return -1;

  for (uint64_t i = 0; i < binmax; ++i)
    fwrite(&buff, sizeof(buff), 1, bin);

  fclose(bin);
  return 0;
}

void hpcp_set_ui(hpcp_t *rop, uint64_t op)
{
  uint64_t v = op;
  uint8_t val = 0;

  while (v >>= 1) // unroll for more speed...
  {
    val++;
  }
  printf("%i\n", val);

  rop->exp = val;
  rop->head = HPCP_INT;
  FILE *f = fopen(TMPPATH "/HPCP-1.bin", "wb");

  // for (size_t i = 0; i < (rop->prec + rop->real_prec_dec); ++i)
  // {
  // }

  // printf("%" PRIu64 ", %" PRIu64 ", " PRINTF_BINARY_PATTERN_INT64 "\n", op, NTH_BIT(op, val), PRINTF_BYTE_TO_BINARY_INT64(op));
  CLR_BIT(op, val);

  op <<= (64 - val);
  // printf("%" PRIu64 ", %" PRIu64 "\n", (uint64_t)(64 - val), (uint64_t)val);
  // printf("2^%" PRIu64 " x 1." PRINTF_BINARY_PATTERN_INT64 "\n", rop->exp, PRINTF_BYTE_TO_BINARY_INT64(op));s

  fwrite(&op, sizeof(uint64_t), 1, f);

  fclose(f);
  return;
}

int hpcp_printf_bin(hpcp_t *op)
{
  printf("2^%c%" PRIu64 " x ", NTH_BIT(op->head, 4) == 0 ? 0 : '-', op->exp);
  for (uint8_t i = 0; i < HPCP_LIMB_SIZE; ++i)
    printf(PRINTF_BINARY_PATTERN_INT64, PRINTF_BYTE_TO_BINARY_INT64(((*(op->start))[i])));
  for (size_t i = 0; i < op->prec + op->real_prec_dec; ++i)
    ;
  return 0;
}

void hpcp_add(hpcp_t *rop, hpcp_t *op1, hpcp_t *op2)
{
  if (rop == NULL || op1 == NULL || op2 == NULL)
    return;

  return;
}

void hpcp_clear(hpcp_t *rop)
{
  free(*(rop->start));
  char filename[64];
  sprintf(filename, TMPPATH "/HPCP-%" PRIu64 ".bin", rop->line);
  printf("%s\n", filename);
  remove(filename);
  free((void *)rop);
  return;
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