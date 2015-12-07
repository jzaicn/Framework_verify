#include <stdio.h>
#include "../emv_base_lib/emv_debug.h"


//������main������
void emv_debug_main()
{
	//ģ������ȼ� �� �������ȼ� ��
	emv_debug_print_line(ERROR_LEVEL, DEBUG_LEVEL)("ERROR_LEVEL, DEBUG_LEVEL\n");
	emv_debug_print_line(ERROR_LEVEL, WARNING_LEVEL)("ERROR_LEVEL, WARNING_LEVEL\n");
	emv_debug_print_line(ERROR_LEVEL, INFO_LEVEL)("ERROR_LEVEL, INFO_LEVEL\n");
	emv_debug_print_line(ERROR_LEVEL, ERROR_LEVEL)("ERROR_LEVEL, ERROR_LEVEL\n");

	emv_debug_print_line(FORCE_ALL_ON_LEVEL, DEBUG_LEVEL)("\n");

	//�ر��������
	emv_debug_print_line(FORCE_ALL_OFF_LEVEL, DEBUG_LEVEL)("FORCE_ALL_OFF_LEVEL, DEBUG_LEVEL\n");
	emv_debug_print_line(FORCE_ALL_OFF_LEVEL, WARNING_LEVEL)("FORCE_ALL_OFF_LEVEL, WARNING_LEVEL\n");
	emv_debug_print_line(FORCE_ALL_OFF_LEVEL, INFO_LEVEL)("FORCE_ALL_OFF_LEVEL, INFO_LEVEL\n");
	emv_debug_print_line(FORCE_ALL_OFF_LEVEL, ERROR_LEVEL)("FORCE_ALL_OFF_LEVEL, WARNING_LEVEL\n");

	emv_debug_print_line(FORCE_ALL_ON_LEVEL, DEBUG_LEVEL)("\n");

	//Ĭ�ϵȼ����
	emv_debug_print_line(DEFAULT_DEBUG_LEVEL, DEFAULT_DEBUG_LEVEL)("DEFAULT_DEBUG_LEVEL is %d\n", EMV_DEBUG_MODULE_OUTPUT_LEVEL);
	emv_debug_print_line(DEFAULT_DEBUG_LEVEL, DEBUG_LEVEL)("DEFAULT_DEBUG_LEVEL, DEBUG_LEVEL\n");
	emv_debug_print_line(DEFAULT_DEBUG_LEVEL, WARNING_LEVEL)("DEFAULT_DEBUG_LEVEL, WARNING_LEVEL\n");
	emv_debug_print_line(DEFAULT_DEBUG_LEVEL, INFO_LEVEL)("DEFAULT_DEBUG_LEVEL, INFO_LEVEL\n");
	emv_debug_print_line(DEFAULT_DEBUG_LEVEL, ERROR_LEVEL)("DEFAULT_DEBUG_LEVEL, WARNING_LEVEL\n");

}