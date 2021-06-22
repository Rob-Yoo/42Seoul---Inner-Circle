CC=gcc
CFLAGS =-Wall -Wextra -Werror
AR=ar
ARFLAGS=crs
NAME = libftprintf.a

SRCS =\
	ft_printf.c \
	ft_printf_c.c \
	ft_printf_int.c \
	ft_printf_s.c \
	ft_printf_u.c \
	ft_printf_utils.c \
	ft_printf_utils_2.c \
	ft_printf_utils_3.c

OBJS = $(SRCS:.c=.o)

HEADER = ./

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@ -I$(HEADER)

clean:
	@rm -rf $(OBJS) 

fclean:
	@rm -rf $(NAME) $(OBJS) 

re: 
	@make fclean
	@make all

