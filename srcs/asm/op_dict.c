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
# include "../../includes/op.h"

/*
**	create_optable()
**	Store op table as an array in asms
**	
**	input: 
**		<t_asm>	asm main structure
**	return: 
**		void
**	
**	1. grap op array from op.c
**	2. memcpy to asms op table
** 
**	op_name: operation name
**	nb_arg: request argument number
**	args: argument types
**	opcode: operation code, from 1~16
**	cycle: wait cycle time before execution
**	description: description
**	code_bytes: is required code type
**	dir_size: 1 if T_dir is 2 bytes, 0 if 4 bytes
**	NOTE: Can add some more if needed
*/
void 	create_optable(t_asm *asm_s)
{
	t_op	op_tab[OP_NUM] =
	{
		{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
		{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
		{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
		{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
		{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
		{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
			"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
		{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
			"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
		{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
			"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
		{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
		{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
			"load index", 1, 1},
		{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
			"store index", 1, 1},
		{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
		{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
		{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
			"long load index", 1, 1},
		{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
		{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
		{0, 0, {0}, 0, 0, 0, 0, 0}
	};
	ft_memcpy(asm_s->op_table, op_tab, sizeof(t_op) * OP_NUM);
}

/*
**	init_asm()
**	bzero main structure asms, create op dictionary
**	Instead of op table, we use op dictionary for searching op info.
**	op_dict key : value => <char *>op_name : <t_op *>op_info
**	
**	input: 
**		<t_asm>	asm main structure
**	return: 
**		void
**	
**	1. bzero asms
**	2. Store op table to asm
**	3. Turn op table to op dictionary
*/
void init_asm(t_asm *asm_s)
{
	int i;

	ft_bzero(asm_s, sizeof(t_asm));
	create_optable(asm_s);
	
	// store op table to dict
	asm_s->op_dict = dict_init();
	i = 0;
	while (i < OP_NUM - 1)
	{
		dict_add(asm_s->op_dict, asm_s->op_table[i].name, 
			&asm_s->op_table[i], sizeof(t_op));
		i++;
	}
}
