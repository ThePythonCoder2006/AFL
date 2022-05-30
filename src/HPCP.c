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
  (*rop)->head = HPCP_0;

  for (uint64_t i = 0; i <= prec; ++i)
    fwrite(&buff, sizeof(buff), 1, bin);

  ++numb_vars;

  // printf("%" PRIu64 "\n", rop->prec);

  fclose(bin);
  return 0;
}

void hpcp_set_ui(hpcp_t *rop, uint64_t op)
{
  if (op == 0)
  {
    fprintf(stderr, "[TODO] handle set ui 0\n");
    return;
  }

  uint8_t buff;
  uint8_t val = 0x20;
  uint8_t pval = 0x40;
  uint8_t sign;

  while (abs(val - pval) > 1)
  {
    // printf("%i, %i, %" PRIu64 ", %" PRIu64 "\n", val, pval, op, ((uint64_t)0x01 << val));
    uint64_t tmp = ((uint64_t)0x01 << val);
    if (op == tmp)
      break;
    else
    {
      if (op < tmp)
        sign = -1;
      else
        sign = 1;

      buff = val;
      val += sign * abs(pval - val) / 2;
      pval = buff;
    }
  }
  printf("%i\n", val);

  rop->exp = val;
  rop->head = 0x00;
  FILE *f = fopen(TMPPATH "/HPCP-1.bin", "wb");

  printf("%" PRIu64 ", %i\n", op, NTH_BIT(op, val));
  UNSET_BIT(op, val);
  printf("%" PRIu64 "\n", op);

  fwrite(&op, sizeof(uint64_t), 1, f);

  fclose(f);
}

void hpcp_clear(hpcp_t *rop)
{
  free(*(rop->start));
  char filename[64];
  sprintf(filename, TMPPATH "/HPCP-%" PRIu64 ".bin", rop->line);
  printf("%s\n", filename);
  remove(filename);
  free((void *)rop);
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