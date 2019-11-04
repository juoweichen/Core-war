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

#include "../../includes/asm.h"

void	read_champ(char *champ)
{
	int fd;
	char *line;

	if ((fd = open(champ, O_RDONLY)) == -1)
	{
		perror("Champ not found");
		exit(0);
	}
	while (get_next_line(fd, &line))
	{
		ft_printf("%s\n", line);
	}
	close(fd);
}

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		// read .s file
		read_champ(argv[1]);
		// validation
		// validation_champ();
		// parsing to machine code
		// parse_champ();
		// store to .cor file
		// release_champ();
	}
	else
		ft_printf("usage: ./asm <your_champ.s>\n");
	return (0);
}