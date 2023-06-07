/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:57:28 by paugonca          #+#    #+#             */
/*   Updated: 2023/06/07 11:34:40 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(void)
{
	int	pid;
	int	file;
	int	wstatus;
	int	statusCode;
	
	pid = fork();
	file = open("pingResults.txt", O_WRONLY | O_CREAT, 0777);
	wstatus = 0;
	statusCode = 0;
	if (pid == -1 || file == -1)
		return (EXIT_FAILURE);
	else if (pid == 0)
	{
		if (execlp("ping", "ping", "-c", "1", "google.com", NULL) == -1)
		{
			printf("Program not found!\n");
			return (EXIT_FAILURE);
		}
	}
	else
	{
		wait(&wstatus);
		if (WIFEXITED(wstatus))
		{
			statusCode = WEXITSTATUS(wstatus);
			if (statusCode == EXIT_SUCCESS)
				printf("Success!\n");
			else
				printf("Failure\n");
		}
	}
	return (statusCode);
}
