#define DAF_GET_GT_OP_REF_NUM ((all_daf[op1_ref] > all_daf[op2_ref]) + 1)
#define DAF_ADD_GET_PTR_GT_OP daf_t *op1 = all_daf[PPCAT(op, PPCAT(DAF_GET_GT_OP_REF_NUM, _ref))]
#define PPCAT_NX(A, B) A##B
#define PPCAT(A, B) PPCAT_NX(A, B)
DAF_ADD_GET_PTR_GT_OP;