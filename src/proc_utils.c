/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:12:49 by paugonca          #+#    #+#             */
/*   Updated: 2023/06/09 17:14:54 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_path(char *cmd, char **env)
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

static void	proc_exec(char *arg, char **env)
{
	char	**cmd;
	int		p;
	char	*path;

	p = 0;
	cmd = ft_split(arg, ' ');
	path = get_path(cmd[0], env);
	if (!path)
	{
		free_matrix(cmd);
		print_error("path not found.");
	}
	if (execve(path, cmd, env) == -1)
		print_error("execution failed.");
}	

void	proc_child(char **av, char **env, int *fd)
{
	int	inp;

	inp = open(av[1], O_RDONLY, 0777);
	if (inp == -1)
		print_error("failed to create input file descriptor.");
	dup2(fd[1], STDOUT_FILENO);
	dup2(inp, STDIN_FILENO);
	close(fd[0]);
	proc_exec(av[2], env);
}

void	proc_parent(char **av, char **env, int *fd)
{
	int	out;

	out = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (out == -1)
		print_error("failed to create output file descriptor.");
	dup2(fd[0], STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	close(fd[1]);
	proc_exec(av[3], env);
}
