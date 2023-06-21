/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:35:56 by paugonca          #+#    #+#             */
/*   Updated: 2023/06/21 14:03:24 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_cmd
{
	char	*path;
	char	**args;
	int		pid;
	int		fd[2];
}				t_cmd;

//extra_utils.c
void	print_error(char *msg);
void	free_matrix(char **mtx);
char	*get_path(const char *cmd, char **env);
//proc_utils.c
void	proc_init(char **av, t_cmd *cmd1, t_cmd *cmd2);
int		proc_exec(t_cmd *cmd1, t_cmd *cmd2, char **env);

#endif
