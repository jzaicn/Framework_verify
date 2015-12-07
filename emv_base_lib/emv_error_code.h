/**
 * @file    emv_error_code.h
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
 * �ṩȫ�ִ�����Ϣ���湦��
 */
#ifndef _emv_error_code_h_
#define _emv_error_code_h_

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus  */


	/**************************************************************************
	 *                  ������ѡ��                   *
	 **************************************************************************/
	//���ô����ʱ���������
#ifndef EMV_SET_ERROR_PRINT
	#include "emv_debug.h"
	//���ô����ʱ���Ƿ��������
	#define EMV_SET_ERROR_PRINT 1

	//���ô���ǡ��޴�ʱ���
	#ifndef EMV_PRINT_WHEN_NOT_NO_ERROR
		#define EMV_PRINT_WHEN_NOT_NO_ERROR 1
	#endif // !EMV_PRINT_WHEN_NOT_NO_ERROR

	//ģ����Եȼ�
	#ifndef EMV_ERROR_CODE_DEBUG_LEVEL
		#define EMV_ERROR_CODE_DEBUG_LEVEL DEBUG_LEVEL
	#endif // !EMV_ERROR_CODE_DEBUG_LEVEL

#endif // !EMV_SET_ERROR_PRINT


	/**************************************************************************
	 *                             M A C R O S                                *
	 **************************************************************************/
	//EMV��������
#define EMV_NO_ERROR 0

	//����������������Լ�ģ������ӣ��������������
	//...

	/**************************************************************************
	 *                         D A T A   T Y P E S                            *
	 **************************************************************************/


	/**************************************************************************
	 *                 E X T E R N A L   R E F E R E N C E S                  *
	 **************************************************************************/

	/**************************************************************************
	 *                        G L O B A L   D A T A                           *
	 **************************************************************************/

	/**************************************************************************
	 *               F U N C T I O N   D E C L A R A T I O N S                *
	 **************************************************************************/

//���ô����룬ͬʱ���������ϢΪ���������ͬӢ��
#define emv_set_error_code(code) set_error_code_with_message(code,#code,__FILE__,__FUNCTION__,__LINE__)

	//��ô�����
	unsigned int emv_get_error_code();

	//��ô�����Ϣ
	char* emv_get_error_message();

	//��ó���λ����Ϣ
	char* emv_get_error_position();

	//����false��ʾ������Ϣ����������벻ƥ��
	unsigned int is_emv_error_code_match_message();

	//�ֶ�����error_code����Ϣ,�����ļ��ͺ������к�
	void set_error_code_with_message(unsigned int error_code, char* error_message,
		char* error_file, char* error_func, unsigned int error_line);

#ifdef __cplusplus
}
#endif /* __cplusplus  */


#endif /* _emv_error_code_h_ */
/* END OF FILE */
