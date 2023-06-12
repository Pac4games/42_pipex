/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:57:52 by paugonca          #+#    #+#             */
/*   Updated: 2023/06/12 15:55:51 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/wait.h>

# define TRUE 1
# define FALSE 0

//extra_utils.c
void	print_error(char *msg);
void	free_matrix(char **matrix);
//proc_utils.c
void	proc_child(char *av, char **env);
void	proc_sort(char *limiter, int ac);

#endif
