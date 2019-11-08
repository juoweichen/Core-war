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

# include "../../includes/corewar.h"

int		check_champ_comment(t_token *token, t_asm *asm_s)
{
	char *cmtstr;

	// TODO: handle quotes(multiple line)
		// if find quote, get next line
	if (token && ft_strequ(token->data, COMMENT_CMD_STRING))
	{
		cmtstr = ft_strctrim(token->next->data, '\"');
		if (strlen(cmtstr) < COMMENT_LENGTH)
			ft_strcpy(asm_s->header.comment, cmtstr);
		else
			return (FALSE);
	}
	else
		return (FALSE);
	return (TRUE);
}

int		check_champ_name(t_token *token, t_asm *asm_s)
{
	char *namestr;

	// TODO: handle quotes(multiple line)
		// if find quote, get next line
	if (token && ft_strequ(token->data, NAME_CMD_STRING))
	{
		namestr = ft_strctrim(token->next->data, '\"');
		if (strlen(namestr) < PROG_NAME_LENGTH)
			ft_strcpy(asm_s->header.prog_name, namestr);
		else
			return (FALSE);
	}
	else
		return (FALSE);
	return (TRUE);
}

char	*get_champ_comment(int fd, t_asm *asm_s)
{
	char	*line;
	t_token	*token;
	
	// TODO: check human notes
	if (get_next_line(fd, &line))
	{
		token = tokenize(line);
		if (check_champ_comment(token, asm_s) == FALSE)
		{
			free_token_list(token);
			ft_strdel(&line);
			return ("Champ comment error");
		}
		free_token_list(token);
		ft_strdel(&line);
	}
	return (NULL);
}

char	*get_champ_name(int fd, t_asm *asm_s)
{
	char	*line;
	t_token	*token;

	// TODO: check human notes
	if (get_next_line(fd, &line))
	{
		token = tokenize(line);
		if (check_champ_name(token, asm_s) == FALSE)
		{
			free_token_list(token);
			ft_strdel(&line);
			return ("Champ name error");
		}
		free_token_list(token);
		ft_strdel(&line);
	}
	return (NULL);
}
