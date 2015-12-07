/**
 * @file    emv_error_code.c
 * @author  Chen Gangjian <chengj@makingic.com>
 * @version 1.0
 *
 * @section LICENSE
 *
 * Copyright (C) 2014 Guangzhou Liking Optoelectronic Technology Co.,Ltd, All
 * Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 * http://www.likingopto.com
 *
 * @section DESCRIPTION
 *
 * This file is ...
 */
#include "header.h"
#include <stdio.h>

/**************************************************************************
 *                   G E N E R A L    C O N S T A N T S                   *
 **************************************************************************/


/**************************************************************************
 *                         D A T A   T Y P E S                            *
 **************************************************************************/


/**************************************************************************
 *                             M A C R O S                                *
 **************************************************************************/


/**************************************************************************
 *                 E X T E R N A L   R E F E R E N C E S                  *
 **************************************************************************/
unsigned int emv_error_code = EMV_NO_ERROR;
char* emv_error_message = "EMV_NO_ERROR";
unsigned int emv_error_code_match_message = TRUE;
char* emv_error_file = "";
char* emv_error_func = "";
unsigned int emv_error_line = 0;
/**************************************************************************
 *                        G L O B A L   D A T A                           *
 **************************************************************************/


/**************************************************************************
 *               F U N C T I O N   D E C L A R A T I O N S                *
 **************************************************************************/
//��ô�����
unsigned int emv_get_error_code()
{
	return emv_error_code;
}
//��ô�����Ϣ
char* emv_get_error_message()
{
	return emv_error_message;
}
//����false��ʾ������Ϣ����������벻ƥ��
unsigned int is_emv_error_code_match_message()
{
	return emv_error_code_match_message;
}
//��ó���λ����Ϣ
char* emv_get_error_position()
{
	unsigned int buf_len = 255;
	static char buf[255];
	
	sprintf_s(buf,buf_len, "[file]: %s , \n[func]: %s , \n[line]: %d \n", emv_error_file, emv_error_func, emv_error_line);
	return buf;
}
//�ֶ�����error_code����Ϣ,�����ļ��ͺ������к�
void set_error_code_with_message(unsigned int error_code, char* error_message, 
	char* error_file, char* error_func, unsigned int error_line)
{
	//����������
	emv_error_code = error_code;
	emv_error_message = error_message;
	emv_error_code_match_message = TRUE;
	emv_error_file = error_file;
	emv_error_func = error_func;
	emv_error_line = error_line;

	//ERROR_MESSAGE : ERROR_CODE
	//[position] :ErrorPosition
	char* error_format = "%s : %d \n%s\n";

	//���������
	if (EMV_SET_ERROR_PRINT == 1)//������ʱ��ӡ
	{
		if (EMV_PRINT_WHEN_NOT_NO_ERROR == 1)//���÷ǡ��޴�ʱ��ӡ
		{
			if (error_code != EMV_NO_ERROR)
			{
				emv_debug_print_line(DEFAULT_DEBUG_LEVEL, ERROR_LEVEL)(error_format, error_message, emv_error_code, emv_get_error_position());
			}
		}
		else//ȫ����ӡ
		{
			emv_debug_print_line(DEFAULT_DEBUG_LEVEL, INFO_LEVEL)(error_format, error_message, emv_error_code, emv_get_error_position());
		}
	}

	

	
}

/* END OF FILE */
