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

void	write_cor()
{
	int fd = 0;

	if ((fd = open("test.cor", O_RDWR | O_CREAT | O_APPEND | O_TRUNC)) == -1)
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

		// test write to file
		write_cor();
	}
	else
		ft_printf("usage: ./asm <your_champ.s>\n");
	return (0);
}