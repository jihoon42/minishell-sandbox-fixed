/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_cleanup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkim2 <jkim2@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 10:19:48 by jkim2             #+#    #+#             */
/*   Updated: 2026/05/25 08:17:23 by jkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define HEREDOC_PREFIX "/tmp/.minishell_new_heredoc_"

static int	is_collected_heredoc(char *file)
{
	size_t	len;

	len = ft_strlen(HEREDOC_PREFIX);
	return (file && ft_strncmp(file, HEREDOC_PREFIX, len) == 0);
}

void	cleanup_collected_heredocs(t_exec *exec)
{
	t_redir	*redir;

	while (exec)
	{
		redir = exec->redirs;
		while (redir)
		{
			if (redir->type == TOKEN_HERE_DOC
				&& is_collected_heredoc(redir->file))
				unlink(redir->file);
			redir = redir->next;
		}
		exec = exec->next;
	}
}
