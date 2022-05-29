# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/29 14:56:08 by jinyoo            #+#    #+#              #
#    Updated: 2022/05/29 16:08:30 by jinyoo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC= c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -I./
NAME = zombie
SRCS =	main.cpp Zombie.cpp newZombie.cpp randomChump.cpp
OBJS = $(SRCS:.cpp=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CXXFLAGS) -o $(NAME) $(OBJS)

%.o: %.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re:
	@$(MAKE) clean
	@$(MAKE) all
