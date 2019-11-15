/* ************************************************************************** *//*                                                                            */
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
**	champ_encoder
**	create .cor file, encode header and instruction, wirte to .cor file
**
**	input: 
**		1. champ file name
**		2. asm main structure
**	return: 
**		errlog, if not error return NULL
**
**	1. create file name, create .cor file
**	2. allocate a string to wirte in the file
**	3. encode head
**	4. encode champ
**	5. write to file with string
*/
char *champ_encoder(char *champ, t_asm *asms)
{
	int 	fd;
	char 	*str;
	int		slen;
	char	*pos;

	champ = ft_strjoin_btw(champ, "cor", '.');
	if ((fd = open(champ, O_RDWR | O_CREAT | O_APPEND | O_TRUNC)) == -1 ||
		chmod(champ, S_IRWXU) == -1)
		return ("Champ file error");
	ft_strdel(&champ);
	slen = MAGIC_LENGTH + PROG_NAME_LENGTH + 4 + 4 + 
		COMMENT_LENGTH + 4 + asms->champ_size;
	// test
	printf("size: %d\n", asms->champ_size);
	str = ft_strnew(slen);
	pos = str;
	head_encoder(&pos, asms);
	ins_encoder(&pos, asms);
	write(fd, str, slen);
	close(fd);
	return (NULL);
}

/*
**	champ_reader()
**	read champ file, vaildation and formalize to encode-ready formats
**	
**	input: 
**		<char *> champ file name
**		<t_asm>	asm main structure
**	return: 
**		<char *> errlog, if not error return NULL
**	
**	1. open champ file
**	2. get name and comment from first and second lines of champ file
**	3. get instructions form rest of lines
**		formalized to encode-ready formats(queue)
**	4. close champ file
*/
char *champ_reader(char *champ, t_asm *asms)
{
	int 	fd;
	char	*errlog;

	if ((fd = open(champ, O_RDONLY)) == -1)
		return ("Champ file error");
	// TODO: order doesn't matter
	if ((errlog = get_champ_name(fd, asms)) != NULL ||
		(errlog = get_champ_comment(fd, asms)) != NULL)
		return (errlog);
	// test
	printf("name: %s\n", asms->header.prog_name);
	printf("comment: %s\n", asms->header.comment);

	if ((errlog = get_instructions(fd, asms)) != NULL)
		return (errlog);
	// test
	printf("formalization completed\n");
	print_format(asms);


	// TODO: free formats
	close(fd);
	return (NULL);
}

/*
**	main()
**	asm main, read champ file, formalize to encode-ready format
**	encode to bytes, write to .cor file
**	
**	input: 
**		argc, argv
**	return: 
**		0 if success
*/
int		main(int argc, char **argv)
{
	t_asm	asms;
	char 	*errlog;

	if (argc == 2)
	{
		init_asm(&asms);
		// read .s file
		if ((errlog = champ_reader(argv[1], &asms)) != NULL)
		{
			perror(errlog);
			exit(1);
		}
		// encode and write to .cor
		if ((errlog = champ_encoder(argv[1], &asms)) != NULL)
		{
			perror(errlog);
			exit(1);
		}
	}
	else
		ft_printf("usage: ./asm <your_champ.s>\n");
	return (0);
}