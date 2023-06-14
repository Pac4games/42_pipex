/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:01:18 by paugonca          #+#    #+#             */
/*   Updated: 2023/06/14 11:56:56 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>
#include <unistd.h>

void	print_error(char *msg)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	free_matrix(char **matrix)
{
	int	p;

	p = 0;
	while (matrix[p])
		free(matrix[p++]);
	free(matrix);
}

int	get_next_line(char **line)
{
	int		p;
	int		res;
	char	*buf;
	char	c;

	p = 0;
	res = 0;
	buf = malloc(1000);
	if (!buf)
		return (-1);
	res = read(0, &c, 1);
	while (res && c != '\n' && c != '\0')
	{
		if (c != '\n' && c != '\0')
			buf[p] = c;
		p++;
		res = read(0, &c, 1);
	}
	buf[p++] = '\n';
	buf[p] = '\0';
	*line = buf;
	free(buf);
	return (res);
}

int	open_file(char *av, int p)
{
	int	fd;

	fd = 0;
	if (p == 0)
		fd = open(av, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (p == 1)
		fd = open(av, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (p == 2)
		fd = open(av, O_RDONLY, 0777);
	if (p == -1)
		print_error("failed to open file descriptor.");
	return (fd);
}
