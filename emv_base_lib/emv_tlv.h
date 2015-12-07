/**
 * @file    emv_tlv.h
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
#ifndef _emv_tlv_h_
#define _emv_tlv_h_


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus  */


	/**************************************************************************
	 *                   G E N E R A L    C O N S T A N T S                   *
	 **************************************************************************/

	/**************************************************************************
	 *                             M A C R O S                                *
	 **************************************************************************/
#define	TLV_PARAM_ERROR 0x0101
#define TLV_DECODE_ERROR 0x0102
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

	//如果这个字节是tag，那么它是否是一个指向包含子tlv的tag
	unsigned int if_tag_has_child(unsigned char buf);

	//如果这个字节是tag，那么它是否包含下一个tag字节
	unsigned int if_tag_first_byte_has_next_byte(unsigned char buf);

	//如果这个字节是tag的第二个字节，那么它是否包含下一个tag字节
	unsigned int if_tag_next_byte_has_next_byte(unsigned char buf);

	//如果这个字节是len，那么它是否是一个指向后续有其他len字节的字节
	unsigned int if_len_has_next_byte(unsigned char buf);

	//如果这个字节是len，而且指示后续还有len字节，那么有多少个len字节
	unsigned int how_many_len_has_next(unsigned char buf);

	//////////////////////////////////////////////////////////////////////////

	//获取tag。 获取tag规则，第一个字节后五位为1则有第二个字节，第二个以后的字节最高位为1则还有后续字节
	unsigned int emv_tlv_get_tag(unsigned char* in_buf, unsigned int in_len, unsigned int* in_offset, unsigned int* out_tag);

	//获取len。 获取len规则，第一个字节大于127则有后续字节表示长度，第一个字节表示后续多少个字节存储长度
	unsigned int emv_tlv_get_len(unsigned char* in_buf, unsigned int in_len, unsigned int* in_offset, unsigned int* out_len);

	//获取value
	unsigned int emv_tlv_get_value(unsigned char* in_buf, unsigned int in_len, unsigned int* in_offset, unsigned int count_len, unsigned char** out_value);

	//////////////////////////////////////////////////////////////////////////

	//设置tag。
	unsigned int emv_tlv_set_tag(unsigned char* out_buf, unsigned int out_buf_len, unsigned int* in_offset, unsigned int in_tag);

	//设置len。
	unsigned int emv_tlv_set_len(unsigned char* out_buf, unsigned int out_buf_len, unsigned int* in_offset, unsigned int in_len);

	//设置value
	unsigned int emv_tlv_set_value(unsigned char* out_buf, unsigned int out_buf_len, unsigned int* in_offset, unsigned int in_len, unsigned char* value);


#ifdef __cplusplus
}
#endif /* __cplusplus  */


#endif /* _emv_tlv_h_ */
/* END OF FILE */
