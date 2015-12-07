/**
* @file    emv_tlv.c
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


/**************************************************************************
*               F U N C T I O N   D E C L A R A T I O N S                *
**************************************************************************/

//�������ֽ���tag����ô���Ƿ���һ��ָ�������tlv��tag
unsigned int if_tag_has_child(unsigned char buf)
{
	if ((buf & 0x20) == 0x20)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

//�������ֽ���tag����ô���Ƿ������һ��tag�ֽ�
unsigned int if_tag_first_byte_has_next_byte(unsigned char buf)
{
	if ((buf & 0x1F) == 0x1F)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

//�������ֽ���tag�ĵڶ����ֽڣ���ô���Ƿ������һ��tag�ֽ�
unsigned int if_tag_next_byte_has_next_byte(unsigned char buf)
{
	if (((buf & 0x80) == 0x80) &&
		((buf & 0x7F) > 0))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

//�������ֽ���len����ô���Ƿ���һ��ָ�����������len�ֽڵ��ֽ�
unsigned int if_len_has_next_byte(unsigned char buf)
{
	if ((buf & 0x80) == 0x80)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

//�������ֽ���len������ָʾ��������len�ֽڣ���ô�ж��ٸ�len�ֽ�
unsigned int how_many_len_has_next(unsigned char buf)
{
	unsigned int has_child_len_byte = buf & 0x7F;
	return has_child_len_byte;
}

//////////////////////////////////////////////////////////////////////////

//��ȡtag�� ��ȡtag���򣬵�һ���ֽں���λΪ1���еڶ����ֽڣ��ڶ����Ժ���ֽ����λΪ1���к����ֽ�
unsigned int emv_tlv_get_tag(unsigned char* in_buf, unsigned int in_len, unsigned int* in_offset, unsigned int* out_tag)
{
	if (in_buf == NULL || in_offset == NULL || in_len == 0 || out_tag == NULL || *in_offset >= in_len)
	{
		emv_set_error_code(TLV_PARAM_ERROR);
		return FALSE;
	}
	else
	{
		unsigned int temp_offset = *in_offset;
		unsigned int temp_tag = 0;

		//�Ƿ��ж���1���ֽ�
		if (if_tag_first_byte_has_next_byte(in_buf[temp_offset]))
		{
			//�ȱ����һ���ֽ�
			temp_tag += in_buf[temp_offset++];
			//�ڶ����ֽڿ�ʼ�ж��Ƿ���Ҫ�¸��ֽ�
			do
			{
				if (temp_offset >= in_len)
				{
					emv_set_error_code(TLV_DECODE_ERROR);
					return FALSE;
				}
				temp_tag = temp_tag << 8;
				temp_tag += in_buf[temp_offset];
			} while (if_tag_next_byte_has_next_byte(in_buf[temp_offset++]));
		}
		else
		{
			//�ȱ����һ���ֽ�
			temp_tag += in_buf[temp_offset++];
		}

		*out_tag = temp_tag;
		*in_offset = temp_offset;
		return TRUE;
	}
}

//��ȡlen�� ��ȡlen���򣬵�һ���ֽڴ���127���к����ֽڱ�ʾ���ȣ���һ���ֽڱ�ʾ�������ٸ��ֽڴ洢����
unsigned int emv_tlv_get_len(unsigned char* in_buf, unsigned int in_len, unsigned int* in_offset, unsigned int* out_len)
{
	if (in_buf == NULL || in_offset == NULL || in_len == 0 || out_len == NULL || *in_offset >= in_len)
	{
		emv_set_error_code(TLV_PARAM_ERROR);
		return FALSE;
	}
	else
	{
		unsigned int temp_offset = *in_offset;
		unsigned int temp_len = 0;

		//�Ƿ��к����ֽ�
		if (if_len_has_next_byte(in_buf[temp_offset]))
		{
			//����ֽڱ�ʾ����
			unsigned int len_size = how_many_len_has_next(in_buf[temp_offset++]);
			unsigned int i = 0;

			if ((temp_offset + len_size) > in_len)
			{
				emv_set_error_code(TLV_DECODE_ERROR);
				return FALSE;
			}
			for (i = 0; i < len_size; i++)
			{
				temp_len = temp_len << 8;
				temp_len += in_buf[temp_offset++];
			}
		}
		//ֻ��һ���ֽ�
		else
		{
			temp_len += in_buf[temp_offset++];
		}

		*in_offset = temp_offset;
		*out_len = temp_len;
		return TRUE;
	}
}

//��ȡvalue
unsigned int emv_tlv_get_value(unsigned char* in_buf, unsigned int in_len, unsigned int* in_offset, unsigned int count_len, unsigned char** out_value)
{
	//��(*offset) + len > length����ȡ = �������Ϊ������������ڿ�
	if (in_buf == NULL || in_offset == NULL || in_len == 0 || out_value == NULL)
	{
		emv_set_error_code(TLV_PARAM_ERROR);
		return FALSE;
	}
	else if ((*in_offset) + count_len > in_len)
	{
		*out_value = NULL;
		emv_set_error_code(TLV_DECODE_ERROR);
		return FALSE;
	}
	else
	{
		*out_value = NULL;
		if (*in_offset == in_len)
		{
			*out_value = NULL;
		}
		else
		{
			*out_value = &in_buf[*in_offset];
		}
		(*in_offset) += count_len;
		return TRUE;
	}
}

//////////////////////////////////////////////////////////////////////////

//����tag��
unsigned int emv_tlv_set_tag(unsigned char* out_buf, unsigned int out_buf_len, unsigned int* in_offset, unsigned int in_tag)
{
	if (out_buf == NULL || in_offset == NULL || out_buf_len == 0 || *in_offset >= out_buf_len)
	{
		emv_set_error_code(TLV_PARAM_ERROR);
		return FALSE;
	}
	else if (in_tag == 0)
	{
		emv_set_error_code(TLV_DECODE_ERROR);
		return FALSE;
	}
	else
	{
		unsigned int temp_len = 10;
		unsigned char temp_buf[10] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, };

		unsigned int temp_offset = temp_len - 1;

		//��tag��������ֽ���
		unsigned char last_value = 0;
		while (TRUE)
		{
			if (in_tag == 0)
			{
				break;
			}

			last_value = in_tag % 256;
			in_tag = in_tag / 256;

			temp_buf[temp_offset--] = last_value;
		}

		//��ȷ���ж�
		if (temp_len - 1 - temp_offset > 1)
		{
			unsigned int test_offset = temp_offset + 1;
			if (!if_tag_first_byte_has_next_byte(temp_buf[test_offset++]))
			{
				emv_set_error_code(TLV_DECODE_ERROR);
				return FALSE;
			}
			for (; test_offset < temp_len - 1;)
			{
				if (!if_tag_next_byte_has_next_byte(temp_buf[test_offset++]))
				{
					emv_set_error_code(TLV_DECODE_ERROR);
					return FALSE;
				}
			}
		}

		//���浽Ŀ��buf��
		{
			unsigned int set_offset = temp_offset + 1;
			for (; set_offset < temp_len;)
			{
				out_buf[(*in_offset)++] = temp_buf[set_offset++];
			}
		}
		return TRUE;
	}
}

//����len��
unsigned int emv_tlv_set_len(unsigned char* out_buf, unsigned int out_buf_len, unsigned int* in_offset, unsigned int in_len)
{
	if (out_buf == NULL || in_offset == NULL || out_buf_len == 0 || *in_offset >= out_buf_len)
	{
		emv_set_error_code(TLV_PARAM_ERROR);
		return FALSE;
	}
	else
	{
		unsigned int len_byte_used = 0;
		unsigned int len_over_127 = FALSE;

		unsigned int temp_len = 10;
		unsigned char temp_buf[10] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, };

		unsigned int begin_offset = *in_offset;
		unsigned int temp_offset = temp_len - 1;

		//��len��������ֽ���
		{
			unsigned char last_value = 0;
			//�Ƿ���Ҫ�����ֽڱ�ʾ���˶��ٸ��ֽ�
			if (in_len > 127)
			{
				len_over_127 = TRUE;
			}

			if (in_len == 0)
			{
				len_byte_used = 1;
				temp_buf[temp_offset--] = 0x00;
			}

			while (TRUE)
			{
				if (in_len == 0)
				{
					break;
				}

				last_value = in_len % 256;
				in_len = in_len / 256;

				len_byte_used++;
				temp_buf[temp_offset--] = last_value;
			}

			if (len_byte_used > 1 || len_over_127 == TRUE)
			{
				temp_buf[temp_offset--] = len_byte_used | 0x80;
				len_byte_used++;
			}
		}


		//��ȷ���ж�
		if (temp_len - 1 - temp_offset > 1)
		{
			unsigned int test_offset = temp_offset + 1;
			if (if_len_has_next_byte(temp_buf[test_offset++]))
			{
				emv_set_error_code(TLV_DECODE_ERROR);
				return FALSE;
			}
			if (len_byte_used + (*in_offset) > out_buf_len)
			{
				emv_set_error_code(TLV_DECODE_ERROR);
				return FALSE;
			}
		}

		//���浽Ŀ��buf��
		{
			unsigned int set_offset = temp_offset + 1;
			for (; set_offset < temp_len;)
			{
				out_buf[(*in_offset)++] = temp_buf[set_offset++];
			}
		}
		return TRUE;
	}
}

//����value
unsigned int emv_tlv_set_value(unsigned char* out_buf, unsigned int out_buf_len, unsigned int* in_offset, unsigned int in_len, unsigned char* value)
{
	if (out_buf == NULL || in_offset == NULL || out_buf_len == 0 || *in_offset > out_buf_len)
	{
		emv_set_error_code(TLV_PARAM_ERROR);
		return FALSE;
	}
	else
	{
		if (in_len + (*in_offset) > out_buf_len)
		{
			emv_set_error_code(TLV_DECODE_ERROR);
			return FALSE;
		}
		else if (in_len == 0 && value != NULL)
		{
			emv_set_error_code(TLV_DECODE_ERROR);
			return FALSE;
		}
		else if (in_len > 0 && value == NULL)
		{
			emv_set_error_code(TLV_DECODE_ERROR);
			return FALSE;
		}
		else if (in_len == 0)
		{
			return TRUE;
		}
		else
		{
			unsigned int i = 0;
			for (i = 0; i < in_len; i++)
			{
				out_buf[(*in_offset)++] = value[i];
			}
			return TRUE;
		}
	}
}


/* END OF FILE */
