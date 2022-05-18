# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: plehtika <plehtika@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/04 12:00:52 by plehtika          #+#    #+#              #
#    Updated: 2022/01/25 10:59:04 by plehtika         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit

SRC_PATH = ./srcs/

SRCS = main make_sqr support validate_map

INCLUDES = -I./includes/ -I./libft/includes/

LIBS = -Llibft -lft

CFLAG = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	make -C libft
	gcc -o $(NAME) $(patsubst %,$(SRC_PATH)%.c,$(SRCS)) $(INCLUDES) $(LIBS) $(CFLAG)

clean:
	make -C libft clean

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
