/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoung <sjoung@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 00:00:00 by sjoung            #+#    #+#             */
/*   Updated: 2026/03/31 00:00:00 by sjoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_redir(int type)
{
	return (type >= TOKEN_REDIR_IN && type <= TOKEN_REDIR_APPEND);
}

t_exec	*parse_redir_argv(t_exec *exec, t_token **token)
{
	while (*token && (*token)->type != TOKEN_PIPE)
	{
		if (is_redir((*token)->type))
		{
			if (!(*token)->next || (*token)->next->type != TOKEN_WORD)
				return (NULL);
			if (!add_redir_lst(exec, (*token)->type, (*token)->next->s))
				return (NULL);
			*token = (*token)->next->next;
		}
		else if ((*token)->type == TOKEN_WORD)
		{
			if (!add_argv(exec, (*token)->s))
				return (NULL);
			*token = (*token)->next;
		}
		else
			return (NULL);
	}
	return (exec);
}

t_exec	*parse_exec(t_token **token)
{
	t_exec	*exec;

	if (!*token || (*token)->type == TOKEN_PIPE)
		return (NULL);
	exec = init_exec();
	if (!exec)
		return (NULL);
	if (!parse_redir_argv(exec, token))
		return (delete_exec_lst(&exec), NULL);
	if (*token && (*token)->type == TOKEN_PIPE)
	{
		exec->pipe_to_next = 1;
		*token = (*token)->next;
		if (!*token || (*token)->type == TOKEN_PIPE)
			return (delete_exec_lst(&exec), NULL);
	}
	return (exec);
}

static void	append_exec(t_exec **head, t_exec **cur, t_exec *new)
{
	if (!*head)
		*head = new;
	else
		(*cur)->next = new;
	*cur = new;
}

t_exec	*parse_all(t_token *tokens)
{
	t_exec	*head;
	t_exec	*cur;
	t_exec	*new;

	head = NULL;
	cur = NULL;
	while (tokens)
	{
		new = parse_exec(&tokens);
		if (!new)
			return (delete_exec_lst(&head), NULL);
		append_exec(&head, &cur, new);
	}
	return (head);
}
