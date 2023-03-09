#ifndef __DAFL_MACROS__
#define __DAFL_MACROS__

/*-------------------------------start constants-------------------------------*/

#define DAF_HEAD_MINUS (1 << DAF_HEAD_EXP_MINUS_COMP)					// 0b00000001
#define DAF_HEAD_ZERO (1 << DAF_HEAD_EXP_ZERO_COMP)						// 0b00000010
#define DAF_HEAD_INF (1 << DAF_HEAD_EXP_INF_COMP)							// 0b00000100
#define DAF_HEAD_NaN (1 << DAF_HEAD_EXP_NaN_COMP)							// 0b00001000
#define DAF_HEAD_EXP_MINUS (1 << DAF_HEAD_EXP_EXP_MINUS_COMP) // 0b00010000
#define DAF_HEAD_INT (1 << DAF_HEAD_EXP_INT_COMP)							// 0b00100000

#define FLOAT_UNIT_BIN_SIZE (30)
#define FLOAT_UNIT_DECIMAL_SIZE (9)
#define TEN_9_BIN_SIZE (FLOAT_UNIT_BIT_SIZE)
#define TEN_9_DECIMAL_SIZE (FLOAT_UNIT_DECIMAL_SIZE)
#define DAF_LIMB_DECIMAL_SIZE (DAF_LIMB_SIZE * TEN_9_DECIMAL_SIZE)
#define DAF_LIMB_BIN_SIZE (DAF_LIMB_SIZE * sizeof(uint30_t))
#define UINT30_MAX ((1ULL << 30) - 1)
#define TEN_9_MAX (999999999ULL)
#define TEN_9_DEC ((UINT30_MAX) - (TEN_9_MAX))

#define TMPPATH "./bin/tmp"

#define DAF_LIMB_SIZE (50)

#define UINT64_TO_UINT30_MASK UINT30_MAX

/*-------------------------------end constants-------------------------------*/
/*-------------------------------start inline functions-------------------------------*/

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
#define DAF_MTSA_NTH(ref, n) ((*DAF_MTSA_LIMB_AT_NTH_UINT30(ref, n))[n % DAF_LIMB_SIZE])
#define DAF_MTSA_GET_LIMB(ref, n) *((*(all_daf[ref])).loaded_mtsa[n])

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

/*-------------------------------end inline functions-------------------------------*/

/*-------------------------start PRINTF_BYTE_TO_BINARY--------------------------*/

#define PRINTF_BINARY_PATTERN_INT8 "%c%c%c%c%c%c%c%c "
#define PRINTF_BYTE_TO_BINARY_INT8(i) \
	(((i)&0x80ll) ? '1' : '0'),         \
			(((i)&0x40ll) ? '1' : '0'),     \
			(((i)&0x20ll) ? '1' : '0'),     \
			(((i)&0x10ll) ? '1' : '0'),     \
			(((i)&0x08ll) ? '1' : '0'),     \
			(((i)&0x04ll) ? '1' : '0'),     \
			(((i)&0x02ll) ? '1' : '0'),     \
			(((i)&0x01ll) ? '1' : '0')

#define PRINTF_BINARY_PATTERN_INT16 \
	PRINTF_BINARY_PATTERN_INT8 PRINTF_BINARY_PATTERN_INT8
#define PRINTF_BYTE_TO_BINARY_INT16(i) \
	PRINTF_BYTE_TO_BINARY_INT8((i) >> 8), PRINTF_BYTE_TO_BINARY_INT8(i)
#define PRINTF_BINARY_PATTERN_INT32 \
	PRINTF_BINARY_PATTERN_INT16 PRINTF_BINARY_PATTERN_INT16
#define PRINTF_BYTE_TO_BINARY_INT32(i) \
	PRINTF_BYTE_TO_BINARY_INT16((i) >> 16), PRINTF_BYTE_TO_BINARY_INT16(i)
#define PRINTF_BINARY_PATTERN_INT64 \
	PRINTF_BINARY_PATTERN_INT32 PRINTF_BINARY_PATTERN_INT32
#define PRINTF_BYTE_TO_BINARY_INT64(i) \
	PRINTF_BYTE_TO_BINARY_INT32((i) >> 32), PRINTF_BYTE_TO_BINARY_INT32(i)

/*-------------------------end PRINTF_BYTE_TO_BINARY--------------------------*/

/*------------------------------start-printf colors-------------------------------*/

#define PRINTF_BLACK "\033[0;30m"
#define PRINTF_RED "\033[0;31m"
#define PRINTF_GREEN "\033[0;32m"
#define PRINTF_YELLOW "\033[0;33m"
#define PRINTF_BLUE "\033[0;34m"
#define PRINTF_PURPLE "\033[0;35m"
#define PRINTF_CYAN "\033[0;36m"
#define PRINTF_WHITE "\033[0;37m"
#define PRINTF_RESET "\033[0m"

#define PRINTF_ERROR PRINTF_RED "[ERROR]" PRINTF_RESET
#define PRINTF_SUCESS PRINTF_GREEN "[SUCESS]" PRINTF_RESET
#define PRINTF_WARNING PRINTF_YELLOW "[WARNING]" PRINTF_RESET

#define PRINTF_NaN "NaN"
#define PRITNF_NaN_len sizeof(PRINTF_NaN)

#define PRINTF_INF "Inf"
#define PRITNF_INF_len sizeof(PRINTF_INF)

#define PRINTF_0 "0"
#define PRITNF_0_len sizeof(PRINTF_0)

/*-------------------------------end printf colors-------------------------------*/

#endif //__DAFL_MACROS__