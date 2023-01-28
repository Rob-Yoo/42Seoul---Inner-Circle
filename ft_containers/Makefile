# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
<<<<<<< HEAD
#    By: jinyoo <jinyoo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/13 16:06:34 by jinyoo            #+#    #+#              #
#    Updated: 2023/01/28 18:05:11 by jinyoo           ###   ########.fr        #
=======
#    By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/18 20:33:04 by jinyoo            #+#    #+#              #
#    Updated: 2022/07/18 20:35:55 by jinyoo           ###   ########.fr        #
>>>>>>> origin
#                                                                              #
# **************************************************************************** #

CXX = c++
<<<<<<< HEAD
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
SRCS = main.cpp
NEWSRCS = new_main.cpp
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
=======
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -I./
NAME = ft_containers
SRCS =	main.cpp
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
	@$(MAKE) clean
	@$(MAKE) all
>>>>>>> origin
