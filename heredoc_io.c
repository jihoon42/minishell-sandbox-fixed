/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_io.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkim2 <jkim2@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 00:00:00 by jkim2             #+#    #+#             */
/*   Updated: 2026/05/17 00:00:00 by jkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_heredoc_stdin(int saved_stdin)
{
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
	setup_signals();
}

int	open_heredoc_file(char *path, int *saved_stdin)
{
	int	fd;

	*saved_stdin = dup(STDIN_FILENO);
	if (*saved_stdin < 0)
		return (-1);
	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd < 0)
	{
		close(*saved_stdin);
		return (-1);
	}
	setup_signals_heredoc();
	return (fd);
}

int	abort_heredoc(char *path, int fd, int saved_stdin, char *line)
{
	free(line);
	close(fd);
	restore_heredoc_stdin(saved_stdin);
	unlink(path);
	return (-1);
}
