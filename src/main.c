/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:57:28 by paugonca          #+#    #+#             */
/*   Updated: 2023/05/31 17:49:10 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(void)
{
	int id = fork();
	int	n;
	int	p;

	if (id == 0)
		n = 1;
	else
	{
		n = 6;
		wait(0);
	}
	p = n;
	while (p < n + 5)
	{
		printf("%d ", p++);
		fflush(stdout);
	}
	if (id != 0)
		printf("\n");
	return (EXIT_SUCCESS);
}
