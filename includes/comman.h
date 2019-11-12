/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by zaz               #+#    #+#             */
/*   Updated: 2013/11/06 14:21:46 by zaz              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAN_H
# define COMMAN_H

# include "op.h"
# include "../libft/includes/libft.h"

typedef struct			s_token
{
	int					type;
	char				*data;
	struct s_token		*next;
}						t_token;

typedef struct	s_asm
{
	t_op		op_table[OP_NUM];	// array
	t_dict		*op_dict;			// dictionary
	t_header	header;
	t_queue		*formats;			// format queue
	int			champ_size;
}				t_asm;

#endif