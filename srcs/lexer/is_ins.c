/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 15:23:59 by csinglet          #+#    #+#             */
/*   Updated: 2019/02/12 15:23:59 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/asm.h"
# include "../../includes/lexer.h"
# include "../../includes/op.h"

int 	is_label(char *data)
{
	int i;
	int len;

	if (data == NULL)
		return (FALSE);
	len = ft_strlen(data);
	i = 0;
	while (i < len - 1)
	{
		if (ft_strchr(LABEL_CHARS, data[i++]) == NULL)
			return (FALSE);
	}
	if (data[i] != LABEL_CHAR)
		return (FALSE);
	return (TRUE);
}

int		is_operation(char *data, t_asm *asms)
{
	if (data == NULL)
		return (FALSE);
	if (dict_get(asms->op_dict, data) != NULL)
		return (TRUE);
	return (FALSE);
}

int		is_register(char *data)
{
	if (data == NULL)
		return (FALSE);
	if (*data != REGISTER_CHAR)
		return (FALSE);
	data += 1;
	if (!ft_isdigit_str(data) || ft_atoi(data) > REG_NUMBER)
		return (FALSE);
	return (TRUE);
}

int		is_direct_mem(char *data)
{
	if (data == NULL)
		return (FALSE);
	if (*data != DIRECT_CHAR)
		return (FALSE);
	return (TRUE);
}


