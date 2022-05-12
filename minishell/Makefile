CFLAGS = -Wall -Wextra -Werror -Iinclude
CC = gcc

# brew info readline
# 인텔 맥 ( 클러스터 PC X )
# READLINE_LIB 	= -lreadline -L/usr/local/opt/readline/lib
# READLINE_INC	= -I/usr/local/opt/readline/include

# 인텔 맥 ( 클러스터 PC O )
READLINE_LIB 	= -lreadline -L /Users/$(USER)/.brew/opt/readline/lib
READLINE_INC	= -I /Users/$(USER)/.brew/opt/readline/include

# M1 맥 ( 클러스터 PC X )
# READLINE_LIB	= -lreadline -L/opt/homebrew/opt/readline/lib
# READLINE_INC	= -I/opt/homebrew/opt/readline/include

SRCS = srcs/main.c \
		srcs/cmd/execute.c \
		srcs/cmd/execute_util.c \
		srcs/cmd/built_in.c \
		srcs/cmd/pipe.c \
		srcs/builtins/ft_cd.c \
		srcs/builtins/ft_pwd.c \
		srcs/builtins/ft_env.c \
		srcs/builtins/ft_exit.c \
		srcs/builtins/ft_echo.c \
		srcs/builtins/ft_unset.c \
		srcs/builtins/ft_export.c \
		srcs/builtins/ft_export2.c \
		srcs/utils/env.c \
		srcs/utils/env2.c \
		srcs/utils/signal.c \
		srcs/utils/minishell_util1.c \
		srcs/utils/error.c \
		srcs/utils/ft_free.c \
		srcs/parse/parser.c \
		srcs/parse/heredoc.c \
		srcs/parse/ft_split_cmds.c \
		srcs/parse/set_is_path.c \
		srcs/parse/parse_cmds.c \
		srcs/parse/set_cmd_list.c \
		srcs/list/cmd_list.c \
		srcs/list/redir_list.c \
		srcs/redirection/redirection.c \

LIBFT = libft/libft.a

NAME = minishell

OBJS = $(SRCS:.c=.o)

all:  $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(READLINE_INC) $(READLINE_LIB)

$(LIBFT):
	@make -C ./libft

%.o: %.c
	$(CC) $(CFLAGS) $(READLINE_INC) -c $< -o $@

clean:
	@make clean -C libft/
	@rm -rf $(OBJS)

fclean: clean
	@make fclean -C libft/
	@rm -rf $(NAME) $(OBJS)

re: fclean all
