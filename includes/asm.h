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
# include <sys/stat.h>
# include "comman.h"

typedef struct	s_argu
{
	t_arg_type	type;
	char		*data;	
}				t_argu;

typedef struct	s_format
{
	char 		*label;
	char 		*op;
	t_argu		**args;
	int			bsize;
	int			address;
}				t_format;

/*
**	op_dict.c
*/
void 	init_asm(t_asm *asms);
/*
**	name_comment.c
*/
char	*get_champ_comment(int fd, t_asm *asms);
char	*get_champ_name(int fd, t_asm *asms);
/*
**	instructions.c
*/
char	*get_instructions(int fd, t_asm *asms);
/*
**	helper.c
*/
void	print_format(t_asm *asms);
void	print_bits(unsigned char octet);
/*
**	encoder.c
*/
void	head_encoder(char **pos, t_asm *asms);
void 	ins_encoder(char **pos, t_asm *asms);
/*
**	format_ins.c
*/
int		is_previous_label(t_format *pre_format);
char	*ins_pre_format(t_token *token, t_format *pre_format, t_dict *op_dict);
char	*ins_new_format(t_token *token, t_queue *formats, t_dict *op_dict);
char	*put_argus_to_format(t_token *token, t_format *format, t_dict *op_dict);

#endif