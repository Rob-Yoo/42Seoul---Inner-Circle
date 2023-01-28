# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jinyoo <jinyoo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/13 16:06:34 by jinyoo            #+#    #+#              #
#    Updated: 2023/01/28 18:05:11 by jinyoo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
SRCS = main.cpp
NEWSRCS = test.cpp
HEADER = ./
NAME = a.out
OBJECTS = $(SRCS:.cpp=.o)
NEWOBJECTS = $(NEWSRCS:.cpp=.o)

all: $(NAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@ -I$(HEADER)

$(NAME): $(OBJECTS)
	$(CXX) $^ -o $@

test: $(NEWOBJECTS)
	$(CXX) $^ -o $@

clean:
	rm -rf $(OBJECTS)
	rm -rf $(NEWOBJECTS)

fclean: clean
	rm -rf $(NAME)
	rm -rf test
	rm -rf *.log

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re
