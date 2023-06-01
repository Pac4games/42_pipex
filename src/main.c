/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:57:28 by paugonca          #+#    #+#             */
/*   Updated: 2023/06/01 17:09:41 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>

int	main(void)
{
	int	id;
	int	res;

	id = fork();
	if (id == 0)
		sleep(1);
	printf("Current ID: %d, Parent ID: %d\n", getpid(), getppid());
	res = wait(NULL);
	if (res == -1)
		printf("No children to wait for.\n");
	else
		printf("%d finished execution.\n", res);
	return (EXIT_SUCCESS);
}
