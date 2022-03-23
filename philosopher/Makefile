# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/23 14:31:23 by jinyoo            #+#    #+#              #
#    Updated: 2022/03/23 20:38:55 by jinyoo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC= gcc
CFLAGS = -Wall -Wextra -Werror -pthread -Iinclude
NAME = philo

SRCS =	src/main.c \
		utils/phil_utils.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

.o: .c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean all