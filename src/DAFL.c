#include "DAFL.h"

uint64_t nb_daf = 0;

uint8_t all_daf_already_init = 0;
daf_t **all_daf = NULL;

char *(err_message)[DAF_ERR_COUNT] = {
    PRINTF_SUCESS " everything appended as intended",
    PRINTF_ERROR " some memory couldn't be allocated",
    PRINTF_ERROR " the file containing the flaots mantissa couldn't be read",
    PRINTF_ERROR " the float you passed in is invalid",
    PRINTF_ERROR " this funcitonnality was not (yet) implemented"};

daf_ret_t daf_load_mantissa(daf_ref_t op_ref)
{
  DAF_GET_PTR(op);
  uint64_t mtsa_size = (op->prec + op->real_prec_dec) - DAF_LIMB_SIZE;

  char filename[64];
  daf_get_filename(filename, op_ref);
  FILE *fmantissa = fopen(filename, "r");

  op->loaded_mtsa = calloc(mtsa_size / DAF_LIMB_SIZE, sizeof(daf_t *));
  if (op->loaded_mtsa == NULL)
    return DAF_RET_ERR_ALLOC;
  for (uint64_t i = 0; i < mtsa_size / DAF_LIMB_SIZE; ++i)
  {
    op->loaded_mtsa[i] = calloc(DAF_LIMB_SIZE, sizeof(uint30_t));
    if (op->loaded_mtsa[i] == NULL)
      return DAF_RET_ERR_ALLOC;

    fread(op->loaded_mtsa[i], sizeof(uint30_t), 1, fmantissa);
  }
  return DAF_RET_SUCESS;
}

daf_ret_t daf_set_file_mantissa_zero(daf_ref_t op_ref)
{
  DAF_GET_PTR(op);

  if (op->prec < DAF_LIMB_SIZE)
    return DAF_RET_SUCESS;

  const uint64_t binmax = (op->prec - DAF_LIMB_SIZE) + op->real_prec_dec;

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
  all_daf[ref]->real_prec_dec = DAF_LIMB_DECIMAL_SIZE - (prec % DAF_LIMB_DECIMAL_SIZE);
  all_daf[ref]->head = DAF_HEAD_INT | DAF_HEAD_ZERO;

  daf_set_file_mantissa_zero(ref);

  return ref;
}

// clear functions

daf_ret_t daf_clear(daf_ref_t op_ref)
{
  DAF_GET_PTR(op);
  free(*(op->start));
  char filename[64];
  daf_get_filename(filename, op_ref);
  remove(filename);

  if (op->loaded_mtsa != NULL)
    for (uint64_t i = 0; i < (op->prec + op->real_prec_dec) / 50 - 1; ++i)
      free(op->loaded_mtsa[i]);
  free(op->loaded_mtsa);

  free((void *)all_daf[op_ref]);
  all_daf[op_ref] = NULL;
  return DAF_RET_SUCESS;
}

// print functions

daf_ret_t daf_printf(const char *fmt, ...)
{
  va_list args;
  va_start(args, fmt);

  char curr;
  while ((curr = *fmt) != '\0')
  {
    if (curr != '%') // if the char is not a '%' then just print it
    {
      ++fmt;
      putchar(curr);
      continue;
    }

    if (*(++fmt) == 'D')
    {
      switch (*(++fmt))
      {
      case 'F':
        ++fmt;
        daf_all_out_str((daf_ref_t)va_arg(args, daf_ref_t));
        break;

      default:
        break;
      }
    }
    else
    {
      fprintf(stderr, PRINTF_ERROR " the print type '%%%c' is not (yet) implemented", curr);
      return DAF_RET_ERR_ALLOC;
    }
  }

  return DAF_RET_SUCESS;
}

daf_ret_t daf_out_str(daf_ref_t op_ref, uint64_t prec)
{
  DAF_GET_PTR(op);

  if (DAF_IS_NaN(op_ref))
  {
    printf("NaN");
    return DAF_RET_SUCESS;
  }

  printf("%c", (op->head | DAF_HEAD_MINUS) == op->head ? '-' : 0);

  if (DAF_IS_ZERO(op_ref))
  {
    printf("0");
    return DAF_RET_SUCESS;
  }

  if (DAF_IS_INF(op_ref))
  {
    printf("Inf");
    return DAF_RET_SUCESS;
  }

  // char sep = DAF_IS_INT(op_ref) * '.';
  char sep = '.';

  daf_ret_t err;
  if ((err = daf_load_mantissa(op_ref)) != DAF_RET_SUCESS)
    return err;

  uint64_t printed_ten_9 = 1;

  printf("%i", (*(op->start))[0]);
  if (op->exp >= DAF_LIMB_SIZE && (prec > DAF_LIMB_SIZE || prec == 0))
  {
    for (uint8_t i = 1; i < DAF_LIMB_SIZE; ++i)
    {
      printf(" %09" PRIu32, (*(op->start))[i]);
    }
    if (op->exp == DAF_LIMB_SIZE)
      putchar(sep);
    printed_ten_9 = DAF_LIMB_SIZE; // printed_ten_9 += DAF_LIMB_SIZE; is equivalent because printed_ten_9 is zero
  }
  else
  {
    for (uint8_t i = 1; i < DAF_LIMB_SIZE; ++i)
    {
      printf(" %09" PRIu32, (*(op->start))[i]);
      if ((printed_ten_9++ == op->exp && DAF_IS_INT(op_ref)) || (op->exp == 0 && DAF_IS_INT(op_ref)))
        return DAF_RET_SUCESS;
      else if (printed_ten_9 == op->exp && !DAF_IS_INT(op_ref))
        putchar(sep);

      if (printed_ten_9 == prec)
        return DAF_RET_SUCESS;
    }
  }

  for (uint64_t i = 0; i < op->prec - DAF_LIMB_SIZE; ++i)
  {
    printf(" %09" PRIu32, DAF_MTSA_NTH(op_ref, i));
    if (++printed_ten_9 == op->exp)
      putchar(sep);
  }
  return DAF_RET_SUCESS;
}

