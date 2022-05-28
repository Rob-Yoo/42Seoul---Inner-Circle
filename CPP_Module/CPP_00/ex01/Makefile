# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/26 17:27:45 by jinyoo            #+#    #+#              #
#    Updated: 2022/05/27 17:55:26 by jinyoo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC= c++
CFLAGS = -Wall -Wextra -Werror -Iinclude -std=c++98
NAME = phone_book

SRCS = srcs/main.cpp srcs/PhoneBook.cpp srcs/Contact.cpp
OBJS = $(SRCS:.cpp=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean all