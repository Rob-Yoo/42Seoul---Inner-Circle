# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jinyoo <jinyoo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/06 15:19:41 by jinyoo            #+#    #+#              #
#    Updated: 2022/01/07 18:38:03 by jinyoo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC= gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude
SERVER = server
CLIENT = client

SRC_SERVER =	src/server/server.c
OBJ_SERVER = $(SRC_SERVER:.c=.o)

SRC_CLIENT =	src/client/client.c
OBJ_CLIENT = $(SRC_CLIENT:.c=.o)

SRC_UTIL =	src/util/ft_atoi.c \
			src/util/ft_putnbr.c \
			src/util/ft_putstr.c
OBJ_UTIL = $(SRC_UTIL:.c=.o)

.PHONY: all clean fclean re

all: $(CLIENT) $(SERVER)

$(SERVER): $(OBJ_SERVER) $(OBJ_UTIL)
	$(CC) $(CFLAGS) -o $(SERVER) $(OBJ_SERVER) $(OBJ_UTIL)

$(CLIENT): $(OBJ_CLIENT) $(OBJ_UTIL)
	$(CC) $(CFLAGS) -o $(CLIENT) $(OBJ_CLIENT) $(OBJ_UTIL)

.o: .c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_CLIENT)
	@rm -rf $(OBJ_SERVER)
	@rm -rf $(OBJ_UTIL)


fclean: clean
	@rm -rf $(CLIENT) $(SERVER)

re: fclean all
