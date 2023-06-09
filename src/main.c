/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:57:28 by paugonca          #+#    #+#             */
/*   Updated: 2023/06/09 17:23:42 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	int		fd[2];
	pid_t	pid1;

	if (ac == 5)
	{
		if (pipe(fd) == -1)
			print_error("couldn't create pipe.");
		pid1 = fork();
		if (pid1 == -1)
			print_error("failed to fork process.");
		if (pid1 == 0)
			proc_child(av, env, fd);
		waitpid(pid1, NULL, 0);
		proc_parent(av, env, fd);
	}
	else
		print_error("invalid arguments.");
	return (EXIT_SUCCESS);
}
