/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:57:28 by paugonca          #+#    #+#             */
/*   Updated: 2023/06/14 12:22:07 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	int	p;
	int	in;
	int	out;

	if (ac >= 5)
	{
		if (!ft_strncmp(av[1], "proc_sort", 0))
		{
			p = 3;
			out = open_file(av[ac - 1], 0);
			proc_sort(av[2], ac);
		}
		else
		{
			p = 2;
			out = open_file(av[ac - 1], 1);
			in = open_file(av[1], 2);
			dup2(in, STDIN_FILENO);
		}
		while (p < ac - 2)
			proc_child(av[p++], env);
		dup2(out, STDOUT_FILENO);
		proc_exec(av[ac - 2], env);
	}
	print_error("invalid arguments.");
}
