#include "DAFL.h"
#include "DAFL_add.h"

uint64_t nb_daf = 0;

uint8_t all_daf_already_init = 0;
daf_t **all_daf = NULL;

const char *const(err_message)[DAF_ERR_COUNT] = {
		PRINTF_SUCESS " everything appended as intended",
		PRINTF_ERROR " failed to allocated some memory",
		PRINTF_ERROR " failed to read the file containing the float's mantissa",
		PRINTF_ERROR " the float you passed in is invalid",
		PRINTF_ERROR " this funcitonnality is not (yet) implemented"};

// daf_ret_t daf_load_mantissa(daf_ref_t op_ref)
// {
// 	fprintf(stderr, PRINTF_ERROR "working with mtsa in files is not allowed for now !\n");
// 	assert(0 && "Illegal");

// 	DAF_GET_PTR(op);

// 	if (op->loaded_mtsa != NULL)
// 		return DAF_RET_SUCESS;

// 	uint64_t mtsa_size = op->prec + op->real_prec_dec;

// 	char filename[64];
// 	daf_get_filename(filename, op_ref);
// 	FILE *fmantissa = fopen(filename, "rb");

// 	if (fmantissa == NULL)
// 	{
// 		fprintf(stderr, PRINTF_ERROR " could not open the file \"%s\" of the mantissa of the daf with ref %" PRIu64 "\n", filename, op_ref);
// 		return DAF_RET_ERR_READ_FILE;
// 	}

// 	op->loaded_mtsa = calloc(mtsa_size / DAF_LIMB_SIZE, sizeof(daf_t *));
// 	if (op->loaded_mtsa == NULL)
// 		return DAF_RET_ERR_ALLOC;
// 	for (uint64_t i = 0; i < mtsa_size / DAF_LIMB_SIZE; ++i)
// 	{
// 		op->loaded_mtsa[i] = calloc(DAF_LIMB_SIZE, sizeof(uint30_t));
// 		if (op->loaded_mtsa[i] == NULL)
// 			return DAF_RET_ERR_ALLOC;

// 		fread(op->loaded_mtsa[i], sizeof(uint30_t), 1, fmantissa);
// 	}
// 	fclose(fmantissa);
// 	return DAF_RET_SUCESS;
// }

// daf_ret_t daf_set_file_mantissa_zero(daf_ref_t op_ref)
// {
// 	fprintf(stderr, PRINTF_ERROR "working with mtsa in files is not allowed for now !\n");
// 	assert(0);

// 	DAF_GET_PTR(op);

// 	if (op->prec < DAF_LIMB_SIZE)
// 		return DAF_RET_SUCESS;

// 	const uint64_t binmax = (op->prec - DAF_LIMB_SIZE) + op->real_prec_dec;

// 	char filename[64];
// 	daf_get_filename(filename, op_ref);

// 	FILE *bin = fopen_mkdir(filename, "wb");
// 	if (bin == NULL)
// 		return DAF_RET_ERR_READ_FILE;

// 	const daf_limb_t buff = {0x00};

// 	for (uint64_t i = 0; i < binmax / DAF_LIMB_SIZE; ++i)
// 		fwrite(&buff, sizeof(buff), 1, bin);

// 	fclose(bin);
// 	return 0;
// }

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

	return ref;
}

// clear functions

daf_ret_t daf_clear(daf_ref_t op_ref)
{
	DAF_GET_PTR(op);
	// char filename[64];
	// daf_get_filename(filename, op_ref);
	// remove(filename);

	if (op->loaded_mtsa != NULL)
		for (uint64_t i = 0; i < (op->prec + op->real_prec_dec) / 50 - 1; ++i)
			free(op->loaded_mtsa[i]);
	free(op->loaded_mtsa);

	free((void *)all_daf[op_ref]);
	all_daf[op_ref] = NULL;

	if (op_ref == nb_daf - 1)
		--nb_daf;
	return DAF_RET_SUCESS;
}

size_t daf_get_filename(char filename[64], daf_ref_t op_ref)
{
	return snprintf(filename, 64, TMPPATH "/DAF-%" PRIu64 ".bin", op_ref);
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
				 ((op->head | DAF_HEAD_EXP_MINUS) == op->head) ? "| | < 1" : "| | >= 1",
				 DAF_IS_INT(op_ref) ? "Int" : "Float");

	printf("|- exp : %" PRIu64 "\n", op->exp);
	printf("|- prec : %" PRIu64 "\n", op->prec);
	printf("|- reak_prec_dec : %" PRIu8 "\n", op->real_prec_dec);
	printf("|- loaded_mtsa : 0x%p\n", op->loaded_mtsa);

	printf("\t|- *loaded_mtsa : 0x%p\n", *(op->loaded_mtsa));
	for (uint64_t i = 0; i < (op->prec + op->real_prec_dec) / DAF_LIMB_SIZE; ++i)
	{
		printf("\t\t|- *(loaded_mtsa)[%" PRIu64 "] : 0x%p\n\t\t\t|- [%u", i, *(op->loaded_mtsa)[i], (*(op->loaded_mtsa)[i])[0]);
		for (uint8_t j = 1; j < DAF_LIMB_SIZE; ++j)
		{
			printf(", %u", (*(op->loaded_mtsa)[i])[j]);
		}
		printf("]\n");
	}

	return DAF_RET_SUCESS;
}

// set functions ------------------------------------------------------

daf_ret_t daf_copy(daf_ref_t rop_ref, daf_ref_t op_ref)
{
	// if rop == op : no need to copy
	if (rop_ref == op_ref)
		return DAF_RET_SUCESS;

	DAF_GET_PTR(rop);
	DAF_GET_PTR(op);

	rop->head = op->head;
	rop->exp = op->exp;
	rop->prec = op->prec;
	rop->real_prec_dec = op->real_prec_dec;

	if (DAF_GET_PREC(op_ref) != DAF_GET_PREC(rop_ref))
	{
		TODO;
		return DAF_RET_ERR_NOT_IMPLEMENTED;
	}

	for (uint64_t i = 0; i < DAF_GET_PREC(rop_ref) / DAF_LIMB_SIZE; ++i)
		memcpy((rop->loaded_mtsa)[i], (op->loaded_mtsa)[i], sizeof(daf_limb_t));

	return DAF_RET_SUCESS;
}

// arthimetric functions ------------------------------------------------------

daf_ret_t daf_negate(daf_ref_t rop_ref, daf_ref_t op_ref)
{
	all_daf[rop_ref]->head = all_daf[op_ref]->head ^ DAF_HEAD_MINUS;
	return DAF_RET_SUCESS;
}

daf_ret_t daf_ror(daf_ref_t rop_ref, daf_ref_t op_ref)
{
	DAF_GET_PTR(rop);
	DAF_GET_PTR(op);

	uint64_t prev = 0;
	for (uint64_t i = 0; i < DAF_GET_PREC(op_ref) / DAF_LIMB_SIZE; ++i)
	{
		memmove((uint32_t *)*(rop->loaded_mtsa)[i] + 1, *(op->loaded_mtsa)[i], sizeof(daf_limb_t) - 1);
		(*(rop->loaded_mtsa)[i])[0] = prev;
		prev = (*(op->loaded_mtsa)[i])[DAF_LIMB_SIZE - 1];
	}

	return DAF_RET_SUCESS;
}

// daf_ret_t daf_sra(daf_ref_t rop_ref, daf_ref_t op_ref, uint64_t dec)
// {
// 	DAF_GET_PTR(rop);
// 	DAF_GET_PTR(op);

// 	for (uint64_t i = 0; i < DAF_GET_PREC(op_ref) / DAF_LIMB_SIZE; ++i)
// 	{
// 		memmove*((rop->loaded_mtsa)[i], *(op->loaded_mtsa)[i], sizeof(daf_limb_t));
// 	}

// 	return DAF_RET_SUCESS;
// }

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