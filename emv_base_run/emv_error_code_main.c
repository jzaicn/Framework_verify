#include <stdio.h>
#include "../emv_base_lib/emv_error_code.h"
#include "stdio.h"


void emv_error_code_main()
{
#define ABC_ERROR 1
	emv_set_error_code(ABC_ERROR);

	printf("error code: %d\n", emv_get_error_code);
	printf(emv_get_error_message());
	printf("\n");
	printf(emv_get_error_position());
	printf("\n");
}