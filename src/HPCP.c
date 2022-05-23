#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <string.h>
#include <HPCP.h>
#include <io.h>

int hpcp_init(hpcp_t *rop, uint64_t prec)
{
  FILE *list = fopen_mkdir("tmp/tmp-list.txt", "a");
  FILE *bin = fopen("tmp/tmp.bin", "wb");
  if (list == NULL || bin == NULL)
    return -1;
  unsigned char buff = 0;
  for (uint64_t i = 0; i <= prec; ++i)
    fwrite(&buff, sizeof(buff), 1, bin);
  // printf("prec = %" PRIu64 " buff = 0x%" PRIx64 "\n", prec, buff);
  rop = malloc(sizeof(hpcp_t));
  hpcp_limb_t *start = calloc(10, sizeof(hpcp_limb_t));
  rop->start = start;
  fclose(list);
  fclose(bin);
  return 0;
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