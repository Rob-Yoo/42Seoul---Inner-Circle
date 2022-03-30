# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jinyoo <jinyoo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/23 14:31:23 by jinyoo            #+#    #+#              #
#    Updated: 2022/03/28 17:26:14 by jinyoo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC= cc
CFLAGS = -Wall -Wextra -Werror -Iinclude
NAME = philo

SRCS =	src/main.c \
		src/threading.c \
		src/phils_state.c \
		src/error_handler.c \
		src/print_state.c \
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