#ifndef __DAFL_PRINT__
#define __DAFL_PRINT__

#include "DAFL.h"

daf_ret_t daf_primitive_out_file_string(FILE *stream, char *buff, const uint64_t n, daf_ref_t op_ref, uint64_t prec, const uint8_t grp);
daf_ret_t daf_primitive_vnprint(FILE *stream, char *const buff, const uint64_t n, const char *fmt, va_list args);

static inline daf_ret_t daf_vfprintf(FILE *stream, const char *fmt, va_list args) { return daf_primitive_vnprint(stream, NULL, UINT64_MAX, fmt, args); }
static inline daf_ret_t daf_vprintf(const char *fmt, va_list args) { return daf_vfprintf(stdout, fmt, args); }
static inline daf_ret_t daf_fprintf(FILE *stream, const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	daf_ret_t ret = daf_vfprintf(stream, fmt, args);
	va_end(args);
	return ret;
}
static inline daf_ret_t daf_eprintf(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	daf_ret_t ret = daf_vfprintf(stderr, fmt, args);
	va_end(args);
	return ret;
}
static inline daf_ret_t daf_printf(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	daf_ret_t ret = daf_vprintf(fmt, args);
	va_end(args);
	return ret;
}

static inline daf_ret_t daf_vsnprintf(char *buff, const uint64_t n, const char *fmt, va_list args) { return daf_primitive_vnprint(NULL, buff, n, fmt, args); }
static inline daf_ret_t daf_vsprintf(char *buff, const char *fmt, va_list args) { return daf_vsnprintf(buff, UINT64_MAX, fmt, args); };
static inline daf_ret_t daf_snprintf(char *buff, const uint64_t n, const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	daf_ret_t ret = daf_vsnprintf(buff, n, fmt, args);
	va_end(args);
	return ret;
}
static inline daf_ret_t daf_sprintf(char *buff, const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	daf_ret_t ret = daf_vsnprintf(buff, UINT64_MAX, fmt, args);
	va_end(args);
	return ret;
}

#endif // __DAFL_PRINT__