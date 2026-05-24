/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkim2 <jkim2@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 00:00:00 by sjoung            #+#    #+#             */
/*   Updated: 2026/05/17 06:57:17 by jkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "libft/libft.h"

# define TOKEN_BLANK 0
# define TOKEN_WORD 1
# define TOKEN_REDIR_IN 2
# define TOKEN_REDIR_OUT 3
# define TOKEN_HERE_DOC 4
# define TOKEN_REDIR_APPEND 5
# define TOKEN_PIPE 6
# define PROMPT "minishell$ "

typedef struct s_token
{
	int				type;
	char			*s;
	int				had_quote;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	int				type;
	char			*file;
	int				had_quote;
	struct s_redir	*next;
}	t_redir;

typedef struct s_exec
{
	char			**argv;
	t_redir			*redirs;
	int				pipe_to_next;
	struct s_exec	*next;
}	t_exec;

typedef struct s_shell
{
	char			**env;
	int				last_exit;
	int				should_exit;
	int				is_interactive;
	int				ambiguous_redirect;
	struct termios	orig_term;
	int				term_saved;
}	t_shell;

extern int	g_signal;

int		ft_strcmp(char *s1, char *s2);
char	*ft_strjoin_free(char *s1, char *s2);
char	*ft_strndup(const char *s, size_t n);
char	*ft_char_to_str(char c);
void	free_split(char **split);

void	free_env(char **env);
char	**dup_env(char **src);
char	*check_env_key(char *s, char *key);
char	*get_env_key(char **line);
char	*get_env_value(char **envp, char *key);
char	*env_get(char **env, char *key);
int		env_set(char ***env, char *key, char *value);
int		env_unset(char ***env, char *key);
int		is_valid_identifier(char *str);

t_token	*init_token_data(int type, char *s, int had_quote);
int		add_token_lst(t_token **head, int type, char *s, int had_quote);
void	delete_token_lst(t_token **head);
int		add_redir_in(char **line, t_token **head);
int		add_pipe(char **line, t_token **head);
int		add_redir_out(char **line, t_token **head);
int		lexer(char *line, t_token **head, t_shell *sh);
int		last_token_type(t_token *head);
char	*read_word(char *line, t_token **head, t_shell *sh, int *flag);
char	*read_heredoc_delimiter(char *line, t_token **head, int *flag);
char	*expand_heredoc_line(char *line, t_shell *sh);
char	*expand_variable(char **line, t_shell *sh);
int		ft_is_operator(char c);
int		ft_is_space(char c);

int		argv_cnt(char **argv);
char	**add_argv(t_exec *exec, char *s);
void	argv_free(char **argv);
void	delete_redir_lst(t_redir **head);
t_exec	*add_redir_lst(t_exec *exec, int type, char *file, int had_quote);
t_exec	*init_exec(void);
void	delete_exec_lst(t_exec **head);
t_exec	*parse_redir_argv(t_exec *exec, t_token **token);
t_exec	*parse_exec(t_token **token);
t_exec	*parse_all(t_token *tokens);

int		collect_heredocs(t_exec *exec, t_shell *sh);
int		open_heredoc_file(char *path, int *saved_stdin);
int		abort_heredoc(char *path, int fd, int saved_stdin, char *line);
void	restore_heredoc_stdin(int saved_stdin);
void	cleanup_collected_heredocs(t_exec *exec);
int		apply_redirections(t_redir *redir);
int		run_redir_only(t_exec *cmd);
int		execute_pipeline(t_exec *head, t_shell *sh);
int		execute_single(t_exec *cmd, t_shell *sh);
int		wait_to_status(int status);
int		wait_children(pid_t last_pid);
void	exec_external(t_exec *cmd, t_shell *sh);
char	*resolve_path(char *cmd, char **env);

int		is_builtin(char *cmd);
int		exec_builtin(t_exec *cmd, t_shell *sh);
int		run_parent_builtin(t_exec *cmd, t_shell *sh);
int		builtin_echo(t_exec *cmd);
int		builtin_pwd(t_shell *sh);
int		builtin_env(t_exec *cmd, t_shell *sh);
int		builtin_cd(t_exec *cmd, t_shell *sh);
int		builtin_exit(t_exec *cmd, t_shell *sh);
int		builtin_export(t_exec *cmd, t_shell *sh);
int		builtin_unset(t_exec *cmd, t_shell *sh);

int		is_current_pwd(char *pwd);
char	*build_logical_pwd(char *current_pwd, char *path);

void	run_loop(t_shell *sh);
void	setup_signals(void);
void	setup_signals_child(void);
void	setup_signals_heredoc(void);
void	setup_signals_ignore(void);
void	disable_echoctl(t_shell *sh);
void	restore_terminal(t_shell *sh);

#endif
