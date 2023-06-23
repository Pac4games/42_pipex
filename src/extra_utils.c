/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:46:47 by paugonca          #+#    #+#             */
/*   Updated: 2023/06/23 12:07:21 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error(char *msg)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	free_matrix(char **mtx)
{
	int	p;

	p = 0;
	while (mtx[p])
		free(mtx[p++]);
	free(mtx);
}

char	*get_path(const char *cmd, char **env)
{
	int		p;
	char	**paths;
	char	*tmp;
	char	*res;

	p = 0;
	while (ft_strnstr(env[p], "PATH", 4) == 0)
		p++;
	paths = ft_split(env[p] + 5, ':');
	p = 0;
	while (paths[p])
	{
		tmp = ft_strjoin(paths[p], "/");
		res = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!access(res, F_OK))
			return (res);
		free(res);
		p++;
	}
	free_matrix(paths);
	return (NULL);
}
