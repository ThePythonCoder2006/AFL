#pragma once
#ifndef __DAFL__
#define __DAFL__

#include <stdint.h>
#include <inttypes.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <float.h>
#include <assert.h>

#ifdef _WIN32
#include <io.h>
#define F_OK 0
#define access _access
#endif

#include "DAFL_consts.h"
#include "DAFL_macros.h"
#include "DAFL_types.h"
#include "DAFL_set.h"
#include "DAFL_add.h"
#include "DAFL_print.h"

/* extern variables */

extern uint64_t nb_daf;

extern uint8_t all_daf_already_init;
extern daf_t **all_daf;

extern const char *const(err_message)[DAF_ERR_COUNT];

/*-------------------------------start functions-------------------------------*/

// daf_ret_t daf_load_mantissa(daf_ref_t ref);

daf_ret_ref_t daf_init(uint64_t prec);

daf_ret_t daf_clear(daf_ref_t op_ref);

size_t daf_get_filename(char filename[64], daf_ref_t op_ref);

daf_ret_t daf_debug_out(daf_ref_t op_ref, const char *const name);

// set functions ------------------------------------------------------
daf_ret_t daf_copy(daf_ref_t rop_ref, daf_ref_t op_ref);

// arthimetric functions ------------------------------------------------------
daf_ret_t daf_negate(daf_ref_t rop_ref, daf_ref_t op_ref);
daf_ret_t daf_ror(daf_ref_t rop_ref, daf_ref_t op_ref);

// file functions
void rek_mkdir(const char *const path);
FILE *fopen_mkdir(const char *const path, const char *const mode);

void swap_ptr_uint8(uint8_t **const a, uint8_t **const b);

/*-------------------------------end functions-------------------------------*/

#endif //__DAFL__