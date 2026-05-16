NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror
CFLAGS += -I/opt/homebrew/opt/readline/include
LDFLAGS = -L/opt/homebrew/opt/readline/lib -lreadline

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS = main.c \
       run_loop.c \
       laxer.c \
       read_word.c \
       expand_variable.c \
       add_token.c \
       token_lst.c \
       parse.c \
       argv_unit.c \
       redir_lst.c \
       exec_lst.c \
       execute_pipeline.c \
       execute_wait.c \
       apply_redirections.c \
       heredoc.c \
       heredoc_io.c \
       heredoc_cleanup.c \
       env_unit.c \
       builtin_env_ops.c \
       builtin_env_set.c \
       builtins.c \
       builtin_basic.c \
       builtin_cd_exit.c \
       builtin_export_unset.c \
       exec_path.c \
       char_utils.c \
       unit.c \
       signals.c \
       signals_heredoc.c \
       terminal.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(LDFLAGS)

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
