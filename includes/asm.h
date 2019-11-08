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

#ifndef ASM_H
# define ASM_H

# include "../libft/includes/libft.h"

typedef struct	s_format
{
	int			bsize;
	int			address;
	char 		*op;
	char		**args;
	char 		*label;
}				t_format;

typedef struct	s_asm
{
	t_op		op_table[OP_NUM];
	t_dict		*op_dict;
	t_header	header;
	t_queue		*fq;		// format queue
	t_dict		*ldict; 	// label dict
}				t_asm;

/*
**	name_comment.c
*/
char	*get_champ_comment(int fd, t_asm *asm_s);
char	*get_champ_name(int fd, t_asm *asm_s);

#endif