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
**	valid_header()
**	header_Validation
**
**	input: 
**		<t_token> header command tokens
**		<char *> comment string to compare, define in op.h
**		<size_t> comment length to compare, define in op.h
**		<char *> header asms->header->prog_name/comment pointer, 
**			if pass validation, cpy name/comment to this pointer.
**	return: 
**		<char *> errlog, if not error return NULL
**	
**	1. check if first token is ".name"/".comment"
**	2. trim out double quote at begin and end
**	3. check if name/comment too long
**	4. copy name/comment to asms->header->prog_name/comment
*/
char	*valid_header(t_token *token, char *cmd_str, size_t cmd_len, char *cmd)
{
	char *trimstr;

	// TODO: handle quotes(multiple line)
		// if find quote, get next line
	if (token && ft_strequ(token->data, cmd_str))
	{
		trimstr = ft_strctrim(token->next->data, '\"');
		if (ft_strlen(trimstr) < cmd_len)
			ft_strcpy(cmd, trimstr);
		else
			return ("Command too long");
	}
	else
		return ("Invalid command string");
	return (NULL);
}

/*
**	get_champ_comment()
**	Validate champ comment header
**
**	input: 
**		<int> champ file descriptor
**		<t_asm>	asm main structure
**	return: 
**		<char *> errlog, if not error return NULL
**	
**	1. get a line from champ file
**	2. tokenize line to token list
**	3. Check if it's in a vaild header form
**	4. free out
*/
char	*get_champ_comment(int fd, t_asm *asms)
{
	char	*line;
	t_token	*token;
	char	*errlog;
	
	// TODO: check human notes
	errlog = NULL;
	if (get_next_line(fd, &line))
	{
		token = tokenize(line, asms);
		errlog = valid_header(token, 
			COMMENT_CMD_STRING, COMMENT_LENGTH, asms->header.comment);
		free_token_list(token);
		ft_strdel(&line);
	}
	return (errlog);
}

/*
**	get_champ_name()
**	Validate champ name header
**
**	input: 
**		<int> champ file descriptor
**		<t_asm>	asm main structure
**	return: 
**		<char *> errlog, if not error return NULL
**	
**	1. get a line from champ file
**	2. tokenize line to token list
**	3. Check if it's in a vaild header form
**	4. free out
*/
char	*get_champ_name(int fd, t_asm *asms)
{
	char	*line;
	t_token	*token;
	char	*errlog;

	// TODO: check human notes
	errlog = NULL;
	if (get_next_line(fd, &line))
	{
		token = tokenize(line, asms);
		errlog = valid_header(token, 
			NAME_CMD_STRING, PROG_NAME_LENGTH, asms->header.prog_name);
		free_token_list(token);
		ft_strdel(&line);
	}
	return (errlog);
}

// Check header, TODO: order doesn't matter
// if this line is name: save to name
// if this line is comment: save to commemnt
// if name and comment are saved, return success
// if lost one or two, return fail
