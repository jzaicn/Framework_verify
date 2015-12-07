/**
 * @file    emv_tlv_tree.c
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

//去除前/后面某些字节 //hex:000001010202 , len = 6 ,offset = 0 ,remove = 00 , left_2_right = TRUE
unsigned int remove_byte(unsigned char* buf, unsigned int* buf_len, unsigned int* offset, unsigned char remove_char, unsigned is_left_to_right)
{
	if (buf == NULL || buf_len == NULL || offset == NULL || is_left_to_right > 1)
	{
		emv_set_error_code(TLV_TREE_PARAM_ERROR);
		return FALSE;
	}
	else
	{
		//处理前置移除字节
		if (is_left_to_right == TRUE)
		{
			unsigned int i = 0;
			for (i = 0; i < (*buf_len); i++)
			{
				if (buf[(*offset)] == remove_char)
				{
					(*offset)++;
				}
				else
				{
					break;
				}
			}
		}
		//处理后置移除字节
		else
		{
			unsigned int i = 0;
			unsigned int temp_len = (*buf_len);
			for (i = 0; i < temp_len; i++)
			{
				if (buf[temp_len - 1 - i] == remove_char)
				{
					(*buf_len)--;
				}
				else
				{
					break;
				}
			}
		}
		return TRUE;
	}
}

//tlv之间会存在没有意义的00字节，移动offset，忽略他们
unsigned int emv_tlv_decode_ignore_nosence_zero_byte_from_left(unsigned char* buf, unsigned int* buf_len, unsigned int* offset)
{
	if (buf == NULL || buf_len == NULL || offset == NULL)
	{
		emv_set_error_code(TLV_TREE_PARAM_ERROR);
		return FALSE;
	}
	else
	{
		return remove_byte(buf, buf_len, offset, 0x00, TRUE);
	}
}

//判断buffer是否用尽了
unsigned int is_buffer_used_up(unsigned int buf_size, unsigned int offset)
{
	//还有剩余字节
	if (buf_size - offset > 0)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

//树节点初始化
unsigned int tree_node_init(tlv_tree_node_t* node)
{
	if (node == NULL)
	{
		emv_set_error_code(TLV_TREE_PARAM_ERROR);
		return FALSE;
	}
	else
	{
		node->tag = 0;
		node->len = 0;
		node->val = NULL;
		node->is_a_template = FALSE;
		node->bother = NULL;
		node->child = NULL;
		return TRUE;
	}
}

//树节点初始化
unsigned int tree_node_array_init(tlv_tree_node_t* node, unsigned int node_array_size)
{
	unsigned int i = 0;
	for (i = 0; i < node_array_size; i++)
	{
		if (!tree_node_init(&(node[i])))
		{
			return FALSE;
		}
	}
	return TRUE;
}

//解析出来的node保存到数组中
unsigned int save_node_2_node(tlv_tree_node_t *dst_node, tlv_tree_node_t* src_node)
{
	if (dst_node == NULL || src_node == NULL)
	{
		emv_set_error_code(TLV_TREE_PARAM_ERROR);
		return FALSE;
	}
	else
	{
		dst_node->tag = src_node->tag;
		dst_node->len = src_node->len;
		dst_node->val = src_node->val;
		dst_node->is_a_template = src_node->is_a_template;
		dst_node->bother = src_node->bother;
		dst_node->child = src_node->child;
		return TRUE;
	}
}

//从buffer中解析一个tlv
unsigned int get_one_tlv(tlv_tree_node_t* node, unsigned char* buf, unsigned int buf_size, unsigned int* offset)
{
	if (node == NULL || buf == NULL || offset == NULL || buf_size <= (*offset))
	{
		emv_set_error_code(TLV_TREE_PARAM_ERROR);
		return FALSE;
	}
	else
	{
		node->is_a_template = if_tag_has_child(buf[*offset]);

		if (!emv_tlv_get_tag(buf, buf_size, offset, &(node->tag)))
		{
			emv_set_error_code(TLV_TREE_DECODE_ERROR);
			return FALSE;
		}
		if (!emv_tlv_get_len(buf, buf_size, offset, &(node->len)))
		{
			emv_set_error_code(TLV_TREE_DECODE_ERROR);
			return FALSE;
		}
		if (!emv_tlv_get_value(buf, buf_size, offset, node->len, &(node->val)))
		{
			emv_set_error_code(TLV_TREE_DECODE_ERROR);
			return FALSE;
		}
		return TRUE;
	}
}

//保存到队列中
unsigned int save_tlv_node_and_set_upper_pointer(tlv_tree_root_t* root, tlv_tree_node_t** upper_pointer, tlv_tree_node_t* node)
{
	//保存空间确认
	if (root->node_size > root->node_used)
	{
		(*upper_pointer) = &(root->node_array[root->node_used]);
		root->node_used++;
		return TRUE;
	}
	else
	{
		emv_set_error_code(TLV_TREE_FULL_ERROR);
		return FALSE;
	}
}

//*内部：tlv树解析，递归函数
unsigned int tlv_tree_buffer_parse_internal(tlv_tree_root_t* root, unsigned char* buf, unsigned int buf_size, tlv_tree_node_t** upper_pointer)
{
	if (root == NULL || buf == NULL || upper_pointer == NULL)
	{
		emv_set_error_code(TLV_TREE_PARAM_ERROR);
		return FALSE;
	}
	else
	{
		unsigned int result = FALSE;
		tlv_tree_node_t* node = &(root->node_array[root->node_used]);
		unsigned int offset = 0;

		//清除前置没用00字节
		if (!emv_tlv_decode_ignore_nosence_zero_byte_from_left(buf, &buf_size, &offset))
		{
			return FALSE;
		}

		//消耗完了buffer，本次不解析，返回成功
		if (is_buffer_used_up(buf_size, offset))
		{
			return TRUE;
		}

		//获取tlv
		if (!get_one_tlv(node, buf, buf_size, &offset))
		{
			return FALSE;
		}

		//确认保存并指向上一级
		if (!save_tlv_node_and_set_upper_pointer(root, upper_pointer, node))
		{
			return FALSE;
		}


		//判断是否是有子节点
		if (node->is_a_template == TRUE)
		{
			result = tlv_tree_buffer_parse_internal(root, node->val, node->len, &(node->child));
			if (!result)
			{
				return result;
			}
		}

		if (node->tag == 0x9F11)
		{
			unsigned int i = 0;
		}

		return tlv_tree_buffer_parse_internal(root, buf + offset, buf_size - offset, &(node->bother));
	}
}

//tlv树解析
unsigned int tlv_tree_buffer_parse(tlv_tree_root_t* root)
{
	return tlv_tree_buffer_parse_internal(root, root->mem_buf, root->mem_used, &(root->root));
}

unsigned int tlv_tree_build_recount_internal(unsigned int * len, tlv_tree_node_t* node)
{
	if (len == NULL || node == NULL)
	{
		emv_set_error_code(TLV_TREE_PARAM_ERROR);
		return FALSE;
	}
	else
	{
		unsigned int buf_len = 10;
		unsigned char buf[10];
		unsigned int offset = 0;
		
		if (node->is_a_template)
		{
			//自己的长度=所有子节点的长度和
			node->len = 0;
			if (!tlv_tree_build_recount_internal(&(node->len), node->child))
			{
				return FALSE;
			}
		}
		
		//计算自己的长度
		offset = 0;
		if (!emv_tlv_set_tag(buf, buf_len, &offset, node->tag))
		{
			return FALSE;
		}
		if (!emv_tlv_set_len(buf, buf_len, &offset, node->len))
		{
			return FALSE;
		}
		//得出自己占用长度
		offset += node->len;

		//递归计算兄弟的长度，累加到自己的长度中
		if (node->bother != NULL)
		{
			if (!tlv_tree_build_recount_internal(&(offset), node->bother))
			{
				return FALSE;
			}
		}
		(*len) += offset;

		return TRUE;
	}
}

//重新计算tlv长度值
unsigned int tlv_tree_build_recount(tlv_tree_root_t* root)
{
	if (root == NULL || root->root == NULL ||
		root->mem_buf == NULL || root->mem_size == 0 || root->mem_used >= root->mem_size)
	{
		emv_set_error_code(TLV_TREE_PARAM_ERROR);
		return FALSE;
	}
	else
	{
		unsigned int i = 0;
		for ( i = 0; i < root->mem_size; i++)
		{
			root->mem_buf[i] = 0x00;
		}

		return tlv_tree_build_recount_internal(&(root->mem_used), root->root);
	}
}

//内部：tlv树结构递归
unsigned int tlv_tree_buffer_build_internal(unsigned char* buf, unsigned int buf_size, unsigned int *offset
	,tlv_tree_node_t* node)
{
	if (buf == NULL || buf_size == 0 || offset == NULL || node == NULL)
	{
		emv_set_error_code(TLV_TREE_PARAM_ERROR);
		return FALSE;
	}
	else
	{
		//保存自己的tag
		if (!emv_tlv_set_tag(buf, buf_size, offset, node->tag))
		{
			return FALSE;
		}

		//保存自己的len
		if (!emv_tlv_set_len(buf,buf_size,offset,node->len))
		{
			return FALSE;
		}

		//如果是父节点，自己的value则是子节点组成
		if (node->is_a_template)
		{
			if (node->child != NULL)
			{
				unsigned int reuslt = FALSE;
				reuslt = tlv_tree_buffer_build_internal(buf, node->len + *offset, offset, node->child);
				if (!reuslt)
				{
					return reuslt;
				}
			}
		}
		//如果不是父节点，那么value就自己组成
		else
		{
			if (!emv_tlv_set_value(buf, buf_size, offset, node->len, node->val))
			{
				return FALSE;
			}
		}

		//保存兄弟节点
		if (node->bother != NULL)
		{
			return tlv_tree_buffer_build_internal(buf, buf_size, offset, node->bother);
		}

		return TRUE;
	}
}

//tlv树结构构建成buf
unsigned int tlv_tree_buffer_build(tlv_tree_root_t* root)
{
	if (root == NULL || root->root == NULL ||
		root->mem_buf == NULL || root->mem_size == 0 || root->mem_used >= root->mem_size)
	{
		emv_set_error_code(TLV_TREE_PARAM_ERROR);
		return FALSE;
	}
	else
	{
		unsigned int mem_used = 0;

		//先重新计算长度
		unsigned int result = tlv_tree_build_recount(root);
		if (!result) return result;
		//再递归整理buffer
		return tlv_tree_buffer_build_internal(root->mem_buf,root->mem_size,&(mem_used),root->root);
	}
}

//打印一个tlv结构
void print_tlv(unsigned int level, tlv_tree_node_t* node, unsigned int is_no_buffer)
{
	unsigned int i = 0;
	unsigned char buf[256];
	for (i = 0; i < level; i++)
	{
		emv_debug_print_block(DEFAULT_DEBUG_LEVEL, INFO_LEVEL)("-");
	}

	emv_debug_print_block(DEFAULT_DEBUG_LEVEL, INFO_LEVEL)("[%04x][%04x]", node->tag, node->len);

	emv_debug_print_block(DEFAULT_DEBUG_LEVEL, INFO_LEVEL)("[");
	if (is_no_buffer == TRUE)
	{
		for (i = 0; i < node->len; i++)
		{
			emv_debug_print_block(DEFAULT_DEBUG_LEVEL, INFO_LEVEL)("%02x ", node->val[i]);
		}
	}
	emv_debug_print_block(DEFAULT_DEBUG_LEVEL, INFO_LEVEL)("]\n");
}

//内部：递归打印树结构
void print_tlv_internal(unsigned int level, tlv_tree_node_t* tlv)
{
	//打印自己
	print_tlv(level, tlv, !(tlv->is_a_template));

	//打印孩子
	if (tlv->child != NULL)
	{
		level++;
		print_tlv_internal(level, tlv->child);
		level--;
	}

	//打印兄弟
	if (tlv->bother != NULL)
	{
		print_tlv_internal(level, tlv->bother);
	}

}

//打印tlv树结构
unsigned int tlv_tree_buffer_print(tlv_tree_root_t* root)
{
	if (root == NULL || root->root == NULL)
	{
		emv_set_error_code(TLV_TREE_PARAM_ERROR);
		return FALSE;
	}
	else
	{
		print_tlv_internal(0, root->root);
		return TRUE;
	}
}

/* END OF FILE */
