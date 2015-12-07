/**
 * @file    level2_debug.c
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
#include <stdarg.h>

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


/**************************************************************************
 *                        G L O B A L   D A T A                           *
 **************************************************************************/
unsigned int g_debug_level = EMV_DEBUG_MODULE_OUTPUT_LEVEL;

/**************************************************************************
 *               F U N C T I O N   D E C L A R A T I O N S                *
 **************************************************************************/
//内部：输出打印等级过滤
unsigned int is_emv_debug_print_level_enable(unsigned module_debug_level, unsigned int word_debug_level)
{
	unsigned int result = FALSE;
	if (g_debug_level == FORCE_ALL_ON_LEVEL)
	{
		//强制输出
		result = TRUE;
	}
	else if (g_debug_level == FORCE_ALL_OFF_LEVEL)
	{
		//不输出
	}
	else
	{
		if (module_debug_level == DEFAULT_DEBUG_LEVEL)
		{
			module_debug_level = g_debug_level;
		}

		if (word_debug_level >= module_debug_level)
		{
			//等级超过限制，输出
			result = TRUE;
		}
	}
	return result;
}

//内部：行输出前缀，不建议使用
unsigned int emv_print_line_prefix()
{
	//不建议输出
	//EMV_PRINT_FUNCTION("[%s]\n", __TIME__);
	return TRUE;
}


//调试buffer
void emv_debug_buffer(unsigned char* buffer, unsigned int len)
{
	if (buffer != NULL && len != 0)
	{
		unsigned int i = 0;
		for (i = 0; i < len; i++)
		{
			EMV_PRINT_FUNCTION( "%02x", buffer[i]);
		}
		EMV_PRINT_FUNCTION("\n");
	}
}

/* END OF FILE */
