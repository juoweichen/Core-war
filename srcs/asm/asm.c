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
#include <sys/stat.h>

void	write_cor(char *champ_name)
{
	int fd = 0;

	champ_name = ft_strjoin_btw(champ_name, "cor", '.');

	if ((fd = open(champ_name, O_RDWR | O_CREAT | O_APPEND | O_TRUNC)) == -1 ||
		chmod(champ_name, S_IRWXU) == -1)
	{
		perror("Create fails");
		exit(0);
	}

	int h1 = 0x0b;
	int h2 = 0x68;
	int h3 = 0x01;
	int h4 = 0x0007;
	int h5 = 0x0001;
	
	write(fd, &h1, 1);
	write(fd, &h2, 1);
	write(fd, &h3, 2);
	write(fd, &h4, 2);
	write(fd, &h5, 2);

	close(fd);
}

// Only check op name for now
int is_ins(t_token *t, t_asm *asm_s)
{
	if (dict_get(asm_s->op_dict, t->data) == NULL)
		return (FALSE);
	return (TRUE);
}

// if last char is LABEL_CHAR && if all char is LABEL_CHARS
int	is_label(t_token *t)
{
	int i;
	int len;

	if (t == NULL)
		return (FALSE);
	len = ft_strlen(t->data);
	i = 0;
	while (i < len - 1)
	{
		if (ft_strchr(LABEL_CHARS, t->data[i++]) == NULL)
			return (FALSE);
	}
	if (t->data[i] != LABEL_CHAR)
		return (FALSE);
	return (TRUE);
}

// void	format_ins(t_token *token, t_asm *asm_s)
// {
// 	int 	op_i;
// 	t_format format;
// 	t_token		*ptr;

// 	format.label = token->data;
// 	format.op = token->next->data;
// 	op_i = search_op_table(format.op);
// 	format.bsize += 
// 	// get ins size & ptr
// 	ptr = token->next->next;
// 	while (ptr != NULL)
// 	{
// 		size += get_arg(&format, token);
// 		ptr = ptr->next;
// 	}
	
// 	// take previous address, count current address
	
// }

// Identify which kinds of type for this token
// type 1: LABEL: INS ARG
// type 2: LABEL:
// type 3: INS ARG
// type 4: EMPTY LINE
char *get_one_instruction(t_token *token, t_asm *asm_s)
{
	asm_s = NULL;

	if (is_label(token))
	{
		if (is_ins(token->next, asm_s))
		{
			printf("type 1: LABEL: INS ARG");
		}	
		else
		{
			printf("type 2: LABEL:");
		}
	}
	else if (is_ins(token, asm_s))
	{
		printf("type 3: INS ARG");
	}
	else
	{
		printf("type 4: EMPTY LINE");
	}
	printf("\n");
	return (NULL);
}

char *read_champ(char *champ, t_asm *asm_s)
{
	int 	fd;
	char 	*line;
	t_token	*token;
	char	*errlog;

	// open champ file
	if ((fd = open(champ, O_RDONLY)) == -1)
		return ("Champ file error");
	// get name and comment
	// TODO: order doesn't matter
	if ((errlog = get_champ_name(fd, asm_s)) != NULL ||
		(errlog = get_champ_comment(fd, asm_s)) != NULL)
		return (errlog);
	// test
	printf("name: %s\n", asm_s->header.prog_name);
	printf("comment: %s\n", asm_s->header.comment);

	// init queue
	if (asm_s->fq == NULL)
		asm_s->fq = queue_init();

	// get instructions
	while (get_next_line(fd, &line))
	{
		printf("line ==> %s\n", line);
		// TODO: handle comment
		token = tokenize(line);
		// formalize token
		if ((errlog = get_one_instruction(token, asm_s)) != NULL)
		{
			free_token_list(token);
			ft_strdel(&line);
			return (errlog);
		}
		free_token_list(token);
		ft_strdel(&line);
	}
	close(fd);
	return (NULL);
}

void 	get_optable(t_asm *asm_s)
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

void init_asm(t_asm *asm_s)
{
	int i;

	// init asm_s
	ft_bzero(asm_s, sizeof(t_asm));

	// store op table
	get_optable(asm_s);
	
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

int		main(int argc, char **argv)
{
	t_asm	asm_s;
	char 	*errlog;
	t_op *o;

	if (argc == 2)
	{
		init_asm(&asm_s);

		// read .s file
		if ((errlog = read_champ(argv[1], &asm_s)) != NULL)
		{
			perror(errlog);
			exit(1);
		}
		// encode

		// write to .cor file
		write_cor(argv[1]);
	}
	else
		ft_printf("usage: ./asm <your_champ.s>\n");
	return (0);
}