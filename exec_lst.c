/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoung <sjoung@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 00:00:00 by sjoung            #+#    #+#             */
/*   Updated: 2026/03/31 00:00:00 by sjoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exec	*init_exec(void)
{
	t_exec	*exec;

	exec = (t_exec *)malloc(sizeof(t_exec));
	if (!exec)
		return (NULL);
	exec->argv = NULL;
	exec->redirs = NULL;
	exec->pipe_to_next = 0;
	exec->next = NULL;
	return (exec);
}

void	delete_exec_lst(t_exec **head)
{
	t_exec	*node;

	while (*head)
	{
		node = (*head)->next;
		argv_free((*head)->argv);
		delete_redir_lst(&((*head)->redirs));
		free(*head);
		*head = node;
	}
}
