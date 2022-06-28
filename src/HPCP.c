#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <string.h>
#include <HPCP.h>
#include <time.h>
#include <stdarg.h>

#ifdef _WIN32
#include <io.h>
#define F_OK 0
#define access _access
#endif

#define TMPPATH "bin/tmp"

#define HPCP_ALL_NUMBS_ORG_SIZE 15

#define ALLOC_ALL_HPCP_LIMBS                                                                 \
  if (all_hpcp_floats == NULL)                                                               \
  {                                                                                          \
    fprintf(stderr, PRINTF_YELLOW "[ERROR] you should use hpcp_global_init()" PRINTF_RESET); \
    all_hpcp_floats = calloc(sizeof(hpcp_t *), HPCP_ALL_NUMBS_ORG_SIZE);                     \
    if (all_hpcp_floats == NULL)                                                             \
      return HPCP_ERR_RET_ALLOC;                                                             \
  }

#define HPCP_CHECK_FLOAT(ref)              \
  if (ref > UINT64_MAX - HPCP_REF_MAX_DEC) \
  return HPCP_ERR_RET_INVALID_FLOAT

/*
dynamicaly allocated array of pointers to hpcp_t
*/
hpcp_t **all_hpcp_floats = NULL;
uint64_t nb_hpcp_floats = 0;

#define HPCP_GET_PTR(op) hpcp_t *op = all_hpcp_floats[op##_ref]

int hpcp_set_file_mantissa_zero(hpcp_ref_t op_ref)
{
  HPCP_GET_PTR(op);

  if (op->prec < sizeof(hpcp_limb_t))
    return 0;

  const uint64_t binmax = (op->prec - sizeof(hpcp_limb_t)) + op->real_prec_dec;

  printf("binmax : %" PRIu64 "\n", binmax);

  char filename[64];
  sprintf(filename, TMPPATH "/HPCP-%" PRIu64 ".bin", op_ref);

  FILE *bin = fopen_mkdir(filename, "wb");
  if (bin == NULL)
    return HPCP_ERR_RET_READ_FILE;

  const hpcp_limb_t buff = {0x00};

  for (uint64_t i = 0; i < binmax / sizeof(hpcp_limb_t); ++i)
    fwrite(&buff, sizeof(buff), 1, bin);

  fclose(bin);
  return 0;
}

/* - init functions -----------------------------------------------------------------------------*/

hpcp_ret_ref_t hpcp_init(const uint64_t prec)
{
  ALLOC_ALL_HPCP_LIMBS;
  // sprintf("%i\n", sizeof((*rop)->line));

  // printf("prec = %" PRIu64 " buff = 0x%" PRIx64 "\n", prec, buff);

  hpcp_t *rop = all_hpcp_floats[nb_hpcp_floats] = malloc(sizeof(hpcp_t));
  if (rop == NULL)
    return (hpcp_ref_t)HPCP_ERR_RET_ALLOC;

  rop->start = calloc(HPCP_LIMB_SIZE, sizeof(uint64_t));
  if (rop->start == NULL)
    return (hpcp_ret_ref_t)HPCP_ERR_RET_ALLOC;

  rop->exp = 0;
  rop->prec = prec;
  rop->head = HPCP_ZERO | HPCP_INT;
  rop->real_prec_dec = (sizeof(hpcp_limb_t)) - ((uint64_t)((prec) % sizeof(hpcp_limb_t)));
  if (prec <= sizeof(hpcp_limb_t))
    rop->real_prec_dec = 0;

  hpcp_set_file_mantissa_zero(nb_hpcp_floats);
  return nb_hpcp_floats++;
}

/* - end init functions ----------------------------------------------------------------------------*/

/* - setting functions -----------------------------------------------------------------------------*/

int hpcp_limb_set_ui(hpcp_limb_t rop, const uint64_t op)
{
  for (size_t i = 0; i < HPCP_LIMB_SIZE; ++i)
  {
    rop[i] = 0;
  }

  rop[HPCP_LIMB_SIZE - 1] = op;

  return 0;
}

int hpcp_set_ui(hpcp_ref_t rop_ref, const uint64_t op)
{
  HPCP_GET_PTR(rop);

  uint64_t fn_op = op;

  if (fn_op == 0)
    rop->head = HPCP_ZERO | HPCP_INT;
  else
    rop->head = HPCP_INT;

  uint64_t v = fn_op;
  uint8_t val = 0;

  while (v >>= 1) // unroll for more speed...
  {
    val++;
  }

  rop->exp = val;

  // printf("%" PRIu64 ", %" PRIu64 ", " PRINTF_BINARY_PATTERN_INT64 "\n", fn_op, NTH_BIT(fn_op, val), PRINTF_BYTE_TO_BINARY_INT64(fn_op));
  CLR_BIT(fn_op, val);

  fn_op <<= (64 - val);
  // printf("%" PRIu64 ", %" PRIu64 "\n", (uint64_t)(64 - val), (uint64_t)val);
  // printf(PRINTF_BINARY_PATTERN_INT64 "\n", PRINTF_BYTE_TO_BINARY_INT64(fn_op));
  (*(rop->start))[0] = fn_op;

  return hpcp_set_file_mantissa_zero(rop_ref);
}

int hpcp_set_plus_zero(hpcp_ref_t rop_ref)
{
  HPCP_GET_PTR(rop);

  rop->head = HPCP_ZERO | HPCP_INT;
  rop->exp = 0;

  for (uint8_t i = 0; i < HPCP_LIMB_SIZE; ++i)
    (*(rop->start))[i] = 0;

  return hpcp_set_file_mantissa_zero(rop_ref);
}

int hpcp_set_minus_zero(hpcp_ref_t rop_ref)
{
  HPCP_GET_PTR(rop);

  rop->head = HPCP_ZERO | HPCP_INT | HPCP_MINUS;
  rop->exp = 0;

  for (uint8_t i = 0; i < HPCP_LIMB_SIZE; ++i)
    (*(rop->start))[i] = 0;

  return hpcp_set_file_mantissa_zero(rop_ref);
}

int hpcp_set_NaN(hpcp_ref_t rop_ref)
{
  HPCP_GET_PTR(rop);

  rop->head = HPCP_NAN;
  rop->exp = 0;

  for (uint8_t i = 0; i < HPCP_LIMB_SIZE; ++i)
    (*(rop->start))[i] = 0;

  return hpcp_set_file_mantissa_zero(rop_ref);
}

int hpcp_set_plus_inf(hpcp_ref_t rop_ref)
{
  HPCP_GET_PTR(rop);

  rop->head = HPCP_INF;
  rop->exp = UINT64_MAX;

  for (uint8_t i = 0; i < HPCP_LIMB_SIZE; ++i)
    (*(rop->start))[i] = 0;

  return hpcp_set_file_mantissa_zero(rop_ref);
}

int hpcp_set_minus_inf(hpcp_ref_t rop_ref)
{
  HPCP_GET_PTR(rop);

  rop->head = HPCP_INF | HPCP_MINUS;
  rop->exp = UINT64_MAX;

  for (uint8_t i = 0; i < HPCP_LIMB_SIZE; ++i)
    (*(rop->start))[i] = 0;

  return hpcp_set_file_mantissa_zero(rop_ref);
}

/* - end setting functions -----------------------------------------------------------------------------*/
/* - print functions -----------------------------------------------------------------------------------*/

int hpcp_printf_bin_sci(hpcp_ref_t op_ref)
{
  HPCP_GET_PTR(op);

  if (HPCP_IS_NAN(op))
  {
    printf("NaN");
    return 0;
  }

  printf("%c", (op->head | HPCP_MINUS) == op->head ? '-' : 0);

  if (HPCP_IS_INF(op))
  {
    printf("Infinity");
    return 0;
  }

  if (HPCP_IS_ZERO(op))
  {
    printf("0");
    return 0;
  }

  printf("2^%c%" PRIu64 " x 1.", (op->head | HPCP_EXP_MINUS) == op->head ? '-' : 0, op->exp);
  for (uint8_t i = 0; i < HPCP_LIMB_SIZE; ++i)
    printf(PRINTF_BINARY_PATTERN_INT64, PRINTF_BYTE_TO_BINARY_INT64(((*(op->start))[i])));

  printf(PRINTF_BLUE "| " PRINTF_RESET);

  if (op->prec <= sizeof(hpcp_limb_t))
    return 0;

  char filename[64];
  hpcp_get_filename(filename, op_ref);
  FILE *bin = fopen(filename, "rb");
  uint64_t data;

  for (size_t i = 0; i < (((op->prec - sizeof(hpcp_limb_t)) + op->real_prec_dec) / sizeof(uint64_t)); ++i)
  {
    fread(&data, sizeof(data), 1, bin);
    printf(PRINTF_BINARY_PATTERN_INT64, PRINTF_BYTE_TO_BINARY_INT64(data));
    if ((i + 1) % HPCP_LIMB_SIZE == 0)
      printf(PRINTF_BLUE "| " PRINTF_RESET);
  }
  fclose(bin);
  return 0;
}

