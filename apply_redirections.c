/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoung <sjoung@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 18:23:29 by sjoung            #+#    #+#             */
/*   Updated: 2026/03/25 18:27:13 by sjoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_redir_file(t_redir *redir)
{
	int	fd;

	fd = -1;
	if (redir->type == TOKEN_REDIR_IN || redir->type == TOKEN_HERE_DOC)
		fd = open(redir->file, O_RDONLY);
	else if (redir->type == TOKEN_REDIR_OUT)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == TOKEN_REDIR_APPEND)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	return (fd);
}

static int	apply_one_redir(t_redir *redir)
{
	int	fd;
	int	target;

	fd = open_redir_file(redir);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(redir->file);
		return (-1);
	}
	if (redir->type == TOKEN_REDIR_IN || redir->type == TOKEN_HERE_DOC)
		target = STDIN_FILENO;
	else
		target = STDOUT_FILENO;
	dup2(fd, target);
	close(fd);
	if (redir->type == TOKEN_HERE_DOC)
		unlink(redir->file);
	return (0);
}

int	apply_redirections(t_redir *redir)
{
	while (redir)
	{
		if (apply_one_redir(redir) < 0)
			return (-1);
		redir = redir->next;
	}
	return (0);
}

int	run_redir_only(t_exec *cmd)
{
	int	saved_in;
	int	saved_out;
	int	ret;

	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	ret = 0;
	if (apply_redirections(cmd->redirs) < 0)
		ret = 1;
	dup2(saved_in, STDIN_FILENO);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_in);
	close(saved_out);
	return (ret);
}
