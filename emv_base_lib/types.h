/**
 * @file    types.h
 * @author  Huang Wen <huangw@likingopto.com>
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
#ifndef _TYPES_H_
#define _TYPES_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32_
#include "windows.h"
#endif

/**************************************************************************
 *                   G E N E R A L    C O N S T A N T S                   *
 **************************************************************************/


/**************************************************************************
 *                         D A T A   T Y P E S                            *
 **************************************************************************/
#ifndef CONST
#define CONST                           const
#endif

#ifndef BOOL
#define BOOL                            int
#endif

typedef signed char                     int8_t; 
typedef signed short                    int16_t;
typedef signed int                      int32_t;
typedef signed long long                int64_t;
typedef unsigned char                   uint8_t;
typedef unsigned short                  uint16_t;
typedef unsigned int                    uint32_t;
typedef unsigned long long              uint64_t;

// #ifndef _WIN32_ 
// #ifndef size_t
// #define size_t                          unsigned int
// #endif
// #endif

#ifndef TRUE
#define TRUE                            1
#endif

#ifndef FALSE
#define FALSE                           0
#endif

#ifndef NULL
#define NULL                            0
#endif
/**************************************************************************
 *                             M A C R O S                                *
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


/**************************************************************************
 *                                                                       
 *  Function Name:                                      
 *                                                                        
 *  Descriptions:                                    
 *                                                                        
 *  Arguments:
 *                                                                        
 *  Returns:                                                    
 *                                                                        
 *  See also:                                                             
 *                                                                        
 **************************************************************************/


#ifdef __cplusplus
}
#endif //#ifdef __cplusplus

#endif //#ifndef _TYPES_H_
/* END OF FILE */
