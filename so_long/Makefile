# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/11 15:47:17 by jinyoo            #+#    #+#              #
#    Updated: 2022/03/14 16:52:14 by jinyoo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC= cc
CFLAGS = -Wall -Wextra -Werror -Iinclude
# -Llib
MLX_FLAGS = -lmlx -framework OpenGL -framework AppKit
NAME = so_long

SRCS =	src/main.c \
		src/key_handler.c \
		src/init.c \
		src/draw_map.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) ${MLX_FLAGS} -o $(NAME) $(OBJS)
.o: .c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean all
