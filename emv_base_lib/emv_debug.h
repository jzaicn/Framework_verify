/**
 * @file    level2_debug.h
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
 *
 * �������е�print������ͨ�����װ���Լ���ѡ��ʵ��ģ�鼶���Լ���������Ƕ����伶�������
 * ����ʹ��print������������ʹ��vsprintf�����Բ������ܶ��Ƹ��������Ϣ��ֻ�����û����ʱ���塣
 * �������㵱ǰʹ��Ҫ��
 * 
 * ���������ѡ�
 * �ⲿprint����
 * �ⲿ�ɶ���ģ��Ĭ������ȼ�
 *
 * ģ���ṩ���ܣ�
 * //�е������
 * emv_debug_print_line (ģ��ȼ����������ȼ�) ("");
 *
 * //��������
 * emv_debug_print_line (ģ��ȼ����������ȼ�) (bufָ�룬buf����);
 */
#ifndef _emv_debug_h_
#define _emv_debug_h_

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus  */


/**************************************************************************
 *                   ������ѡ��                   *
 **************************************************************************/
 //debug���������
#ifndef EMV_DEBUG_MODULE_OUTPUT_LEVEL
	#define EMV_DEBUG_MODULE_OUTPUT_LEVEL DEBUG_LEVEL
#endif // !EMV_DEBUG_MODULE_OUTPUT_LEVEL

 //debugģ��ʹ���¼�print�������
#ifndef EMV_PRINT_FUNCTION
	//Ĭ��ʹ��ϵͳprintf
	#include <stdio.h>
	#define EMV_PRINT_FUNCTION printf
#endif // !EMV_PRINT_FUNCTION

/**************************************************************************
 *                             M A C R O S                                *
 **************************************************************************/


//debug�����Ϣ�ȼ�
typedef enum {
	FORCE_ALL_ON_LEVEL	,

	DEBUG_LEVEL			,
	INFO_LEVEL			,
	WARNING_LEVEL		,
	ERROR_LEVEL			,

	FORCE_ALL_OFF_LEVEL	,
	DEFAULT_DEBUG_LEVEL	,
}emv_debug_level;
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

	//���������������¶������������Ϣ���������debugģ���ڲ������ǰ׺���
#define emv_debug_print_block(module_debug_level,word_debug_level)	\
if (is_emv_debug_print_level_enable(module_debug_level,word_debug_level)) emv_debug_buffer

	//���������������¶������������Ϣ������debugģ���ڲ�����ǰ׺���
#define emv_debug_print_line(module_debug_level,word_debug_level)	\
if ( is_emv_debug_print_level_enable(module_debug_level,word_debug_level) && emv_print_line_prefix()) EMV_PRINT_FUNCTION

	//�ڲ��������ӡ�ȼ�����
	unsigned int is_emv_debug_print_level_enable(unsigned module_debug_level, unsigned int word_debug_level);

	//�ڲ��������ǰ׺��������ʹ��
	unsigned int emv_print_line_prefix();

	//����buffer
	void emv_debug_buffer(unsigned char* buffer, unsigned int len);


#ifdef __cplusplus
}
#endif /* __cplusplus  */


#endif /* _emv_debug_H_ */
/* END OF FILE */
