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
 * 基于现有的print函数，通过宏封装调试级别选择，实现模块级调试级别，下面再嵌套语句级调试输出
 * 由于使用print函数，而不是使用vsprintf，所以参数不能定制附带输出信息，只能由用户输出时定义。
 * 基本满足当前使用要求。
 * 
 * 对外可配置选项：
 * 外部print函数
 * 外部可定义模块默认输出等级
 *
 * 模块提供功能：
 * //行调试输出
 * emv_debug_print_line (模块等级，调试语句等级) ("");
 *
 * //块调试输出
 * emv_debug_print_line (模块等级，调试语句等级) (buf指针，buf长度);
 */
#ifndef _emv_debug_h_
#define _emv_debug_h_

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus  */


/**************************************************************************
 *                   可配置选项                   *
 **************************************************************************/
 //debug总输出控制
#ifndef EMV_DEBUG_MODULE_OUTPUT_LEVEL
	#define EMV_DEBUG_MODULE_OUTPUT_LEVEL DEBUG_LEVEL
#endif // !EMV_DEBUG_MODULE_OUTPUT_LEVEL

 //debug模块使用下级print方法入口
#ifndef EMV_PRINT_FUNCTION
	//默认使用系统printf
	#include <stdio.h>
	#define EMV_PRINT_FUNCTION printf
#endif // !EMV_PRINT_FUNCTION

/**************************************************************************
 *                             M A C R O S                                *
 **************************************************************************/


//debug输出信息等级
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

	//当调试允许的情况下对外输出调试信息，不会输出debug模块内部定义的前缀输出
#define emv_debug_print_block(module_debug_level,word_debug_level)	\
if (is_emv_debug_print_level_enable(module_debug_level,word_debug_level)) emv_debug_buffer

	//当调试允许的情况下对外输出调试信息，可在debug模块内部定义前缀输出
#define emv_debug_print_line(module_debug_level,word_debug_level)	\
if ( is_emv_debug_print_level_enable(module_debug_level,word_debug_level) && emv_print_line_prefix()) EMV_PRINT_FUNCTION

	//内部：输出打印等级过滤
	unsigned int is_emv_debug_print_level_enable(unsigned module_debug_level, unsigned int word_debug_level);

	//内部：行输出前缀，不建议使用
	unsigned int emv_print_line_prefix();

	//调试buffer
	void emv_debug_buffer(unsigned char* buffer, unsigned int len);


#ifdef __cplusplus
}
#endif /* __cplusplus  */


#endif /* _emv_debug_H_ */
/* END OF FILE */
