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

	//�������ֽ���tag����ô���Ƿ���һ��ָ�������tlv��tag
	unsigned int if_tag_has_child(unsigned char buf);

	//�������ֽ���tag����ô���Ƿ������һ��tag�ֽ�
	unsigned int if_tag_first_byte_has_next_byte(unsigned char buf);

	//�������ֽ���tag�ĵڶ����ֽڣ���ô���Ƿ������һ��tag�ֽ�
	unsigned int if_tag_next_byte_has_next_byte(unsigned char buf);

	//�������ֽ���len����ô���Ƿ���һ��ָ�����������len�ֽڵ��ֽ�
	unsigned int if_len_has_next_byte(unsigned char buf);

	//�������ֽ���len������ָʾ��������len�ֽڣ���ô�ж��ٸ�len�ֽ�
	unsigned int how_many_len_has_next(unsigned char buf);

	//////////////////////////////////////////////////////////////////////////

	//��ȡtag�� ��ȡtag���򣬵�һ���ֽں���λΪ1���еڶ����ֽڣ��ڶ����Ժ���ֽ����λΪ1���к����ֽ�
	unsigned int emv_tlv_get_tag(unsigned char* in_buf, unsigned int in_len, unsigned int* in_offset, unsigned int* out_tag);

	//��ȡlen�� ��ȡlen���򣬵�һ���ֽڴ���127���к����ֽڱ�ʾ���ȣ���һ���ֽڱ�ʾ�������ٸ��ֽڴ洢����
	unsigned int emv_tlv_get_len(unsigned char* in_buf, unsigned int in_len, unsigned int* in_offset, unsigned int* out_len);

	//��ȡvalue
	unsigned int emv_tlv_get_value(unsigned char* in_buf, unsigned int in_len, unsigned int* in_offset, unsigned int count_len, unsigned char** out_value);

	//////////////////////////////////////////////////////////////////////////

	//����tag��
	unsigned int emv_tlv_set_tag(unsigned char* out_buf, unsigned int out_buf_len, unsigned int* in_offset, unsigned int in_tag);

	//����len��
	unsigned int emv_tlv_set_len(unsigned char* out_buf, unsigned int out_buf_len, unsigned int* in_offset, unsigned int in_len);

	//����value
	unsigned int emv_tlv_set_value(unsigned char* out_buf, unsigned int out_buf_len, unsigned int* in_offset, unsigned int in_len, unsigned char* value);


#ifdef __cplusplus
}
#endif /* __cplusplus  */


#endif /* _emv_tlv_h_ */
/* END OF FILE */
