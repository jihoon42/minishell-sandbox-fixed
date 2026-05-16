/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkim2 <jkim2@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 20:45:00 by jkim2             #+#    #+#             */
/*   Updated: 2026/05/16 20:45:00 by jkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_heredoc_path(void)
{
	static int	idx;
	char		*num;
	char		*path;

	num = ft_itoa(idx++);
	if (!num)
		return (NULL);
	path = ft_strjoin("/tmp/.minishell_new_heredoc_", num);
	free(num);
	return (path);
}

static int	write_heredoc(char *path, char *delim)
{
	int		fd;
	char	*line;

	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd < 0)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
	return (0);
}

static int	process_heredoc(t_redir *redir)
{
	char	*path;

	path = get_heredoc_path();
	if (!path)
		return (-1);
	if (write_heredoc(path, redir->file) < 0)
		return (free(path), -1);
	free(redir->file);
	redir->file = path;
	return (0);
}

int	collect_heredocs(t_exec *exec)
{
	t_redir	*redir;

	while (exec)
	{
		redir = exec->redirs;
		while (redir)
		{
			if (redir->type == TOKEN_HERE_DOC && process_heredoc(redir) < 0)
				return (-1);
			redir = redir->next;
		}
		exec = exec->next;
	}
	return (0);
}
