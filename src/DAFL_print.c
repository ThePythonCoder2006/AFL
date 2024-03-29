#include "DAFL_print.h"

#ifdef _DEBUG
#define BEFORE_PRINT PRINTF_RED
#define AFTER_PRINT PRINTF_RESET
#else
#define BEFORE_PRINT
#define AFTER_PRINT
#endif

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
		fprintf(stream, BEFORE_PRINT str AFTER_PRINT, __VA_ARGS__);

daf_ret_t daf_primitive_vnprint(FILE *stream, char *buff, const uint64_t n, const char *fmt, va_list args)
{
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
				putc(curr, stream);
			++printed_chars;

			if (printed_chars >= n && n != UINT64_MAX)
				return DAF_RET_SUCESS;

			continue;
		}

		if (*(++fmt) == 'D')
		{
			uint8_t is_grp = 0;
		switch_l:
			switch (*(++fmt))
			{
			case 'F':
				++fmt;
				if (sn)
					daf_primitive_out_file_string(NULL, buff, n - printed_chars,
																				(daf_ref_t)va_arg(args, daf_ref_t),
																				((n - printed_chars) - ((n - printed_chars) % TEN_9_DECIMAL_SIZE)) / TEN_9_DECIMAL_SIZE,
																				is_grp);
				else
					daf_primitive_out_file_string(stream, NULL, UINT64_MAX, (daf_ref_t)va_arg(args, daf_ref_t), (n - printed_chars), is_grp);

				printed_chars += n - printed_chars;

				if (printed_chars >= n && n != UINT64_MAX)
					return DAF_RET_SUCESS;

				break;

			case 'g':
				is_grp = 1;
				goto switch_l;
				break;

			default:
				break;
			}
		}
		else
		{
			TODO;
			return DAF_RET_ERR_NOT_IMPLEMENTED;

			const char modif = *(fmt++);
			if (modif == '%')
			{
				if (sn)
					strncat(buff, "%", 1);
				else
					putc('%', stream);
				continue;
			}

			const char tmp[16] = {'%', modif, 0};
			if (sn)
			{
				const uint8_t len = 64;
				char tmp_buff[len];
				vsnprintf(tmp_buff, sizeof(tmp_buff), tmp, args);
				strncat(buff, tmp_buff, len);
				printed_chars += len;
			}
			else
				printed_chars += vfprintf(stream, tmp, args);
		}
	}

	return DAF_RET_SUCESS;
}

daf_ret_t daf_primitive_out_file_string(FILE *stream, char *buff, const uint64_t n, daf_ref_t op_ref, uint64_t prec, const uint8_t grp)
{
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

	// daf_ret_t err;
	// if ((err = daf_load_mantissa(op_ref)) != DAF_RET_SUCESS)
	// 	return err;

	uint64_t printed_chars = 0;
	uint64_t printed_ten_9 = 0;

	for (uint64_t i = 0; i < (op->prec + op->real_prec_dec - 2); ++i)
	{
		if (i == 0)
		{
			out_args("%" PRIu32, DAF_MTSA_NTH(op_ref, 0));
			++printed_chars;
		}
		else
		{
			out_args("%c", grp ? ' ' : 0);
			out_args("%09" PRIu32, DAF_MTSA_NTH(op_ref, i));
			printed_chars += 9;
		}

		++printed_ten_9;

		if (printed_chars >= n && n != UINT64_MAX)
			return DAF_RET_SUCESS;

		if (printed_ten_9 >= prec || printed_ten_9 >= op->prec + op->real_prec_dec)
			return DAF_RET_SUCESS;

		if (DAF_IS_INT(op_ref) && printed_ten_9 > op->exp)
			return DAF_RET_SUCESS;

		if (printed_ten_9 == op->exp + 1)
		{
			if (sn)
				strncat(buff, &sep, 1);
			else
				putchar(sep);
			continue;
		}
	}
	return DAF_RET_SUCESS;

#undef out_str
#undef out_args
}
