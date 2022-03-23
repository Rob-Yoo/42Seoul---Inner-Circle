# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/23 14:31:23 by jinyoo            #+#    #+#              #
#    Updated: 2022/03/23 14:32:19 by jinyoo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jinyoo <jinyoo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/14 15:13:17 by jinyoo            #+#    #+#              #
#    Updated: 2022/02/03 03:16:14 by jinyoo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC= gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude
NAME = philo

SRCS =	src/main.c
OBJS = $(SRCS:.c=.o)

# SRC_UTILS = src/util/ft_putstr.c \
# 			src/util/ft_strncmp.c \
# 			src/util/ft_split.c \
# 			src/util/ft_strchr.c \
# 			src/util/ft_isdigit.c
# OBJ_UTILS = $(SRC_UTILS:.c=.o)

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