/* - end print functions -----------------------------------------------------------------------------*/
/* - arthrimetrics functions -----------------------------------------------------------------------------*/

int hpcp_div_2_ui(hpcp_ref_t rop_ref, hpcp_ref_t op_ref, const uint64_t dec)
{
  ALLOC_ALL_HPCP_LIMBS;
  HPCP_CHECK_FLOAT(op_ref);

  HPCP_GET_PTR(rop);
  HPCP_GET_PTR(op);

  uint64_t dec2 = dec;

  hpcp_copy(rop_ref, op_ref);

  rop->head &= ~(HPCP_INT);

  if (op->exp < dec2)
  {
    rop->exp = dec2 - op->exp;
    rop->head |= HPCP_EXP_MINUS;
    return 0;
  }
  if (op->head | HPCP_EXP_MINUS == op->head)
    dec2 = -dec;

  rop->exp = op->exp - dec2;
  rop->head &= ~(HPCP_EXP_MINUS);

  return 0;
}

/*a function that add two uint64_t (op1 and op2), sets the result into an another uint64_t passed as pointer (rop) and return the remaider of the addition*/
uint8_t hpcp_add_uint64(uint64_t *rop, const uint64_t op1, const uint64_t op2)
{
  // add the two operands and dont care if there is an overflow (it it detected id the if statement and taken care of)
  *rop = op1 + op2;
  return UINT64_MAX - op1 < op2;
}

/*a function that add two hpcp_limb_t passed as pointers (op1 and op2), sets the result into an another hpcp_limb_t passed as pointer (rop) and return the remaider of the addition, dec in bits*/
int8_t hpcp_add_limb(hpcp_limb_t *rop, const hpcp_limb_t op1_top, const hpcp_limb_t op1_bottom, const hpcp_limb_t op2, const uint16_t dec)
{
  // helper macros for the hpcp_add function for keeping the remaiders
#define HPCP_ADD_GET_REM_BIT(rem_var, N) (((rem_var)[(size_t)((N) / 8)] >> ((((N)-1) % 8))) & 1)
#define HPCP_ADD_SET_REM_BIT(rem_var, N) (((rem_var)[(size_t)((N) / 8)]) |= (1 << (((N)-1) % 8)))
#define HPCP_ADD_CLR_REM_BIT(rem_var, N) (((rem_var)[(size_t)((N) / 8)]) &= ~(1 << (((N)-1) % 8)))

  // this will be one if an only if the result of the sum is bigger than 2^(64*10) - 1
  // if the result doesn't fit in the 64*HPCP_LIMB_SIZE bits availible in hpcp_limb_t
  uint8_t rem = 0;

  // using an array to store all of the remainders of the sums : each bit represents a remainder
  // in binary a remainder can only be 0 or 1
  uint8_t *arrem1 = calloc(1, ((uint64_t)(HPCP_LIMB_SIZE / 8)) + 1),
          *arrem2 = calloc(1, ((uint64_t)(HPCP_LIMB_SIZE / 8)) + 1); // It's needed to calloc these to have them as pointers
  if (arrem1 == NULL || arrem2 == NULL)
    return HPCP_ERR_RET_ALLOC;

  // the number of uint64_t that wont need to be split before
  const uint8_t uint64_dec = (dec - (dec % sizeof(uint64_t))) / sizeof(uint64_t);

  const uint8_t bit_dec = dec % sizeof(uint64_t);
  const uint64_t mask = ((1ull << bit_dec) - 1);

  // summing each pair of uint64_t individually
  for (size_t i = 0; i < HPCP_LIMB_SIZE; ++i)
  {
    uint64_t nval = (op1_top[i + uint64_dec] & mask) | (op1_top[i + uint64_dec] & ~mask);
    if (hpcp_add_uint64(&(*rop)[i], nval, op2[i]))
      HPCP_ADD_SET_REM_BIT(arrem1, i + 1);
  }

  uint8_t run = 1;
  while (run)
  {
    // the (i + 1) are because the i's start from 0 and not from 1
    for (size_t i = 0; i < (HPCP_LIMB_SIZE - 1); ++i)
    {
      if (HPCP_ADD_GET_REM_BIT(arrem1, i + 1))
      {
        // if there will not be an owerflow then apply the remainder
        if ((*rop)[i] < UINT64_MAX)
          HPCP_ADD_CLR_REM_BIT(arrem1, i + 1), ((*rop)[i])++;
        else // else set the remainder for the next value and reset the uint64_t to 0
          HPCP_ADD_SET_REM_BIT(arrem2, i + 2), ((*rop)[i]) = 0;
      }
    }

    // if the biggest uint64_t of the limb is at max and there is a remainder, the overflow goes into the rem return value to hpcp_add
    // and the largest uint64_t is set to 0
    if (((*rop)[HPCP_LIMB_SIZE - 1] >= UINT64_MAX) && HPCP_ADD_GET_REM_BIT(arrem1, HPCP_LIMB_SIZE))
      rem = 1, (*rop)[HPCP_LIMB_SIZE - 1] = 0;

    // suppose that there is no more remainder
    run = 0;

    // reset the remainder array n°1 that has allready been used to 0 and check if the second array contains any non zero value
    for (uint8_t i = 0; i < ((size_t)(HPCP_LIMB_SIZE / 8)) + 1; ++i)
    {
      arrem1[i] = 0;
      if (arrem2[i])
      // if the second remainder array does contain non-zero element(s) then keep running and skip the swaping of the arrays
      {
        run = 1;
        continue;
      }
    }

    swap_ptr_uint8(&arrem1, &arrem2);
  }

  return rem;
}

