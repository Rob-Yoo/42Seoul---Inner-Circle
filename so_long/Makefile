# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jinyoo <jinyoo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/11 15:47:17 by jinyoo            #+#    #+#              #
#    Updated: 2022/03/17 02:29:26 by jinyoo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude

NAME = so_long

SRCS_DIR = ./src
SRCS = src/main.c src/init.c src/key_handler.c src/draw.c src/check_map.c
OBJS = $(SRCS:.c=.o)

# 외부라이브러리 모음 =================================================
LIB_NAME = ft
LIB_DIR = ./include/libft
LIB = $(addprefix $(LIB_DIR)/, libft.a)

MLX_NAME = mlx
MLX_DIR = ./include/minilibx_opengl_20191021
MLX = $(addprefix $(MLX_DIR)/, libmlx.a)

GNL_NAME = gnl
GNL_DIR = ./include/get_next_line
GNL = $(addprefix $(GNL_DIR)/, libgnl.a)

# 외부라이브러리 모음 ===================================================
.PHONY : all clean fclean re

$(NAME) : $(OBJS)
	$(MAKE) -C $(LIB_DIR) bonus
	$(MAKE) -C $(MLX_DIR) all
	$(MAKE) -C $(GNL_DIR) all
	$(CC) $(CFLAGS) -L$(LIB_DIR) -l$(LIB_NAME) -L$(MLX_DIR) -l$(MLX_NAME) \
			-L$(GNL_DIR) -l$(GNL_NAME) \
			-framework OpenGL -framework AppKit $^ -o $@
	# @install_name_tool -change libmlx.dylib ./include/minilibx_opengl_20191021/libmlx.a $(NAME)

$(SRCS_DIR)/%.o : $(SRCS_DIR)/%.c
	$(CC) $(CFLAGS) -I$(MLX_DIR) -I$(LIB_DIR) -I$(GNL_DIR) -c $< -o $@

all : $(NAME)

clean :
	@rm -rf $(OBJS)
	$(MAKE) -C $(LIB_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean
	$(MAKE) -C $(GNL_DIR) clean

fclean :
	@rm -rf $(NAME) $(OBJS)
	$(MAKE) -C $(LIB_DIR) fclean
	$(MAKE) -C $(MLX_DIR) clean
	$(MAKE) -C $(GNL_DIR) fclean

re : fclean all
