/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoung <sjoung@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 00:00:00 by sjoung            #+#    #+#             */
/*   Updated: 2026/03/31 00:00:00 by sjoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_redir_lst(t_redir **head)
{
	t_redir	*node;

	while (*head)
	{
		node = (*head)->next;
		free((*head)->file);
		free(*head);
		*head = node;
	}
}

t_exec	*add_redir_lst(t_exec *exec, int type, char *file, int had_quote)
{
	t_redir	*data;
	t_redir	*cur;

	data = (t_redir *)malloc(sizeof(t_redir));
	if (!data)
		return (NULL);
	data->type = type;
	data->file = ft_strdup(file);
	data->had_quote = had_quote;
	data->next = NULL;
	if (!exec->redirs)
		exec->redirs = data;
	else
	{
		cur = exec->redirs;
		while (cur->next)
			cur = cur->next;
		cur->next = data;
	}
	return (exec);
}