/*function that add two const hpcp_t passed as pointers (op1 and op2) and sets the result into an another hpcp_t pointer (rop)*/
int hpcp_add(hpcp_ref_t rop_ref, hpcp_ref_t op1_ref, hpcp_ref_t op2_ref)
{
  ALLOC_ALL_HPCP_LIMBS;

  HPCP_CHECK_FLOAT(op1_ref);
  HPCP_CHECK_FLOAT(op2_ref);

  HPCP_GET_PTR(rop);
  HPCP_GET_PTR(op1);
  HPCP_GET_PTR(op2);

  // using an array to store all of the remainders of the sums : each bit represents a remainder
  // in binary a remainder can only be 0 or 1
  uint8_t arrem1_arr[((uint64_t)(HPCP_LIMB_SIZE / 8)) + 1],
      arrem2_arr[((uint64_t)(HPCP_LIMB_SIZE / 8)) + 1]; // It is needed to calloc these to have them as pointers

  uint8_t *arrem1 = arrem1_arr;
  uint8_t *arrem2 = arrem2_arr;

  hpcp_limb_t *ropstart = rop->start, *op1start = op1->start, *op2start = op2->start;

  // the number of limbs used by the return operand (rop)
  const uint64_t max_limb_numb = ((rop->prec + rop->real_prec_dec) - sizeof(hpcp_limb_t)) / sizeof(hpcp_limb_t);

  rop->loaded_mantissa = calloc(sizeof(hpcp_limb_t *), max_limb_numb);

  // open all of the file containing the mantissas of the operands
  char filename[64];

  hpcp_get_filename(filename, op1_ref);
  FILE *op1bin;
  OPEN_FILE_OR_PANIC(filename, "rb", op1bin);

  hpcp_get_filename(filename, op2_ref);
  FILE *op2bin;
  OPEN_FILE_OR_PANIC(filename, "rb", op2bin);

  const uint32_t limb_dec = (dec - (dec % sizeof(hpcp_limb_t)));

  // add the limbs in pair for the start of both op's
  if (hpcp_add_limb(ropstart, *op1start, *op2start, limb_dec) == 1)
    HPCP_ADD_SET_REM_BIT(arrem1, 1);

  hpcp_limb_t tmpop1, tmpop2;
  for (size_t i = 0; i < max_limb_numb; ++i)
  {
    (rop->loaded_mantissa)[i] = malloc(sizeof(hpcp_limb_t));

    fread(&tmpop1, sizeof(tmpop1), 1, op1bin);
    fread(&tmpop2, sizeof(tmpop2), 1, op2bin);
    if (hpcp_add_limb((rop->loaded_mantissa)[i], tmpop1, tmpop2) == 1)
      HPCP_ADD_SET_REM_BIT(arrem1, i + 1);

    int limb_i_is_max = 0;
    for (size_t j = 0; j < HPCP_LIMB_SIZE; ++j)
      if ((*((rop->loaded_mantissa)[i])[j]) == UINT64_MAX)
      {
        limb_i_is_max = 1;
        break;
      }

    hpcp_limb_t limb_one;
    hpcp_limb_set_ui(limb_one, 1);

    // check if rop is at max if not then do add the remaider
    if (limb_i_is_max == 0)
    {
      hpcp_add_limb((rop->loaded_mantissa)[i], *((rop->loaded_mantissa)[i]), limb_one);
      HPCP_ADD_CLR_REM_BIT(arrem1, i + 1);
    }

    printf("%i\n", i);
  }
  // open rop's mantissa only when needing to save
  hpcp_get_filename(filename, rop_ref);
  FILE *ropbin;
  OPEN_FILE_OR_PANIC(filename, "wb", ropbin);

  for (size_t i = 0; i < max_limb_numb; ++i)
  {
    fwrite((rop->loaded_mantissa)[i], sizeof(hpcp_limb_t), 1, ropbin);
  }

  fclose(ropbin);
  fclose(op1bin);
  fclose(op2bin);

  for (size_t i = 0; i < max_limb_numb; ++i)
    free(*((rop->loaded_mantissa)[i]));

  free((rop->loaded_mantissa));

  return 0;

#undef HPCP_ADD_GET_REM_BIT
#undef HPCP_ADD_SET_REM_BIT
#undef HPCP_ADD_CLR_REM_BIT
}

