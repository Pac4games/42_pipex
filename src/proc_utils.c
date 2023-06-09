/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:12:49 by paugonca          #+#    #+#             */
/*   Updated: 2023/06/09 15:04:30 by paugonca         ###   ########.fr       */
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
	p = 0;
	while (paths[p])
		free(paths[p++]);
	free(paths);
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
		while (cmd[p])
			free(cmd[p++]);
		free(cmd);
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
