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
**	put_argus_to_format()
**	iterate args, check if op and arg match
**	
**	input: 
**		1. tokens start with arguments
**		2. target format
**		3. operation info dict, for validate operation use
**	return: 
**		errlog, null if no error 
**	
**	1. get opinfo from op_dict
**	2. malloc args' spaces in format
**	3. validate arguments
**	4. Store those arguments with type to target format
**	5. add bsize
*/
char	*put_argus_to_format(t_token *token, t_format *format, t_dict *op_dict)
{
	int		arg_num;
	t_op	*opinfo;

	if (token == NULL)
		return ("operation no arguments");
	opinfo = dict_get(op_dict, format->op);
	arg_num = 0;
	format->args = (t_argu **)ft_memalloc(sizeof(t_argu *) * (opinfo->nb_arg + 1));
	while (token != NULL)
	{
		if (token->next == NULL && arg_num + 1 < opinfo->nb_arg)
			return ("Not enough arguments");
		if (arg_num > opinfo->nb_arg)
			return ("Too many arguments");
		if ((token->type & opinfo->args[arg_num]) == 0)
			return ("Incorrect argument format");
		format->args[arg_num] = (t_argu *)ft_memalloc(sizeof(t_argu));
		format->args[arg_num]->type = token->type;
		format->args[arg_num]->data = ft_strdup(token->data);
		format->bsize += token->type;
		arg_num++;
		token = token->next;
	}
	return (NULL);
}

/*
**	ins_new_format()
**	put instruction to a new format
**	
**	input: 
**		1. tokens start with operation
**		2. formats queue
**		3. operation info dict, for validate operation use
**	return: 
**		errlog, null if no error 
**	
**	1. put operation to format
**	2. add bsize to 2, +1 op & +1 byte code
**	3. put args to format
**	4. set address, if it's first, address = 0, 
**		if not first, address = last address + last bsize
**	5. push local format to formats queue
*/
char	*ins_new_format(t_token *token, t_queue *formats, t_dict *op_dict)
{
	t_format f;
	char *errlog;

	bzero(&f, sizeof(t_format));
	errlog = NULL;
	f.op = ft_strdup(token->data);
	f.bsize += 2;
	errlog = put_argus_to_format(token->next, &f, op_dict);
	if (formats->last == NULL)
		f.address = 0;
	else
		f.address = ((t_format *)formats->last->data)->address + 
			((t_format *)formats->last->data)->bsize;
	qpush(formats, &f, sizeof(t_format));
	return (errlog);
}

/*
**	ins_pre_format()
**	put instruction to previous format in queue
**	
**	input: 
**		1. tokens start with operation
**		2. previous format
**		3. operation info dict, for validate operation use
**	return: 
**		errlog, null if no error 
**	
**	1. put operation to pre format
**	2. add bsize to 2, +1 op & +1 byte code
**	3. put args to format
*/
char	*ins_pre_format(t_token *token, t_format *pre_format, t_dict *op_dict)
{
	pre_format->op = ft_strdup(token->data);
	pre_format->bsize += 2;
	return(put_argus_to_format(token->next, pre_format, op_dict));
}

/*
**	is_previous_label()
**	check if last format in queue is a empty label
**	
**	input: 
**		<t_format> previous format
**	return: 
**		true if last format in queue is a empty label
**	
**	1. check there's label and bsize is 0
*/
int		is_previous_label(t_format *pre_format)
{
	if (pre_format->label != NULL && pre_format->bsize == 0)
		return (TRUE);
	return (FALSE);
}