inline int hpcp_negate(hpcp_ref_t rop_ref, hpcp_ref_t op_ref)
{
  hpcp_t *rop = all_hpcp_floats[rop_ref], *op = all_hpcp_floats[op_ref];

  rop->head = op->head ^ HPCP_MINUS;

  return 0;
}

/* - end arthrimetrics functions -----------------------------------------------------------------------------*/

void hpcp_clear(hpcp_ref_t rop_ref)
{
  HPCP_GET_PTR(rop);
  free(*(rop->start));
  char filename[64];
  hpcp_get_filename(filename, rop_ref);
  printf("%s\n", filename);
  remove(filename);
  free((void *)rop);
  all_hpcp_floats[rop_ref] = NULL;
  return;
}

int hpcp_copy(hpcp_ref_t dst_ref, hpcp_ref_t src_ref)
{
  // hpcp_t *dst = all_hpcp_floats[dst_ref], *src = all_hpcp_floats[src_ref];
  HPCP_GET_PTR(dst);
  HPCP_GET_PTR(src);

  dst->exp = src->exp;
  dst->prec = src->prec;
  dst->head = src->head;
  dst->start = src->start;
  dst->real_prec_dec = src->real_prec_dec;

  char filename[64];
  hpcp_get_filename(filename, src_ref);
  FILE *srcbin = fopen(filename, "rb");
  hpcp_get_filename(filename, dst_ref);
  FILE *dstbin = fopen(filename, "wb");

  if (srcbin == NULL || dstbin == NULL)
    return HPCP_ERR_RET_READ_FILE;

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

size_t hpcp_get_filename(char filename[64], hpcp_ref_t op_ref)
{
  return sprintf(filename, TMPPATH "/HPCP-%" PRIu64 ".bin", op_ref);
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

// general purpuse stuff -------------------------------------------------

inline int64_t abs2(const int64_t op)
{
  int const mask = op >> ((sizeof(int) * 8) - 1);

  return (op + mask) ^ mask;
}

void swap_ptr_uint8(uint8_t **const a, uint8_t **const b)
{
  uint8_t *c = *a;
  *a = *b;
  *b = c;
  return;
}