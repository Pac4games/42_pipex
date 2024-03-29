/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:53:13 by paugonca          #+#    #+#             */
/*   Updated: 2023/06/23 12:07:59 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	proc_create(t_cmd *cmd1, t_cmd *cmd2)
{
	int	fds[2];

	if (pipe(fds) == -1)
		print_error("failed to create pipes.");
	cmd1->fd[1] = fds[1];
	cmd2->fd[0] = fds[0];
}

static void	proc_cmd(t_cmd *cmd, char **env, int plug, int p)
{
	cmd->pid = fork();
	if (cmd->pid == -1)
		print_error("failed to fork process.");
	else if (cmd->pid == 0)
	{
		close(plug);
		if (cmd->fd[p] == -1)
			print_error("failed to use file descriptor.");
		dup2(cmd->fd[0], STDIN_FILENO);
		dup2(cmd->fd[1], STDOUT_FILENO);
		cmd->path = get_path(cmd->args[0], env);
		if (!cmd->path)
			print_error("failed to get PATH.");
		close(cmd->fd[0]);
		close(cmd->fd[1]);
		execve(cmd->path, cmd->args, env);
		free(cmd->path);
		exit(42);
	}
}

static int	proc_wait(t_cmd *cmd1, t_cmd *cmd2)
{
	int	res;
	int	end_pid;
	int	stat;

	res = 0;
	end_pid = 1;
	while (end_pid > 0)
	{
		end_pid = wait(&stat);
		if (end_pid == cmd1->pid)
			close(cmd1->fd[1]);
		else
			close(cmd2->fd[0]);
		if (end_pid == cmd2->pid)
		{
			if (WIFEXITED(stat))
				res = WEXITSTATUS(stat);
			else if (WIFSIGNALED(stat))
				res = WTERMSIG(stat);
			else
				res = 1;
		}
	}
	return (res);
}

void	proc_init(char **av, t_cmd *cmd1, t_cmd *cmd2)
{
	cmd1->fd[0] = open(av[1], O_RDONLY);
	cmd2->fd[1] = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (cmd1->fd[0] == -1 || cmd2->fd[1] == -1)
		print_error("failed to open file descriptor.");
	cmd1->args = ft_split(av[2], ' ');
	cmd2->args = ft_split(av[3], ' ');
	if (!cmd1->args)
		print_error("failed to parse first command.");
	else if (!cmd2->args)
		print_error("failed to parse second command.");
}

int	proc_exec(t_cmd *cmd1, t_cmd *cmd2, char **env)
{
	int	res;

	res = 0;
	proc_create(cmd1, cmd2);
	proc_cmd(cmd1, env, cmd2->fd[0], 0);
	proc_cmd(cmd2, env, cmd1->fd[1], 1);
	close(cmd1->fd[0]);
	close(cmd1->fd[1]);
	res = proc_wait(cmd1, cmd2);
	return (res);
}
