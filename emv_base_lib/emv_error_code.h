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
 * 提供全局错误信息保存功能
 */
#ifndef _emv_error_code_h_
#define _emv_error_code_h_

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus  */


	/**************************************************************************
	 *                  可配置选项                   *
	 **************************************************************************/
	//设置错误的时候立刻输出
#ifndef EMV_SET_ERROR_PRINT
	#include "emv_debug.h"
	//设置错误的时候是否立刻输出
	#define EMV_SET_ERROR_PRINT 1

	//设置错误非“无错”时输出
	#ifndef EMV_PRINT_WHEN_NOT_NO_ERROR
		#define EMV_PRINT_WHEN_NOT_NO_ERROR 1
	#endif // !EMV_PRINT_WHEN_NOT_NO_ERROR

	//模块调试等级
	#ifndef EMV_ERROR_CODE_DEBUG_LEVEL
		#define EMV_ERROR_CODE_DEBUG_LEVEL DEBUG_LEVEL
	#endif // !EMV_ERROR_CODE_DEBUG_LEVEL

#endif // !EMV_SET_ERROR_PRINT


	/**************************************************************************
	 *                             M A C R O S                                *
	 **************************************************************************/
	//EMV正常运行
#define EMV_NO_ERROR 0

	//其他错误码可以在自己模块中添加，或者在这里添加
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

//设置错误码，同时保存错误消息为错误码宏相同英文
#define emv_set_error_code(code) set_error_code_with_message(code,#code,__FILE__,__FUNCTION__,__LINE__)

	//获得错误码
	unsigned int emv_get_error_code();

	//获得错误消息
	char* emv_get_error_message();

	//获得出错位置信息
	char* emv_get_error_position();

	//返回false表示错误消息可能与错误码不匹配
	unsigned int is_emv_error_code_match_message();

	//手动设置error_code和消息,错误文件和函数，行号
	void set_error_code_with_message(unsigned int error_code, char* error_message,
		char* error_file, char* error_func, unsigned int error_line);

#ifdef __cplusplus
}
#endif /* __cplusplus  */


#endif /* _emv_error_code_h_ */
/* END OF FILE */
