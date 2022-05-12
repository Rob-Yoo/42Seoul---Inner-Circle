SRC_DIR = ./
NAME = libft.a

SRCS = $(addprefix ${SRC_DIR},\
ft_memset.c\
ft_bzero.c\
ft_memcpy.c\
ft_isalpha.c\
ft_isdigit.c\
ft_isascii.c\
ft_isalnum.c\
ft_isprint.c\
ft_toupper.c\
ft_tolower.c\
ft_strlen.c\
ft_strlcpy.c\
ft_strlcat.c\
ft_strchr.c\
ft_strrchr.c\
ft_strnstr.c\
ft_memccpy.c\
ft_memmove.c\
ft_memchr.c\
ft_memcmp.c\
ft_atoi.c\
ft_calloc.c\
ft_strdup.c\
ft_strncmp.c\
ft_putchar_fd.c\
ft_putstr_fd.c\
ft_putendl_fd.c\
ft_putnbr_fd.c\
ft_substr.c\
ft_strjoin.c\
ft_strtrim.c\
ft_itoa.c\
ft_strmapi.c\
ft_split.c)

BONUS_SRCS = $(addprefix ${SRC_DIR}, \
ft_lstnew.c \
ft_lstadd_front.c \
ft_lstsize.c \
ft_lstlast.c \
ft_lstadd_back.c \
ft_lstdelone.c \
ft_lstmap.c \
ft_lstclear.c \
ft_lstiter.c)

OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror

ifdef WITH_BONUS
	OBJECTS = $(OBJS) $(BONUS_OBJS)
else
	OBJECTS = $(OBJS)
endif

.PHONY: all
all: $(NAME)

.PHONY: bonus
bonus:
	@make WITH_BONUS=1 all

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJECTS)
	@ar rc $@ $^

.PHONY: clean
clean:
	@rm -f $(OBJS) $(BONUS_OBJS)

.PHONY: fclean
fclean: clean
	@rm -f $(NAME)

.PHONY: re
re: fclean all

