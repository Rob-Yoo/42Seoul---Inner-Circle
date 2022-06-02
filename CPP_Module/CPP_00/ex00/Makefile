# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/20 16:57:08 by jinyoo            #+#    #+#              #
#    Updated: 2022/06/02 21:24:22 by jinyoo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX= c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
NAME = megaphone

SRCS =	megaphone.cpp
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
