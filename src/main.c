/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:39:36 by paugonca          #+#    #+#             */
/*   Updated: 2023/06/21 14:05:50 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>

int	main(int ac, char **av, char **env)
{
	int		res;
	t_cmd	cmd1;
	t_cmd	cmd2;

	if (ac != 5)
		print_error("you must input 4 arguments.");
	proc_init(av, &cmd1, &cmd2);
	res = proc_exec(&cmd1, &cmd2, env);
	free_matrix(cmd1.args);
	free_matrix(cmd2.args);
	close(cmd1.fd[0]);
	close(cmd2.fd[1]);
	return (res);
}
