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
**	write_int
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
**	3. 
**	4. 
*/
void ins_encoder(char **pos, t_asm *asms)
{
	t_format	*format;
	t_op		*op;

	while (!qis_empty(asms->formats))
	{
		format = qpop(asms->formats);
		op = dict_get(asms->op_dict, format->op);
		write_int_move_pos(pos, op->opcode, 1);
		
	}
}