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

void	print_format(t_asm *asms)
{
	t_qnode *qp;
	t_format *f;
	int i;
	
	qp = asms->formats->first;
	while (qp != NULL)
	{
		f = qp->data;
		if (f == NULL)
			continue ;
		printf("label: %s", f->label);
		if (f->op != NULL)
		{
			printf(" | op: %s | args: ", f->op);
			i = 0;
			while (f->args[i] != NULL)
				printf("%s, ", f->args[i++]->data);
		}
		printf(" | address: %d | bsize: %d\n", f->address, f->bsize);
		qp = qp->next;
	}
}

void	print_bits(unsigned char octet)
{
	int shift = 7;
	unsigned char mask = 1;
	char out;

	while (shift >= 0)
	{
		out = ((octet >> shift) & mask) + '0';
		write(1, &out, 1);
		--shift;
	}
}