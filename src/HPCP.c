#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <conio.h>
#include <HPCP.h>
#include <dirent.h>

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
  printf("ok\n");
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

int remove_recursive(const char *const path)
{
  struct dirent *de; // Pointer for directory entry

  // opendir() returns a pointer of DIR type.
  DIR *dr = opendir(".");

  if (dr == NULL) // opendir returns NULL if couldn't open directory
  {
    printf("Could not open current directory");
    return 0;
  }

  while ((de = readdir(dr)) != NULL)
    printf("%s\n", de->d_name);

  closedir(dr);
  return 0;
}