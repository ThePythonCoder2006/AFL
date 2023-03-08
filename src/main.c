#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#include "DAFL.h"

#define PREC 1

int main(int argc, char **argv)
{
	// remove the first element of the call (the name of the program)
	--argc, argv++;

	daf_ref_t op1 = daf_init(PREC),
						op2 = daf_init(PREC);

	daf_set_ui(op1, 1);
	daf_set_ui(op2, 1);

	daf_debug_out(op1, "op1");
	daf_debug_out(op2, "op2");

	daf_add(op1, op1, op2);

	daf_debug_out(op1, "op1");
	daf_debug_out(op2, "op2");

	daf_printf("op1 : %DF", op1);

	daf_clear(op1);
	daf_clear(op2);

	return EXIT_SUCCESS;
}