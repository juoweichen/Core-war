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
**	format_instruction()
**	Create a format in queue, check if last format in queue is a empty label
**	
**	input: 
**		1. tokens start with operations
**		2. asm main structure
**	return: 
**		errlog, if not error return NULL
**	
**	1. if there's not queue, create it
**	2. check if last format in queue is only with label
**	3. if true, combine current instruction with last format
**	4. if false, make a new format to store instruction
*/
char 	*format_instruction(t_token *token, t_asm *asms)
{
	char *errlog;

	if (token == NULL)
		return ("Incorrect instruction");
	errlog = NULL;
	if (asms->formats == NULL)
		asms->formats = queue_init();
	if (asms->formats->last && is_previous_label(asms->formats->last->data))
		errlog = ins_pre_format(token, asms->formats->last->data, asms->op_dict);
	else
		errlog = ins_new_format(token, asms->formats, asms->op_dict);
	return (errlog);
}

/*
**	format_label()
**	create a format only with label and set bsize to 0 in formats queue
**	
**	input: 
**		<t_token> tokens start with label
**		<t_asm>	asm main structure
**	return: 
**		<char *> errlog, if not error return NULL
**	
**	1. if there's not queue or no dict, create it
**	2. put label to local format, I try not to use too much malloc
**	3. set address, if it's first, address = 0, 
**		if not first, address = last address + last bsize
**	4. push local format to formats queue
*/
char	*format_label(t_token *token, t_asm *asms)
{
	t_format	f;

	if (token == NULL)
		return ("Incorrect label");
	ft_bzero(&f, sizeof(t_format));
	if (asms->formats == NULL)
		asms->formats = queue_init();
	if (asms->label_dict == NULL)
		asms->label_dict = dict_init();
	f.label = ft_strdup(ft_strctrim(token->data, ':'));
	if (asms->formats->last == NULL)
		f.address = 0;
	else
		f.address = ((t_format *)asms->formats->last->data)->address +
			((t_format *)asms->formats->last->data)->bsize;
	dict_add(asms->label_dict, f.label, &f.address, sizeof(int *));
	qpush(asms->formats, &f, sizeof(t_format));
	return (NULL);
}

/*
**	formalizer()
**	Read instruction line, formalize it
**	
**	input: 
**		<t_token> instruction tokens
**		<t_asm>	asm main structure
**	return: 
**		<char *> errlog, if not error return NULL
**	
**	1. test if instruction match LABEL: OP ARG
**	2. test if instruction match LABEL:
**	3. test if instruction match OP ARG
**	4. if none, return with error
*/
char 	*formalizer(t_token	*token, t_asm *asms)
{
	char *errlog;

	errlog = NULL;
	if (token == NULL)
		return (NULL);
	if (token->type == T_LAB)
	{
		errlog = format_label(token, asms);
		if (token->next && token->next->type == T_OP)
			errlog = format_instruction(token->next, asms); // TODO: join errlog
	}
	else if (token->type == T_OP)
		errlog = format_instruction(token, asms);
	else
		errlog = "illegal instruction";
	return (errlog);
}

/*
**	get_instructions()
**	Read instruction line, formalize it
**	
**	input: 
**		<int> champ file descriptor
**		<t_asm>	asm main structure
**	return: 
**		<char *> errlog, if not error return NULL
**	
**	1. Read every line under header
**	2. tokenize it
**	3. send tokens to formalizer
*/
char	*get_instructions(int fd, t_asm *asms)
{
	char 	*line;
	t_token	*token;
	char	*errlog;

	// TODO: handle comment
	errlog = NULL;
	while (get_next_line(fd, &line))
	{
		token = tokenize(line, asms);
		// test
		print_token(token);
		if ((errlog = formalizer(token, asms)) != NULL)
		{
			free_token_list(token);
			ft_strdel(&line);
			return (errlog);
		}
		free_token_list(token);
		ft_strdel(&line);
	}
	asms->champ_size = ((t_format *)asms->formats->last->data)->address +
		((t_format *)asms->formats->last->data)->bsize;
	return (NULL);
}
