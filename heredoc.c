/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkim2 <jkim2@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 20:45:00 by jkim2             #+#    #+#             */
/*   Updated: 2026/05/25 08:18:04 by jkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define HEREDOC_PREFIX "/tmp/.minishell_new_heredoc_"

static char	*get_heredoc_path(void)
{
	static int	idx;
	char		*num;
	char		*path;

	num = ft_itoa(idx++);
	if (!num)
		return (NULL);
	path = ft_strjoin(HEREDOC_PREFIX, num);
	free(num);
	return (path);
}

static void	write_heredoc_line(int fd, char *line, t_redir *redir, t_shell *sh)
{
	char	*expanded;

	if (!redir->had_quote)
	{
		expanded = expand_heredoc_line(line, sh);
		if (expanded)
		{
			ft_putendl_fd(expanded, fd);
			free(expanded);
		}
	}
	else
		ft_putendl_fd(line, fd);
}

static int	write_heredoc(char *path, t_redir *redir, t_shell *sh)
{
	int		fd;
	int		saved_stdin;
	char	*line;

	fd = open_heredoc_file(path, &saved_stdin);
	if (fd < 0)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (g_signal == SIGINT)
			return (abort_heredoc(path, fd, saved_stdin, line));
		if (!line || ft_strcmp(line, redir->file) == 0)
		{
			free(line);
			break ;
		}
		write_heredoc_line(fd, line, redir, sh);
		free(line);
	}
	close(fd);
	restore_heredoc_stdin(saved_stdin);
	return (0);
}

static int	process_heredoc(t_redir *redir, t_shell *sh)
{
	char	*path;

	path = get_heredoc_path();
	if (!path)
		return (-1);
	if (write_heredoc(path, redir, sh) < 0)
		return (free(path), -1);
	free(redir->file);
	redir->file = path;
	return (0);
}

int	collect_heredocs(t_exec *exec, t_shell *sh)
{
	t_redir	*redir;
	t_exec	*head;

	head = exec;
	while (exec)
	{
		redir = exec->redirs;
		while (redir)
		{
			if (redir->type == TOKEN_HERE_DOC
				&& process_heredoc(redir, sh) < 0)
				return (cleanup_collected_heredocs(head), -1);
			redir = redir->next;
		}
		exec = exec->next;
	}
	return (0);
}
