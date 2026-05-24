/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoung <sjoung@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 00:00:00 by sjoung            #+#    #+#             */
/*   Updated: 2026/03/31 00:00:00 by sjoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*init_token_data(int type, char *s, int had_quote)
{
	t_token	*data;

	data = (t_token *)malloc(sizeof(t_token));
	if (!data)
	{
		free(s);
		return (NULL);
	}
	data->type = type;
	data->s = s;
	data->had_quote = had_quote;
	data->next = NULL;
	return (data);
}

int	add_token_lst(t_token **head, int type, char *s, int had_quote)
{
	t_token	*node;
	t_token	*data;

	data = init_token_data(type, s, had_quote);
	if (!data)
		return (0);
	if (!*head)
	{
		*head = data;
		return (1);
	}
	node = *head;
	while (node->next)
		node = node->next;
	node->next = data;
	return (1);
}

void	delete_token_lst(t_token **head)
{
	t_token	*node;

	while (*head)
	{
		node = (*head)->next;
		free((*head)->s);
		free(*head);
		*head = node;
	}
}
