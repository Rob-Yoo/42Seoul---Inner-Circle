# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/26 17:27:45 by jinyoo            #+#    #+#              #
#    Updated: 2022/06/02 21:24:29 by jinyoo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX= c++
CXXFLAGS = -Wall -Wextra -Werror -Iinclude -std=c++98
NAME = phone_book

SRCS = srcs/main.cpp srcs/PhoneBook.cpp srcs/Contact.cpp
OBJS = $(SRCS:.cpp=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re:
	@${MAKE} fclean
	@${MAKE} all
