#ifndef __DAFL_MACROS__
#define __DAFL_MACROS__

#define DIV_CEIL(p, q) ((p) / (q) + ((p) % (q) != 0))

#define DAF_IS_ZERO(ref) (((all_daf[ref])->head | (DAF_HEAD_ZERO)) == (all_daf[ref])->head)
#define DAF_IS_NaN(ref) (((all_daf[ref])->head | (DAF_HEAD_NaN)) == (all_daf[ref])->head)
#define DAF_IS_INF(ref) (((all_daf[ref])->head | (DAF_HEAD_INF)) == (all_daf[ref])->head)
#define DAF_IS_INT(ref) (((all_daf[ref])->head | (DAF_HEAD_INT)) == (all_daf[ref])->head)
#define DAF_IS_POS(ref) (((all_daf[ref])->head | (DAF_HEAD_MINUS)) != (all_daf[ref])->head)

#define DAF_GET_PTR(op) daf_t *op = all_daf[op##_ref]

#define DAF_GET(ref, key) (all_daf[(ref)]->key)

#define DAF_GET_PREC(ref) (all_daf[(ref)]->prec + all_daf[(ref)]->real_prec_dec)

#define DAF_MTSA_LIMB_AT_NTH_UINT30(ref, n) ((*(all_daf[ref])).loaded_mtsa[(n - (n % DAF_LIMB_SIZE)) / DAF_LIMB_SIZE])
#define DAF_MTSA_NTH(ref, n) ((*DAF_MTSA_LIMB_AT_NTH_UINT30((ref), (n)))[(n) % DAF_LIMB_SIZE])
#define DAF_MTSA_GET_LIMB(ref, n) *((*(all_daf[(ref)])).loaded_mtsa[(n)])

#define SMOD_2x(op, m) (op - (op > m) * (m))
#define SMOD_4x(op, m) SMOD_2x(SMOD_2x(op, 2 * m), m)
#define SMOD_8x(op, m) SMOD_4x(SMOD_4x(op, 4 * m), m)

#define OPEN_FILE_OR_PANIC(path, mode, var)                          \
	if (((var) = fopen((path), (mode))) == NULL)                       \
	{                                                                  \
		fprintf(stderr, PRINTF_ERROR " could not open file %s", (path)); \
		return DAF_RET_ERR_READ_FILE;                                    \
	}

#define PPCAT_NX(A, B) A##B
#define PPCAT(A, B) PPCAT_NX(A, B)

#define XSTR(a) #a
#define STR(a) XSTR(a)

#define SAFE_CALL(func, rop_ref, ...)                           \
	if (rop_ref == arg2_ref)                                      \
	{                                                             \
		daf_ref_t rop2_ref = daf_init(DAF_GET(arg1_ref, prec));     \
		daf_ret_t ret = PPCAT(func, _restrict)(rop2_ref, arg1_ref); \
		daf_copy(arg1_ref, rop2_ref);                               \
		daf_clear(rop2_ref);                                        \
		return ret;                                                 \
	}                                                             \
	return PPCAT(func, _restrict)(arg1_ref, arg2_ref);

#define TODO fprintf(stderr, PRINTF_ERROR " Not yet implemented !!! %i\n", __LINE__)

#ifdef _DEBUG
#define daf_debug(op) daf_debug_out(PPCAT(op, _ref), STR(op))
#else
#define daf_debug(op)
#endif

#endif //__DAFL_MACROS__