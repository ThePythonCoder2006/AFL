#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <string.h>
#include <HPCP.h>
#include <io.h>
#include <time.h>

#define TMPPATH "bin/tmp"

uint64_t numb_vars = 1;

int hpcp_init(hpcp_t **rop, uint64_t prec)
{
  char filename[64];
  sprintf(filename, "./" TMPPATH "/HPCP-%" PRIu64 ".bin", numb_vars);

  FILE *bin = fopen_mkdir(filename, "wb");
  if (bin == NULL)
    return -1;

  uint8_t buff = 0x00;
  for (uint64_t i = 0; i <= prec; ++i)
    fwrite(&buff, sizeof(buff), 1, bin);
  fwrite((uint64_t)0, sizeof(uint64_t), 1, bin);

  printf("%i\n", sizeof((*rop)->line));

  // printf("prec = %" PRIu64 " buff = 0x%" PRIx64 "\n", prec, buff);
  *rop = malloc(sizeof(hpcp_t));
  (*rop)->start = calloc(1, sizeof(hpcp_limb_t));
  (*rop)->prec = prec;
  (*rop)->line = numb_vars;

  ++numb_vars;

  // printf("%" PRIu64 "\n", rop->prec);

  fclose(bin);
  return 0;
}

void hpcp_set_ui(hpcp_t *rop, uint64_t op)
{
}

void hpcp_clear(hpcp_t *rop)
{
  char filename[64];
  sprintf(filename, "./" TMPPATH "/HPCP-%" PRIu64 ".bin", rop->line);
  printf("%s\n", filename);
  // remove(filename);
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