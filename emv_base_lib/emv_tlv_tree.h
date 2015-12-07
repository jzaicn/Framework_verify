/**
 * @file    emv_tlv_tree.h
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
#ifndef _emv_tlv_tree_h_
#define _emv_tlv_tree_h_


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus  */


	/**************************************************************************
	 *                   G E N E R A L    C O N S T A N T S                   *
	 **************************************************************************/

	/**************************************************************************
	 *                             M A C R O S                                *
	 **************************************************************************/
#define TLV_TREE_MODULE_ERROR 0x0100
#define TLV_TREE_PARAM_ERROR	(	TLV_TREE_MODULE_ERROR	+	1	)
#define TLV_TREE_DECODE_ERROR	(	TLV_TREE_MODULE_ERROR	+	2	)
#define TLV_TREE_FULL_ERROR		(	TLV_TREE_MODULE_ERROR	+	2	)
	/**************************************************************************
	 *                         D A T A   T Y P E S                            *
	 **************************************************************************/


	typedef struct tlv_tree_node_s
	{
		unsigned int tag;
		unsigned int len;
		unsigned char* val;
		unsigned int is_a_template;
		struct tlv_tree_node_s* bother;
		struct tlv_tree_node_s* child;
	}tlv_tree_node_t;


	typedef struct tlv_tree_root_s
	{
		struct tlv_tree_node_s* node_array;
		unsigned int node_size;
		unsigned int node_used;
		
		unsigned char* mem_buf;
		unsigned int mem_size;
		unsigned int mem_used;

		tlv_tree_node_t* root;
	}tlv_tree_root_t;

	typedef enum tlv_decode_state_e
	{
		tlv_tree_decode_succeed,
		tlv_tree_decode_param_error,
		tlv_tree_decode_error,
		tlv_tree_decode_mem_error,
	}tlv_decode_state_t;


	typedef enum emv_return_e
	{
		emv_fail = 0,
		emv_pass = 1,
	}emv_return_t;



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
	unsigned int remove_byte(unsigned char* buf, unsigned int* buf_len, unsigned int* offset, unsigned char remove_char, unsigned is_left_to_right);

	//tlv之间会存在没有意义的00字节，移动offset，忽略他们
	unsigned int emv_tlv_decode_ignore_nosence_zero_byte_from_left(unsigned char* buf, unsigned int* buf_len, unsigned int* offset);

	//判断buffer是否用尽了
	unsigned int is_buffer_used_up(unsigned int buf_size, unsigned int offset);

	//树节点初始化
	unsigned int tree_node_init(tlv_tree_node_t* node);

	//树节点初始化
	unsigned int tree_node_array_init(tlv_tree_node_t* node, unsigned int node_array_size);

	//解析出来的node保存到数组中
	unsigned int save_node_2_node(tlv_tree_node_t *dst_node, tlv_tree_node_t* src_node);

	//从buffer中解析一个tlv
	unsigned int get_one_tlv(tlv_tree_node_t* node, unsigned char* buf, unsigned int buf_size, unsigned int* offset);

	//保存到队列中
	unsigned int save_tlv_node_and_set_upper_pointer(tlv_tree_root_t* root, tlv_tree_node_t** upper_pointer, tlv_tree_node_t* node);

	//*内部：tlv树解析，递归函数
	unsigned int tlv_tree_buffer_parse_internal(tlv_tree_root_t* root, unsigned char* buf, unsigned int buf_size, tlv_tree_node_t** upper_pointer);

	//tlv树解析
	unsigned int tlv_tree_buffer_parse(tlv_tree_root_t* root);

	//内部：tlv树结构递归
	unsigned int tlv_tree_buffer_build_internal(unsigned char* buf, unsigned int buf_size, unsigned int *offset
		, tlv_tree_node_t* node);

	//tlv树结构构建成buf
	unsigned int tlv_tree_buffer_build(tlv_tree_root_t* root);

	//打印一个tlv结构
	void print_tlv(unsigned int level, tlv_tree_node_t* node, unsigned int is_no_buffer);

	//内部：递归打印树结构
	void print_tlv_internal(unsigned int level, tlv_tree_node_t* tlv);

	//打印tlv树结构
	unsigned int tlv_tree_buffer_print(tlv_tree_root_t* root);


#ifdef __cplusplus
}
#endif /* __cplusplus  */


#endif /* _emv_tlv_tree_h_ */
/* END OF FILE */
