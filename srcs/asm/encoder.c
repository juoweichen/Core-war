/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by zaz               #+#    #+#             */
/*   Updated: 2013/11/06 14:21:46 by zaz              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/asm.h"
# include "../../includes/lexer.h"
# include "../../includes/op.h"

/*
**	write_int_move_pos
**	write 32bits integer to the current positon of string, 
**	will move position at the same time
**
**	input: 
**		1. current string position
**		2. target interger
**		3. write size
**	return: 
**		void
**	
**	1. read integer bits backward(bid endian?)
**	2. put to pos, move pos forward
*/
void	write_int_move_pos(char **pos, int num, size_t size)
{
	int i;

	i = size - 1;
	while (i >= 0)
	{
		**pos = (char)(num >> (8 * i));
		(*pos)++;
		i--;
	}
}
/*
**	head_encoder
**	encode header, write to file
**
**	input: 
**		1. current string position, start at begining
**		2. asm main structure
**	return: 
**		errlog, if not error return NULL
**	
**	1. write magic numbers, move the position at the same time
**	2. write name to current position, move the position
**	3. write champion bytes size, move the position
**	4. write comment, move to the begin of instruction
*/
void head_encoder(char **pos, t_asm *asms)
{
	write_int_move_pos(pos, COREWAR_EXEC_MAGIC, 4);
	ft_strcpy(*pos, asms->header.prog_name);
	(*pos) += PROG_NAME_LENGTH + 4;
	write_int_move_pos(pos, asms->champ_size, 4);
	ft_strcpy(*pos, asms->header.comment);
	(*pos) += COMMENT_LENGTH + 4;
}

int get_code_bytes(t_format	*format, t_op *opinfo)
{
	int i;
	int code_bytes;

	code_bytes = 0;
	i = 0;
	
	printf("op: %s\n", opinfo->name);
	while (i < MAX_ARGS_NUMBER - 1)
	{
		// test
		// print_bits(code_bytes);
		// printf("\n");

		if (format->args[i] != NULL)
		{
			// test
			// printf("i: %d, nb: %d\n", i, opinfo->nb_arg);
			if (format->args[i]->type == T_REG)
				code_bytes += REG_CODE;
			else if (format->args[i]->type == T_DIR)
				code_bytes += DIR_CODE;
			else if (format->args[i]->type == T_IND)
				code_bytes += IND_CODE;
		}
		code_bytes = code_bytes << 2;
		i++;
	}
	return (code_bytes);
}

void encode_regular(char *arg, char **pos, int size)
{
	int num;

	if (!arg)
		return ;
	num = 0;
	if (!ft_isdigit_str(arg))
		return ;
	num = ft_atoi(arg);
	write_int_move_pos(pos, num, size);
}

// TODO: error check
// TODO: 5 arguments!
void encode_label(char *arg, char **pos, int size, t_format *format, t_asm *asms)
{
	int address_offset;
	int *la;

	address_offset = 0;
	if (!arg)
		return ;
	// check if label match
	printf("looking for label: %s\n", arg);
	if ((la = dict_get(asms->label_dict, arg)) == NULL)
		return ; // label not found
	address_offset = *la - format->address;
	printf("label %s locate at address: %d, currrent offset: %d\n", arg, *la, address_offset);
	write_int_move_pos(pos, address_offset, size);
}

// TODO: error check
void encode_register(char *arg, char **pos, int size)
{
	int reg_num;

	if (!arg)
		return ;
	reg_num = 0;
	if (!ft_isdigit_str(arg))
		return ;
	if ((reg_num = ft_atoi(arg)) > REG_NUMBER)
		return ;	// errlog
	write_int_move_pos(pos, reg_num, size);
}

// TODO: error check
// TODO: Too many argumenets
void arg_encoder(char *arg, char **pos, int size, t_format *format, t_asm *asms)
{
	printf("arg: %s\n", arg);
	if (!arg)
		return ;
	if (*arg == 'r')
		encode_register(arg + 1, pos, size);
	else if (*arg == ':')
		encode_label(arg + 1, pos, size, format, asms);
	else
		encode_regular(arg, pos, size);
}

/*
**	ins_encoder
**	encode instruction format to bytes, write to file
**
**	input: 
**		1. current string position, start at the exe code
**		2. asm main structure
**	return: 
**		errlog, if not error return NULL
**	
**	1. pop a instruction from formats, get the op from op_dict
**	2. write opcode
**	3. write code bytes, some op don't need code bytes set to 0
**	4. 
*/
void	ins_encoder(char **pos, t_asm *asms)
{
	t_format	*format;
	t_op		*opinfo;
	int			code_bytes;
	int			i;

	while (qis_empty(asms->formats) != TRUE)
	{
		format = qpop(asms->formats);
		opinfo = dict_get(asms->op_dict, format->op);
		write_int_move_pos(pos, opinfo->opcode, 1);	
		code_bytes = get_code_bytes(format, opinfo);
		printf("code bytes: %x\n", code_bytes);
		// if don't need code_bytes, opinfo->code_bytes = 0 write 0 byte to file
		write_int_move_pos(pos, code_bytes, opinfo->code_bytes);
		
		i = 0;
		while (i < opinfo->nb_arg)
		{
			if (format->args[i]->type == T_REG)
				arg_encoder(format->args[i]->data, pos, 1, format, asms);
			else if (format->args[i]->type == T_DIR)
				arg_encoder(format->args[i]->data + 1, pos, DIR_SIZE -
					opinfo->dir_size * 2, format, asms);
			else if (format->args[i]->type == T_IND)
				arg_encoder(format->args[i]->data, pos, 2, format, asms);
			i++;
		}
	}
}