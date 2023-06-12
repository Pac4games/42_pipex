# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/29 14:41:29 by paugonca          #+#    #+#              #
#    Updated: 2023/06/12 16:47:09 by paugonca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= pipex

CC			= cc
CFLAGS		= -Wall -Wextra -Werror

RM			= rm -f
MKD			= mkdir

SRC_NAME	= main.c		\
			  extra_utils.c	\
			  proc_utils.c

SRC			= $(addprefix $(SRC_PATH)/, $(SRC_NAME))
OBJ			= $(patsubst $(SRC_PATH)/%.c, $(OBJ_PATH)/%.o, $(SRC))
DEPS		= ./libs/libft/libft.a ./libs/get_next_line/get_next_line.a

SRC_PATH	= ./src
OBJ_PATH	= ./obj

all: $(NAME)

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
$(NAME): $(DEPS) $(OBJ_PATH) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(DEPS) -o $(NAME)

LIBFT_PATH	= ./libs/libft
./libs/libft/libft.a: $(shell make -C $(LIBFT_PATH) -q libft.a)
	make bonus -C $(LIBFT_PATH)

GNL_PATH	= ./libs/get_next_line
./libs/get_next_line/get_next_line.a: $(shell make -C $(GNL_PATH) -q get_next_line.a || echo force)
	make -C $(GNL_PATH)

$(OBJ_PATH):
	$(MKD) -p obj

clean:
	make clean -C $(LIBFT_PATH)
	make clean -C $(GNL_PATH)
	$(RM) -r $(OBJ_PATH)

fclean: clean
	make fclean -C $(LIBFT_PATH)
	make fclean -C $(GNL_PATH)
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
