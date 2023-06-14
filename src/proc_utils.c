/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:12:49 by paugonca          #+#    #+#             */
/*   Updated: 2023/06/14 12:38:18 by paugonca         ###   ########.fr       */
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

void	proc_exec(char *arg, char **env)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(arg, ' ');
	path = get_path(cmd[0], env);
	if (!path)
	{
		free_matrix(cmd);
		print_error("valid path not found.");
	}
	if (execve(path, cmd, env) == -1)
		print_error("invalid command.");
}

void	proc_child(char *av, char **env)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		print_error("failed to open pipe.");
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		proc_exec(av, env);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

void	proc_sort(char *limiter, int ac)
{
	pid_t	buf;
	int		fd[2];
	char	*line;

	if (ac < 6)
		print_error("invalid syntax.");
	if (pipe(fd) == -1)
		print_error("failed to create pipe.");
	buf = fork();
	if (buf == 0)
	{
		close(fd[0]);
		while (get_next_line(&line))
		{
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
				exit(EXIT_SUCCESS);
			write(fd[1], line, ft_strlen(line));
		}
	}
	else
	{
		close(fd[0]);
		dup2(fd[0], STDIN_FILENO);
		wait(NULL);
	}
}
