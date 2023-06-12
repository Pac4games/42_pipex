# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/24 17:01:52 by paugonca          #+#    #+#              #
#    Updated: 2023/04/17 15:37:52 by paugonca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	get_next_line.a

SRC =	get_next_line	\
		get_next_line_utils

CC =		cc
RM =		rm -f
CFLAGS =	-Wall -Werror -Wextra -I.

all:$(NAME)

$(NAME): $(SRC:=.o)
			ar rc $(NAME) $(SRC:=.o)
clean:
	$(RM)	$(SRC:=.o)
fclean: clean
		$(RM)	$(NAME)
re:	fclean	$(NAME)

.PHONY: all clean fclean re
