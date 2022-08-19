#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>

#include "DAFL.h"

#ifdef _WIN32
#include <io.h>
#define F_OK 0
#define access _access
#endif

uint64_t nb_daf = 0;

uint8_t all_daf_already_init = 0;
daf_t **all_daf = NULL;

daf_ret_t daf_load_mantissa(daf_ref_t op_ref)
{
  DAF_GET_FLT(op);
  uint64_t mantissa_size = op.exp + op.real_prec_dec - DAF_LIMB_SIZE;

  char filename[64];
  daf_get_filename(filename, op_ref);
  FILE *fmantissa = fopen(filename, "r");

  for (uint64_t i = 0; i < mantissa_size; ++i)
  {
    fread(&(op.loaded_mantissa[i]), sizeof(daf_limb_t), 1, fmantissa);
  }
  return DAF_RET_SUCESS;
}

daf_ret_t daf_set_file_mantissa_zero(daf_ref_t op_ref)
{
  DAF_GET_FLT(op);

  if (op.prec < DAF_LIMB_SIZE)
    return DAF_RET_SUCESS;

  const uint64_t binmax = (op.prec - DAF_LIMB_SIZE) + op.real_prec_dec;

  // printf("binmax : %" PRIu64 "\n", binmax);

  char filename[64];
  daf_get_filename(filename, op_ref);

  FILE *bin = fopen_mkdir(filename, "wb");
  if (bin == NULL)
    return DAF_RET_ERR_READ_FILE;

  const daf_limb_t buff = {0x00};

  for (uint64_t i = 0; i < binmax / DAF_LIMB_SIZE; ++i)
    fwrite(&buff, sizeof(buff), 1, bin);

  fclose(bin);
  return 0;
}

// init functions

daf_ret_t init_all_daf(void)
{
  if (!all_daf_already_init)
  {
    printf("%i\n", all_daf_already_init);
    all_daf = calloc(10, sizeof(daf_t *));
    all_daf_already_init = 1;
  }
  if (all_daf == NULL)
  {
    return DAF_RET_ERR_ALLOC;
  }
  return DAF_RET_SUCESS;
}

daf_ret_ref_t daf_init(uint64_t prec)
{
  if (init_all_daf() == DAF_RET_ERR_ALLOC)
    return DAF_RET_ERR_ALLOC;

  daf_ret_ref_t ref = nb_daf++;

  all_daf[ref] = calloc(1, sizeof(daf_t));
  if (all_daf[ref] == NULL)
    return DAF_RET_ERR_ALLOC;

  all_daf[ref]->start = calloc(DAF_LIMB_SIZE, sizeof(uint30_t));
  if (all_daf[ref]->start == NULL)
    return DAF_RET_ERR_ALLOC;

  all_daf[ref]->exp = 0ULL;
  all_daf[ref]->prec = prec;
  all_daf[ref]->real_prec_dec = TEN_9_DECIMAL_SIZE - (prec % TEN_9_DECIMAL_SIZE);
  all_daf[ref]->head = DAF_HEAD_INT | DAF_HEAD_ZERO;

  daf_set_file_mantissa_zero(ref);

  return ref;
}

// print functions

daf_ret_t daf_printf(const char *fmt, ...)
{
  va_list args;
  va_start(args, fmt);

  char curr;
  while ((curr = *fmt) != '\0')
  {
    fmt++;
    if (curr != '%') // if the char is not a '%' then just print it
    {
      putchar(curr);
      continue;
    }

    switch (*(fmt++)) // acess the next caracter after the '%'
    {
    case 'F':
    {
      daf_all_out_str((daf_ref_t)va_arg(args, daf_ref_t));
    }
    break;
    default:
    {
      fprintf(stderr, "[ERROR] the print type '%%%c' is not (yet) implemented", curr);
      return DAF_RET_ERR_ALLOC;
    }
    }
  }

  return DAF_RET_SUCESS;
}

daf_ret_t daf_out_str(daf_ref_t op_ref, uint64_t prec)
{
  if (prec != 0ULL)
  {
    fprintf(stderr, "[ERROR] not implemented yet...");
    return DAF_RET_ERR_ALLOC;
  }

  daf_ret_t err;
  if ((err = daf_load_mantissa(op_ref)) != DAF_RET_SUCESS)
    return err;

  DAF_GET_FLT(op);
  uint64_t integer_part_size = op.exp;

  for (uint64_t i = 0; i < integer_part_size - (integer_part_size % DAF_LIMB_SIZE); ++i)
  {
    for (uint8_t j = 0; j < DAF_LIMB_SIZE; ++j)
    {
      printf("%i", (*(op.loaded_mantissa[i]))[j]);
    }
  }

  return DAF_RET_SUCESS;
}

size_t daf_get_filename(char filename[64], daf_ref_t op_ref)
{
  return sprintf(filename, TMPPATH "/DAF-%" PRIu64 ".bin", op_ref);
}

// file stuff ------------------------------------------------------

void rek_mkdir(const char *const path)
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

FILE *fopen_mkdir(const char *const path, const char *const mode)
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
