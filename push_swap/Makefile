# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jinyoo <jinyoo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/14 15:13:17 by jinyoo            #+#    #+#              #
#    Updated: 2022/01/19 19:34:17 by jinyoo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC= gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude
NAME = push_swap

SRCS =	src/push_swap/main.c \
		src/push_swap/operation/deque.c \
		src/push_swap/operation/operations.c \
		src/push_swap/operation/operation_list.c \
		src/push_swap/sort/push_swap.c \
		src/push_swap/error/error.c
OBJS = $(SRCS:.c=.o)

SRC_UTILS =	src/util/ft_atoi.c \
			src/util/ft_putstr.c \
			src/util/ft_isdigit.c
OBJ_UTILS = $(SRC_UTILS:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS) $(OBJ_UTILS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(OBJ_UTILS)

.o: .c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJS)
	@rm -rf $(OBJ_UTILS)

fclean: clean
	@rm -rf $(NAME)

re: fclean all
