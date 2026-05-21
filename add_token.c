/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoung <sjoung@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 00:00:00 by sjoung            #+#    #+#             */
/*   Updated: 2026/05/21 23:30:20 by sjoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_redir_in(char **line, t_token **head)
{
	(*line)++;
	if (**line == '<')
	{
		if (!add_token_lst(head, TOKEN_HERE_DOC, ft_strdup("<<")))
			return (0);
		(*line)++;
	}
	else if (!add_token_lst(head, TOKEN_REDIR_IN, ft_strdup("<")))
		return (0);
	return (1);
}

int	add_pipe(char **line, t_token **head)
{
	if (!add_token_lst(head, TOKEN_PIPE, ft_strdup("|")))
		return (0);
	(*line)++;
	return (1);
}

int	add_redir_out(char **line, t_token **head)
{
	(*line)++;
	if (**line == '>')
	{
		if (!add_token_lst(head, TOKEN_REDIR_APPEND, ft_strdup(">>")))
			return (0);
		(*line)++;
	}
	else if (!add_token_lst(head, TOKEN_REDIR_OUT, ft_strdup(">")))
		return (0);
	return (1);
}
