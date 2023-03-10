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

#include "DAFL_macros.h"
#include "DAFL_types.h"
#include "DAFL_add.h"

extern uint64_t nb_daf;

extern uint8_t all_daf_already_init;
extern daf_t **all_daf;

extern const char *const(err_message)[DAF_ERR_COUNT];

/*-------------------------------start functions-------------------------------*/

// daf_ret_t daf_load_mantissa(daf_ref_t ref);

// init functions
daf_ret_ref_t daf_init(uint64_t prec);

// clear functions
daf_ret_t daf_clear(daf_ref_t op_ref);

// print functions
daf_ret_t daf_primitive_out_file_string(FILE *stream, char *buff, const uint64_t n, daf_ref_t op_ref, uint64_t prec);
daf_ret_t daf_primitive_vnprint(FILE *stream, char *const buff, const uint64_t n, const char *fmt, va_list args);

static inline daf_ret_t daf_vfprintf(FILE *stream, const char *fmt, va_list args) { return daf_primitive_vnprint(stream, NULL, UINT64_MAX, fmt, args); }
static inline daf_ret_t daf_vprintf(const char *fmt, va_list args) { return daf_vfprintf(stdout, fmt, args); }
static inline daf_ret_t daf_fprintf(FILE *stream, const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	return daf_vfprintf(stream, fmt, args);
}
static inline daf_ret_t daf_eprintf(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	return daf_vfprintf(stderr, fmt, args);
}
static inline daf_ret_t daf_printf(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	return daf_vprintf(fmt, args);
}

static inline daf_ret_t daf_vsnprintf(char *buff, const uint64_t n, const char *fmt, va_list args) { return daf_primitive_vnprint(NULL, buff, n, fmt, args); }
static inline daf_ret_t daf_vsprintf(char *buff, const char *fmt, va_list args) { return daf_vsnprintf(buff, UINT64_MAX, fmt, args); };
static inline daf_ret_t daf_snprintf(char *buff, const uint64_t n, const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	return daf_vsnprintf(buff, n, fmt, args);
};
static inline daf_ret_t daf_sprintf(char *buff, const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	return daf_vsnprintf(buff, UINT64_MAX, fmt, args);
};

size_t daf_get_filename(char filename[64], daf_ref_t op_ref);

daf_ret_t daf_debug_out(daf_ref_t op_ref, const char *const name);

// set functions ------------------------------------------------------
daf_ret_t daf_limb_set_zero(daf_limb_t *rop);

daf_ret_t daf_set_plus_zero(daf_ref_t op_ref);
daf_ret_t daf_set_minus_zero(daf_ref_t op_ref);
daf_ret_t daf_set_NaN(daf_ref_t op_ref);
daf_ret_t daf_set_plus_inf(daf_ref_t op_ref);
daf_ret_t daf_set_minus_inf(daf_ref_t op_ref);

daf_ret_t daf_set_ui(daf_ref_t rop_ref, uint64_t op);

// arthimetric functions ------------------------------------------------------
daf_ret_t daf_negate(daf_ref_t rop_ref, daf_ref_t op_ref);

// file functions
void rek_mkdir(const char *const path);
FILE *fopen_mkdir(const char *const path, const char *const mode);

void swap_ptr_uint8(uint8_t **const a, uint8_t **const b);

/*-------------------------------end functions-------------------------------*/

#endif //__DAFL__