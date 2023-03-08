#include "DAFL.h"

uint64_t nb_daf = 0;

uint8_t all_daf_already_init = 0;
daf_t **all_daf = NULL;

char *(err_message)[DAF_ERR_COUNT] = {
		PRINTF_SUCESS " everything appended as intended",
		PRINTF_ERROR " failed to allocated some memory",
		PRINTF_ERROR " failed to read the file containing the float's mantissa",
		PRINTF_ERROR " the float you passed in is invalid",
		PRINTF_ERROR " this funcitonnality is not (yet) implemented"};

daf_ret_t daf_load_mantissa(daf_ref_t op_ref)
{
	fprintf(stderr, PRINTF_ERROR "working with mtsa in files is not allowed for now !\n");
	assert(0 && "Illegal");

	DAF_GET_PTR(op);

	if (op->loaded_mtsa != NULL)
		return DAF_RET_SUCESS;

	uint64_t mtsa_size = op->prec + op->real_prec_dec;

	char filename[64];
	daf_get_filename(filename, op_ref);
	FILE *fmantissa = fopen(filename, "rb");

	if (fmantissa == NULL)
	{
		fprintf(stderr, PRINTF_ERROR " could not open the file \"%s\" of the mantissa of the daf with ref %" PRIu64 "\n", filename, op_ref);
		return DAF_RET_ERR_READ_FILE;
	}

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
	fprintf(stderr, PRINTF_ERROR "working with mtsa in files is not allowed for now !\n");
	assert(0);

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

daf_ret_t daf_set_mtsa_zero(daf_ref_t op_ref)
{
	DAF_GET_PTR(op);

	for (uint64_t i = 0; i < op->prec + op->real_prec_dec; ++i)
		DAF_MTSA_NTH(op_ref, i) = 0;

	return DAF_RET_SUCESS;
}

// init functions

daf_ret_t init_all_daf(void)
{
	if (!all_daf_already_init)
	{
		// printf("%i\n", all_daf_already_init);
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

	all_daf[ref]->exp = 0ULL;
	all_daf[ref]->prec = prec;
	all_daf[ref]->real_prec_dec = DAF_LIMB_SIZE - prec % DAF_LIMB_SIZE;
	all_daf[ref]->head = DAF_HEAD_INT | DAF_HEAD_ZERO;

	// allocated the mantissa.

	all_daf[ref]->loaded_mtsa = calloc((prec + all_daf[ref]->real_prec_dec) / DAF_LIMB_SIZE, sizeof(daf_t *));
	if (all_daf[ref]->loaded_mtsa == NULL)
		return DAF_RET_ERR_ALLOC;
	for (uint64_t i = 0; i < (prec + all_daf[ref]->real_prec_dec) / DAF_LIMB_SIZE; ++i)
	{
		all_daf[ref]->loaded_mtsa[i] = calloc(DAF_LIMB_SIZE, sizeof(uint30_t));
		if (all_daf[ref]->loaded_mtsa[i] == NULL)
			return DAF_RET_ERR_ALLOC;
	}

	daf_set_mtsa_zero(ref);

	return ref;
}

// clear functions

daf_ret_t daf_clear(daf_ref_t op_ref)
{
	DAF_GET_PTR(op);
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

	// daf_ret_t err;
	// if ((err = daf_load_mantissa(op_ref)) != DAF_RET_SUCESS)
	// 	return err;

	uint64_t printed_ten_9 = 1;

	out_args("%" PRIu32, DAF_MTSA_NTH(op_ref, 0));

	for (uint64_t i = 1; i < op->prec + op->real_prec_dec - DAF_LIMB_SIZE; ++i)
	{
		out_args(" %09" PRIu32, DAF_MTSA_NTH(op_ref, i));

		printed_chars += 9;
		if (printed_chars >= n && n != UINT64_MAX)
			return DAF_RET_SUCESS;

		if (printed_ten_9 >= prec || printed_ten_9 >= op->prec + op->real_prec_dec)
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

daf_ret_t daf_debug_out(daf_ref_t op_ref, const char *const name)
{
	printf("%s\n", name);

	DAF_GET_PTR(op);

	printf("|- head : %" PRIu8 " : %c ; %s ; %s ; %s ; %s ; %s\n", op->head,
				 DAF_IS_POS(op_ref) ? '+' : '-',
				 DAF_IS_ZERO(op_ref) ? "0" : "!= 0",
				 DAF_IS_INF(op_ref) ? "Inf" : "finite",
				 DAF_IS_NaN(op_ref) ? "NaN" : "aN",
				 !((op->head | DAF_HEAD_EXP_MINUS) == op->head) ? "| | < 1" : "| | >= 1",
				 DAF_IS_INT(op_ref) ? "Int" : "Float");

	printf("|- exp : %" PRIu64 "\n", op->exp);
	printf("|- prec : %" PRIu64 "\n", op->prec);
	printf("|- reak_prec_dec : %" PRIu8 "\n", op->real_prec_dec);
	printf("|- loaded_mtsa : 0x%p\n", op->loaded_mtsa);

	printf("\t|- *loaded_mtsa : 0x%p\n", *(op->loaded_mtsa));
	for (uint64_t i = 0; i < (op->prec + op->real_prec_dec) / DAF_LIMB_SIZE; ++i)
	{
		printf("\t\t|- *(loaded_mtsa)[%" PRIu64 "] : 0x%p\n\t\t\t|- [%u", i, (*(op->loaded_mtsa))[i], ((*(op->loaded_mtsa))[i])[0]);
		for (uint8_t j = 1; j < DAF_LIMB_SIZE; ++j)
		{
			printf(", %u", ((*(op->loaded_mtsa))[i])[j]);
		}
		printf("]\n");
	}

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

	return daf_set_file_mantissa_zero(op_ref);
}

daf_ret_t daf_set_minus_zero(daf_ref_t op_ref)
{
	DAF_GET_PTR(op);

	op->head = DAF_HEAD_ZERO | DAF_HEAD_INT | DAF_HEAD_MINUS;
	op->exp = 0;

	return daf_set_file_mantissa_zero(op_ref);
}

daf_ret_t daf_set_NaN(daf_ref_t op_ref)
{
	DAF_GET_PTR(op);

	op->head = DAF_HEAD_NaN;
	op->exp = 0;

	return daf_set_file_mantissa_zero(op_ref);
}

daf_ret_t daf_set_plus_inf(daf_ref_t op_ref)
{
	DAF_GET_PTR(op);

	op->head = DAF_HEAD_INF;
	op->exp = UINT64_MAX;

	return daf_set_file_mantissa_zero(op_ref);
}

daf_ret_t daf_set_minus_inf(daf_ref_t op_ref)
{
	DAF_GET_PTR(op);

	op->head = DAF_HEAD_INF | DAF_HEAD_MINUS;
	op->exp = UINT64_MAX;

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
	p3 = (((tmp / (TEN_9_MAX + 1)) - p2) / (TEN_9_MAX + 1)) % (TEN_9_MAX + 1);

	DAF_GET_PTR(rop);
	rop->head = DAF_HEAD_INT;

	daf_set_mtsa_zero(rop_ref);

	if (p3 == 0)
	{
		if (p2 == 0)
		{
			rop->exp = 0;
			DAF_MTSA_NTH(rop_ref, 0) = p1;
			return DAF_RET_SUCESS;
		}
		rop->exp = 1;
		DAF_MTSA_NTH(rop_ref, 1) = p1;
		DAF_MTSA_NTH(rop_ref, 0) = p2;
		return DAF_RET_SUCESS;
	}

	rop->exp = 2;
	DAF_MTSA_NTH(rop_ref, 2) = p1;
	DAF_MTSA_NTH(rop_ref, 1) = p2;
	DAF_MTSA_NTH(rop_ref, 0) = p3;

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