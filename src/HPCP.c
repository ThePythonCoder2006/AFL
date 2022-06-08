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

  FILE *bin = fopen_mkdir(filename, "wb");
  if (bin == NULL)
    return -1;

  uint8_t buff = 0x00;

  // sprintf("%i\n", sizeof((*rop)->line));

  // printf("prec = %" PRIu64 " buff = 0x%" PRIx64 "\n", prec, buff);
  *rop = malloc(sizeof(hpcp_t));
  (*rop)->start = calloc(1, sizeof(hpcp_limb_t));
  (*rop)->line = numb_vars;
  (*rop)->exp = 0;
  (*rop)->prec = prec;
  (*rop)->head = HPCP_0;
  printf("head : %" PRIu8 "\n", (*rop)->head);

  for (uint64_t i = 0; i <= prec; ++i)
    fwrite(&buff, sizeof(buff), 1, bin);

  ++numb_vars;

  // printf("%" PRIu64 "\n", rop->prec);

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
  rop->head = 0x00;
  FILE *f = fopen(TMPPATH "/HPCP-1.bin", "wb");

  // for (size_t i = 0; i < (rop->prec + rop->real_prec_dec); ++i)
  // {
  // }

  printf("%" PRIu64 ", %" PRIu64 ", " PRINTF_BINARY_PATTERN_INT64 "\n", op, NTH_BIT(op, val), PRINTF_BYTE_TO_BINARY_INT64(op));
  CLR_BIT(op, val);

  op <<= (64 - val);
  printf("%" PRIu64 ", %" PRIu64 "\n", (uint64_t)(64 - val), val);
  printf("2^%" PRIu64 " x 1." PRINTF_BINARY_PATTERN_INT64 "\n", rop->exp, PRINTF_BYTE_TO_BINARY_INT64(op));

  fwrite(&op, sizeof(uint64_t), 1, f);

  fclose(f);
  return;
}

<<<<<<< HEAD
void hpcp_add(hpcp_t rop, hpcp_t op1, hpcp_t op2)
{
  return;
}

=======
int hpcp_printf_bin(hpcp_t *op)
{
  printf("2^%" PRIu8 "%" PRIu64 "", (op->head & HPCP_0) == op->head ? 0 : '-', op->exp);
  for (size_t i = 0; i < op->prec + op->real_prec_dec; ++i)
    return 0;
}

void hpcp_add(hpcp_t *rop, hpcp_t *op1, hpcp_t *op2)
{
  if (rop == NULL || op1 == NULL || op2 == NULL)
    return;

  return;
}

>>>>>>> 8b0d6d52e9a5acf511c3b7994829d53696025c96
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