size_t daf_get_filename(char filename[64], daf_ref_t op_ref)
{
  return sprintf(filename, TMPPATH "/DAF-%" PRIu64 ".bin", op_ref);
}

daf_ret_t daf_err_to_str(daf_ret_t err, char *const buff)
{
  strcpy(buff, err_message[err]);
  return DAF_RET_SUCESS;
}

// set functions ------------------------------------------------------

daf_ret_t daf_set_plus_zero(daf_ref_t op_ref)
{
  DAF_GET_PTR(op);

  op->head = DAF_HEAD_ZERO | DAF_HEAD_INT;
  op->exp = 0;

  for (uint8_t i = 0; i < DAF_LIMB_SIZE; ++i)
    (*(op->start))[i] = 0;

  return daf_set_file_mantissa_zero(op_ref);
}

daf_ret_t daf_set_minus_zero(daf_ref_t op_ref)
{
  DAF_GET_PTR(op);

  op->head = DAF_HEAD_ZERO | DAF_HEAD_INT | DAF_HEAD_MINUS;
  op->exp = 0;

  for (uint8_t i = 0; i < DAF_LIMB_SIZE; ++i)
    (*(op->start))[i] = 0;

  return daf_set_file_mantissa_zero(op_ref);
}

daf_ret_t daf_set_NaN(daf_ref_t op_ref)
{
  DAF_GET_PTR(op);

  op->head = DAF_HEAD_NaN;
  op->exp = 0;

  for (uint8_t i = 0; i < DAF_LIMB_SIZE; ++i)
    (*(op->start))[i] = 0;

  return daf_set_file_mantissa_zero(op_ref);
}

daf_ret_t daf_set_plus_inf(daf_ref_t op_ref)
{
  DAF_GET_PTR(op);

  op->head = DAF_HEAD_INF;
  op->exp = UINT64_MAX;

  for (uint8_t i = 0; i < DAF_LIMB_SIZE; ++i)
    (*(op->start))[i] = 0;

  return daf_set_file_mantissa_zero(op_ref);
}

daf_ret_t daf_set_minus_inf(daf_ref_t op_ref)
{
  DAF_GET_PTR(op);

  op->head = DAF_HEAD_INF | DAF_HEAD_MINUS;
  op->exp = UINT64_MAX;

  for (uint8_t i = 0; i < DAF_LIMB_SIZE; ++i)
    (*(op->start))[i] = 0;

  return daf_set_file_mantissa_zero(op_ref);
}

daf_ret_t daf_set_ui(daf_ref_t rop_ref, uint64_t op)
{
  if (op == 0)
  {
    daf_set_plus_zero(rop_ref);
    return DAF_RET_SUCESS;
  }

  uint30_t p1, p2, p3, tmp;

  p1 = op % (TEN_9_MAX + 1);
  p2 = (tmp = ((op - p1) / (TEN_9_MAX))) % (TEN_9_MAX + 1);
  p3 = ((tmp - p2) / (TEN_9_MAX)) % (TEN_9_MAX + 1);

  DAF_GET_PTR(rop);
  rop->head = DAF_HEAD_INT;
  if (p2 == 0)
  {
    rop->exp = 0;
    (*(rop->start))[0] = p1;
    return DAF_RET_SUCESS;
  }
  if (p3 == 0)
  {
    rop->exp = 1;
    (*(rop->start))[1] = p1;
    (*(rop->start))[0] = p2;
    return DAF_RET_SUCESS;
  }

  rop->exp = 2;
  (*(rop->start))[2] = p1;
  (*(rop->start))[1] = p2;
  (*(rop->start))[0] = p3;

  return DAF_RET_SUCESS;
}

// arthimetric functions ------------------------------------------------------

daf_ret_t daf_negate(daf_ref_t rop_ref, daf_ref_t op_ref)
{
  all_daf[rop_ref]->head = all_daf[op_ref]->head ^ DAF_HEAD_MINUS;
  return DAF_RET_SUCESS;
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
