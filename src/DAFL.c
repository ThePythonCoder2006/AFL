#include "DAFL.h"

uint64_t nb_daf = 0;

uint8_t all_daf_already_init = 0;
daf_t **all_daf = NULL;

char *(err_message)[DAF_ERR_COUNT] = {
    PRINTF_SUCESS " everything appended as intended",
    PRINTF_ERROR " some memory couldn't be allocated",
    PRINTF_ERROR " the file containing the float's mantissa couldn't be read",
    PRINTF_ERROR " the float you passed in is invalid",
    PRINTF_ERROR " this funcitonnality was not (yet) implemented"};

daf_ret_t daf_load_mantissa(daf_ref_t op_ref)
{
  DAF_GET_PTR(op);

  if (op->loaded_mtsa != NULL)
    return DAF_RET_SUCESS;

  uint64_t mtsa_size = (op->prec + op->real_prec_dec) - DAF_LIMB_SIZE;

  char filename[64];
  daf_get_filename(filename, op_ref);
  FILE *fmantissa = fopen(filename, "rb");

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
  fclose(fmantissa);
  return DAF_RET_SUCESS;
}

daf_ret_t daf_set_file_mantissa_zero(daf_ref_t op_ref)
{
  DAF_GET_PTR(op);

  if (op->prec < DAF_LIMB_SIZE)
    return DAF_RET_SUCESS;

  const uint64_t binmax = (op->prec - DAF_LIMB_SIZE) + op->real_prec_dec;

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

daf_ret_t daf_primitive_vnprint(FILE *stream, char *buff, const uint64_t n, const char *fmt, va_list args)
{
#define out_str(str)                 \
  if (sn)                            \
    strncat(buff, str, strlen(str)); \
  else                               \
    fprintf(stream, "%s", str);

#define out_args(str, ...)                                  \
  if (sn)                                                   \
  {                                                         \
    char tmp_buff[64];                                      \
    snprintf(tmp_buff, sizeof(tmp_buff), str, __VA_ARGS__); \
    strncat(buff, str, strlen(str));                        \
  }                                                         \
  else                                                      \
    fprintf(stream, str, __VA_ARGS__);

  uint64_t printed_chars = 0;

  const uint8_t sn = (stream == NULL && buff != NULL) ? 1 : 0;

  char curr;
  while ((curr = *fmt) != '\0')
  {
    if (curr != '%') // if the char is not a '%' then just print it
    {
      ++fmt;

      if (sn)
        strncat(buff, &curr, 1);
      else
        fprintf(stream, "%c", curr);
      ++printed_chars;

      if (printed_chars >= n && n != UINT64_MAX)
        return DAF_RET_SUCESS;

      continue;
    }

    if (*(++fmt) == 'D')
    {
      switch (*(++fmt))
      {
      case 'F':
        ++fmt;
        if (sn)
          daf_primitive_out_file_string(NULL, buff, n - printed_chars, (daf_ref_t)va_arg(args, daf_ref_t), ((n - printed_chars) - ((n - printed_chars) % TEN_9_DECIMAL_SIZE)) / TEN_9_DECIMAL_SIZE);
        else
          daf_primitive_out_file_string(stream, NULL, UINT64_MAX, (daf_ref_t)va_arg(args, daf_ref_t), (n - printed_chars));

        printed_chars += n - printed_chars;

        if (printed_chars >= n && n != UINT64_MAX)
          return DAF_RET_SUCESS;

        break;

      default:
        break;
      }
    }
    else
    {
      char tmp[16];
      snprintf(tmp, sizeof(tmp), "%%%c", *(fmt++));
      if (sn)
      {
        uint8_t len;
        char tmp_buff[64];
        vsnprintf(tmp_buff, sizeof(tmp_buff), tmp, args);
        strncat(buff, tmp_buff, len = strlen(tmp_buff));
        printed_chars += len;
      }
      else
        printed_chars += vfprintf(stream, tmp, args);
    }
  }

  return DAF_RET_SUCESS;
}

daf_ret_t daf_primitive_out_file_string(FILE *stream, char *buff, const uint64_t n, daf_ref_t op_ref, uint64_t prec)
{
  uint64_t printed_chars = 0;

  const uint8_t sn = (stream == NULL && buff != NULL) ? 1 : 0;

  DAF_GET_PTR(op);

  // checking for NaN
  if (DAF_IS_NaN(op_ref))
  {
    out_str("NaN");
    return DAF_RET_SUCESS;
  }

  // adding sign
  const char tmp = (op->head | DAF_HEAD_MINUS) == op->head ? '-' : 0;
  if (sn)
    strncat(buff, &tmp, 1);
  else
    fprintf(stream, "%c", tmp);

  // checking for 0
  if (DAF_IS_ZERO(op_ref))
  {
    out_str("0");
    return DAF_RET_SUCESS;
  }

  // checking for inf
  if (DAF_IS_INF(op_ref))
  {
    out_str("Inf");
    return DAF_RET_SUCESS;
  }

  const char sep = '.';

  daf_ret_t err;
  if ((err = daf_load_mantissa(op_ref)) != DAF_RET_SUCESS)
    return err;

  uint64_t printed_ten_9 = 1;

  if (sn)
  {
    uint8_t len;
    char tmp_buff[64];
    snprintf(tmp_buff, sizeof(tmp_buff), "%i", (*(op->start))[0]);
    strncat(buff, "%i", len = strlen("%i"));
    printed_chars += len;
  }
  else
    printed_chars += fprintf(stream, "%i", (*(op->start))[0]);

  if (0 == op->exp && DAF_IS_INT(op_ref))
    return DAF_RET_SUCESS;

  if (printed_chars >= n && n != UINT64_MAX)
    return DAF_RET_SUCESS;

  if (op->exp >= DAF_LIMB_SIZE && (prec > DAF_LIMB_SIZE || prec == 0))
  {
    for (uint8_t i = 1; i < DAF_LIMB_SIZE; ++i)
    {
      out_args(" %09" PRIu32, (*(op->start))[i])
    }
    if (op->exp == DAF_LIMB_SIZE)
    {
      if (sn)
        strncat(buff, &sep, 1);
      else
        putchar(sep);
      ++printed_chars;
    }

    printed_ten_9 = DAF_LIMB_SIZE, printed_chars += (DAF_LIMB_SIZE - 1) * TEN_9_DECIMAL_SIZE; // printed_ten_9 += DAF_LIMB_SIZE; is equivalent because printed_ten_9 is zero

    if (printed_chars >= n && n != UINT64_MAX)
      return DAF_RET_SUCESS;
  }
  else
  {
    for (uint8_t i = 1; i < DAF_LIMB_SIZE; ++i)
    {
      out_args(" %09" PRIu32, (*(op->start))[i]);

      printed_chars += 9;
      if (printed_chars >= n && n != UINT64_MAX)
        return DAF_RET_SUCESS;

      if ((printed_ten_9++ == op->exp && DAF_IS_INT(op_ref)))
      {
        return DAF_RET_SUCESS;
      }
      else
      {
        if (printed_ten_9 == op->exp && !DAF_IS_INT(op_ref))
        {
          if (sn)
            strncat(buff, &sep, 1);
          else
            putchar(sep);
        }
      }

      if (printed_ten_9 == prec)
        return DAF_RET_SUCESS;
    }
  }

  for (uint64_t i = 0; i < op->prec - DAF_LIMB_SIZE; ++i)
  {
    out_args(" %09" PRIu32, DAF_MTSA_NTH(op_ref, i));

    printed_chars += 9;
    if (printed_chars >= n && n != UINT64_MAX)
      return DAF_RET_SUCESS;

    if (++printed_ten_9 == op->exp)
    {
      if (sn)
        strncat(buff, &sep, 1);
      else
        putchar(sep);
    }
  }
  return DAF_RET_SUCESS;

#undef out_str
#undef out_args
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

daf_ret_t daf_limb_set_zero(daf_limb_t *rop)
{
  for (uint8_t i = 0; i < DAF_LIMB_SIZE; ++i)
    (*rop)[i] = 0;
  return DAF_RET_SUCESS;
}

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

  uint30_t p1, p2, p3;
  uint64_t tmp;

  p1 = op % (TEN_9_MAX + 1);
  tmp = (op - p1);
  p2 = ((tmp / (TEN_9_MAX + 1))) % (TEN_9_MAX + 1);
  p3 = ((tmp - p2) / (TEN_9_MAX + 1)) % (TEN_9_MAX + 1);

  DAF_GET_PTR(rop);
  rop->head = DAF_HEAD_INT;
  if (p3 == 0)
  {
    if (p2 == 0)
    {
      rop->exp = 0;
      (*(rop->start))[0] = p1;
      return DAF_RET_SUCESS;
    }
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

daf_ret_t daf_ten_9_add(uint30_t *const rop, const uint30_t op1, const uint30_t op2)
{
#define DAF_ADD_GET_CARRY(op) (op >> 30)
  *rop = op1 + op2;
  if (*rop > TEN_9_MAX)
  {
    *rop -= (TEN_9_MAX + 1);
    *rop |= 1 << 30;
  }
  return DAF_RET_SUCESS;
}
daf_ret_t daf_limb_pp(daf_limb_t *rop) // adds one to the limb
{
  for (uint8_t i = 0; i < DAF_LIMB_SIZE; ++i)
  {
    if ((*rop)[i] < TEN_9_MAX)
    {
      (*rop)[i]++;
      break;
    }
    else if ((*rop)[i] == TEN_9_MAX)
    {
      (*rop)[i] = 0;
      continue;
    }
    else
    {
      fprintf(stderr, PRINTF_ERROR "the ten_9 at index %" PRIu8 " had a value higher than the maximum accepted value  (rop[%" PRIu8 "] = %u > %u, %lu)\n", i, i, (*rop)[i], (uint32_t)TEN_9_MAX, UINT32_MAX);
      printf("rop[%" PRIu8 "] = " PRINTF_BINARY_PATTERN_INT32 "\n", i, PRINTF_BYTE_TO_BINARY_INT32((*rop)[i]));

      return DAF_RET_ERR_INVALID_FLOAT;
    }
  }

  return DAF_RET_SUCESS;
}

daf_ret_t daf_limb_add(uint8_t *const carry, daf_limb_t *const rop, const daf_limb_t op1_top, const daf_limb_t op1_bott, const daf_limb_t op2, const uint8_t uint30_dec)
{
  // helper macros for the hpcp_add function for keeping the remaiders
#define DAF_ADD_GET_REM_BIT(rem_var, N) (((rem_var)[(uint64_t)((N) / 8)] >> ((((N)-1) % 8))) & 1)
#define DAF_ADD_SET_REM_BIT(rem_var, N) (((rem_var)[(uint64_t)((N) / 8)]) |= (1 << (((N)-1) % 8)))
#define DAF_ADD_CLR_REM_BIT(rem_var, N) (((rem_var)[(uint64_t)((N) / 8)]) &= ~(1 << (((N)-1) % 8)))

  // using an array as bitfield to store all of the carrys of the sums
  uint8_t *arrcarry1 = calloc(1, ((uint64_t)(DAF_LIMB_SIZE / 8)) + 1),
          *arrcarry2 = calloc(1, ((uint64_t)(DAF_LIMB_SIZE / 8)) + 1);
  // It's needed to calloc these to have them as pointers

  if (arrcarry1 == NULL || arrcarry2 == NULL)
    return DAF_RET_ERR_ALLOC;

  // summing each pair of uint30_t individually
  for (size_t i = 0; i < DAF_LIMB_SIZE; ++i)
  {
    if (i < uint30_dec)
    {
      daf_ten_9_add(&(*rop)[i], op1_bott[i], op2[i]);
    }
    else
    {
      daf_ten_9_add(&(*rop)[i], op1_top[i + uint30_dec], op2[i]);
    }
    if (DAF_ADD_GET_CARRY((*rop)[i]) == 1)
      DAF_ADD_SET_REM_BIT(arrcarry1, i + 1);

    ;
    printf("rop[%" PRIu8 "] = " PRINTF_BINARY_PATTERN_INT32 "\n", i, PRINTF_BYTE_TO_BINARY_INT32((*rop)[i]));
  }

  uint8_t run = 1;
  while (run)
  {
    // the (i + 1) are because the i's start from 0 and not from 1
    for (size_t i = 0; i < (DAF_LIMB_SIZE - 1); ++i)
    {
      if (DAF_ADD_GET_REM_BIT(arrcarry1, i + 1))
      {
        // if there will not be an owerflow then apply the carry
        if ((*rop)[i] < TEN_9_MAX)
          DAF_ADD_CLR_REM_BIT(arrcarry1, i + 1), ((*rop)[i])++;
        else // else set the carry for the next value and reset the uint64_t to 0
          DAF_ADD_SET_REM_BIT(arrcarry2, i + 2), ((*rop)[i]) = 0;
      }
    }

    // if the biggest uint64_t of the limb is at max and there is a carry, the overflow goes into the rem return value to hpcp_add
    // and the largest uint64_t is set to 0
    if (((*rop)[DAF_LIMB_SIZE - 1] >= TEN_9_MAX) && DAF_ADD_GET_REM_BIT(arrcarry1, DAF_LIMB_SIZE))
      *carry = 1, (*rop)[DAF_LIMB_SIZE - 1] = 0;

    // suppose that there is no more carry
    run = 0;

    // reset the carry array n°1 that has allready been used to 0 and check if the second array contains any non zero value
    for (uint8_t i = 0; i < ((size_t)(DAF_LIMB_SIZE / 8)) + 1; ++i)
    {
      arrcarry1[i] = 0;
      if (arrcarry2[i])
      // if the second carry array does contain non-zero element(s) then keep running and skip the swaping of the arrays
      {
        run = 1;
        continue;
      }
    }

    swap_ptr_uint8(&arrcarry1, &arrcarry2);
  }

  return DAF_RET_SUCESS;
}

/*function that add two const hpcp_t passed as refs (op1_ref and op2_ref) and sets the result into an another hpcp_t ref (rop_ref)*/
daf_ret_t daf_add(daf_ref_t rop_ref, daf_ref_t op1_ref, daf_ref_t op2_ref)
{
  DAF_GET_PTR(rop);
  daf_t *op1, *op2;
  if (DAF_GET(op1_ref, exp) >= DAF_GET(op2_ref, exp))
  {
    op1 = all_daf[op1_ref];
    op2 = all_daf[op2_ref];
  }
  else
  {
    op2 = all_daf[op1_ref];
    op1 = all_daf[op2_ref];
  }

  rop->head = 0;

  if (DAF_IS_INT(op1_ref) && DAF_IS_INT(op2_ref))
  {
    rop->head |= DAF_HEAD_INT;

    if (DAF_IS_ZERO(op1_ref) && DAF_IS_ZERO(op2_ref))
    {
      if (DAF_IS_POS(op1_ref) && DAF_IS_POS(op2_ref))
      {
        daf_set_plus_zero(rop_ref);
        return DAF_RET_SUCESS;
      }
    }
  }

  if (DAF_IS_NaN(op1_ref) || DAF_IS_NaN(op2_ref))
  {
    daf_set_NaN(rop_ref);
    return DAF_RET_SUCESS;
  }

  if (DAF_IS_INF(op1_ref) || DAF_IS_INF(op2_ref))
  {
    if (DAF_IS_POS(op1_ref) && DAF_IS_POS(op2_ref))
    {
      daf_set_plus_inf(rop_ref);
      return DAF_RET_SUCESS;
    }
    else if (!DAF_IS_POS(op1_ref) && !DAF_IS_POS(op2_ref))
    {
      daf_set_minus_inf(rop_ref);
      return DAF_RET_SUCESS;
    }
    daf_set_plus_zero(rop_ref);
    return DAF_RET_SUCESS;
  }

  // using a bit field to store all of the remainders of the sums
  uint8_t arrcarry1_arr[((uint64_t)(DAF_LIMB_SIZE / 8)) + 1],
      arrcarry2_arr[((uint64_t)(DAF_LIMB_SIZE / 8)) + 1];

  uint8_t *arrcarry1 = arrcarry1_arr;
  uint8_t *arrcarry2 = arrcarry2_arr;

  // the number of limbs used by the return operand (rop)
  const uint64_t max_limb_numb = ((rop->prec + rop->real_prec_dec) - sizeof(daf_limb_t)) / sizeof(daf_limb_t);

  // loading all of the mantissa of the operands

  daf_load_mantissa(op1_ref);
  daf_load_mantissa(op2_ref);
  daf_load_mantissa(rop_ref);

  const uint64_t dec = op1->exp - op2->exp;             // the number of uint30_t that the two operands are offseted by to each other
  const uint64_t limb_dec = dec / DAF_LIMB_SIZE;        // the number of limbs that the two operands are offseted by to each other
  const uint64_t uint30_limb_dec = dec % DAF_LIMB_SIZE; // the number of uint30_t in a limbs that the two operands are offseted by to each other

  // add the limbs in pair for the start of both op's
  uint8_t carry;
  if (dec <= DAF_LIMB_SIZE)
    daf_limb_add(&carry, rop->start, *(op1->start), *(op1->loaded_mtsa[0]), *(op2->start), dec);
  else
    daf_limb_add(&carry, rop->start, *(op1->start), *(op1->loaded_mtsa[0]), *(op2->loaded_mtsa[limb_dec]), uint30_limb_dec);

  if (carry == 1)
    DAF_ADD_SET_REM_BIT(arrcarry1, 1);

  for (size_t i = 0; i < max_limb_numb; ++i)
  {
    (rop->loaded_mtsa)[i] = malloc(sizeof(daf_limb_t));
    if (i > limb_dec)
      daf_limb_add(&carry, (rop->loaded_mtsa)[i], *(op1->loaded_mtsa[i]), *(op1->loaded_mtsa[i + 1]), *(op2->loaded_mtsa[i + limb_dec - 1]), uint30_limb_dec);
    else if (i == limb_dec)
      daf_limb_add(&carry, rop->loaded_mtsa[i], *(op1->loaded_mtsa[i]), *(op1->loaded_mtsa[i + 1]), *(op2->start), uint30_limb_dec);
    else
    {
      for (uint8_t j = 0; j < DAF_LIMB_SIZE; ++j)
      {
        if (j < uint30_limb_dec)
          (*(rop->loaded_mtsa[i]))[j] = (*(op1->loaded_mtsa[i]))[j];
        else
          (*(rop->loaded_mtsa[i]))[j] = (*(op1->loaded_mtsa[i + 1]))[j];
      }
    }
    if (carry == 1)
      DAF_ADD_SET_REM_BIT(arrcarry1, i + 1);
  }
  uint8_t run = 1;

  while (run)
  {
    for (uint64_t i = 0; i < max_limb_numb; ++i)
    {
      uint8_t limb_i_is_max = 0;
      for (size_t j = 0; j < DAF_LIMB_SIZE; ++j)
        if ((((*(rop->loaded_mtsa))[i])[j]) == TEN_9_MAX)
        {
          limb_i_is_max = 1;
          break;
        }

      // check if rop is at max if not then do add the remaider
      if (limb_i_is_max == 0)
      {
        daf_limb_pp(&(*(rop->loaded_mtsa))[i + 1]);
        DAF_ADD_CLR_REM_BIT(arrcarry1, i + 1);
      }
      else
      {
        DAF_ADD_SET_REM_BIT(arrcarry2, i + 2);
        daf_limb_set_zero(&(*(rop->loaded_mtsa))[i]);
      }
    }
    // suppose that there is no more carry
    run = 0;

    // reset the carry array n°1 that has allready been used to 0 and check if the second array contains any non zero value
    for (uint8_t i = 0; i < ((size_t)(DAF_LIMB_SIZE / 8)) + 1; ++i)
    {
      arrcarry1[i] = 0;
      if (arrcarry2[i])
      // if the second carry array does contain non-zero element(s) then keep running and skip the swaping of the arrays
      {
        run = 1;
        continue;
      }
    }

    swap_ptr_uint8(&arrcarry1, &arrcarry2);
  }

  return DAF_RET_SUCESS;

#undef DAF_ADD_GET_REM_BIT
#undef DAF_ADD_SET_REM_BIT
#undef DAF_ADD_CLR_REM_BIT
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
    printf(PRINTF_ERROR "error while trying to create '%s'\n", path);
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

void swap_ptr_uint8(uint8_t **const a, uint8_t **const b)
{
  uint8_t *c = *a;
  *a = *b;
  *b = c;
  return;
}