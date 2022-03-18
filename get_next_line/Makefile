# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/15 18:49:45 by jinyoo            #+#    #+#              #
#    Updated: 2022/03/18 15:44:01 by jinyoo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
NAME = libgnl.a

SRCS = get_next_line.c get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

.PHONY : all clean fclean re

all : $(NAME)

$(NAME) : $(OBJS)
	ar rc $@ $^

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean : $(OBJS)
	@rm -f $(OBJS)

fclean : $(OBJS) $(OBJS) $(NAME)
	@rm -f $^

re : fclean
	make all
