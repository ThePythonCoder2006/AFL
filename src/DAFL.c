#include <stdlib.h>
#include <stdio.h>

#include "DAFL.h"

uint64_t nb_daf = 0;

uint8_t all_daf_already_init = 0;
daf_t **all_daf;

daf_ret_t init_all_daf(void)
{
  if (!all_daf_already_init)
  {
    all_daf = calloc(10, sizeof(daf_t *));
  }
  return DAF_RET_SUCESS;
}

daf_ret_ref_t daf_init(uint64_t prec)
{
  init_all_daf();

  daf_ret_ref_t ref = nb_daf;

  all_daf[ref]->exp = 0;
  all_daf[ref]->prec = prec;
  all_daf[ref]->real_prec_dec = TEN_9_DECIMAL_SIZE - (prec % TEN_9_DECIMAL_SIZE);
  all_daf[ref]->head = DAF_HEAD_INT | DAF_HEAD_ZERO;
  return ref++;
}