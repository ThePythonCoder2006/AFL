#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#include "DAFL.h"

#define PREC 51

int main(int argc, char **argv)
{
	// remove the first element of the call (the name of the program)
	--argc, argv++;

	daf_ref_t op1 = daf_init(PREC),
						op2 = daf_init(PREC),
						rop = daf_init(PREC);

	daf_set_ui(op1, TEN_9_MAX);
	daf_set_ui(op2, TEN_9_MAX);

	for (uint32_t i = 0; i < 10; ++i)
	{
		daf_add(rop, op1, op2);

#ifdef _DEBUG
#define PRINTF_RED
#define PRINTF_RESET
#endif

		daf_printf(PRINTF_RED "%DgF" PRINTF_RESET "\n", op2);
	}

	daf_clear(op1);
	daf_clear(op2);
	daf_clear(rop);

	return EXIT_SUCCESS;
}

void test_limb_add(void)
{
	uint8_t carry, dec = 2;

	daf_limb_t rop, op1 = {TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX},
									op2_bott = {0},																																																																	// = {TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX},
			op2_top = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0}; // = {TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX, TEN_9_MAX};

	printf("op1 = ");
	for (uint8_t i = 0; i < DAF_LIMB_SIZE; ++i)
	{
		printf("%09" PRIu32 " ", op1[i]);
	}
	putchar('\n');

	printf("op2 = ");
	for (uint8_t i = 0; i < DAF_LIMB_SIZE; ++i)
	{
		if (i < dec)
			printf("%09" PRIu32 " ", op2_bott[DAF_LIMB_SIZE - dec + i]);
		else
			printf(PRINTF_CYAN "%09u ", op2_top[i - dec]);
	}
	// printf(PRINTF_RESET);
	putchar('\n');

	daf_limb_add(&carry, &rop, op1, op2_bott, op2_top, dec);

	printf(PRINTF_RESET "rop=%1" PRIu8 " ", carry);
	for (uint8_t i = 0; i < DAF_LIMB_SIZE; ++i)
	{
		printf("%09" PRIu32 " ", rop[i]);
	}
	putchar('\n');

	return;
}
