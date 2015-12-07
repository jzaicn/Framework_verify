#include <stdio.h>
#include "../emv_base_lib/header.h"

int main()
{
#define ABC_ERROR 1
	emv_set_error_code(ABC_ERROR);

	printf("error data:\n");
	printf("%s : %d \n%s\n", emv_get_error_message(), emv_get_error_code(), emv_get_error_position());

#define CDE_ERROR 2
	emv_set_error_code(CDE_ERROR);

	printf("error data:\n");
	printf("%s : %d \n%s\n", emv_get_error_message(), emv_get_error_code(), emv_get_error_position());


	getchar();



	return 0;
}