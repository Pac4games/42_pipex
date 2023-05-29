# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/29 14:41:29 by paugonca          #+#    #+#              #
#    Updated: 2023/05/29 15:02:26 by paugonca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= pipex

CC			= cc
CFLAGS		= -Wall -Wextra -Werror

RM			= rm -f
MKD			= mkdir

SRC_NAME	= main.c

SRC			= $(addprefix $(SRC_PATH)/, $(SRC_NAME))
OBJ			= $(patsubst $(SRC_PATH)/%.c, $(OBJ_PATH)/%.o, $(SRC))
DEPS		= ./libft/libft.a

SRC_PATH	= src/
OBJ_PATH	= obj/

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
$(NAME): $(DEPS) $(OBJ_PATH) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(DEPS) -o $(NAME)

LIBFT_PATH	= ./libft
./libft/libft.a: $(shell make -C $(LIBFT_PATH) -q libft.a)
	make bonus -C $(LIBFT_PATH)

$(OBJ_PATH):
	$(MKD) -p obj

clean:
	make clean -C $(LIBFT_PATH)
	$(RM) -r $(OBJ_PATH)

fclean: clean
	make fclean -C $(LIBFT_PATH)
	$(RM) $(NAME)

re: fclean all

.PHONY: all re clean fclean
