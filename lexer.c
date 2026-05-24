/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoung <sjoung@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 00:00:00 by sjoung            #+#    #+#             */
/*   Updated: 2026/03/31 00:00:00 by sjoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	last_token_type(t_token *head)
{
	if (!head)
		return (-1);
	while (head->next)
		head = head->next;
	return (head->type);
}

static int	lexer_state(char **line, t_token **head, t_shell *sh)
{
	int	flag;

	flag = 1;
	if (ft_is_space(**line))
		(*line)++;
	else if (**line == '&')
		return (delete_token_lst(head), 0);
	else if (**line == '|')
		flag = add_pipe(line, head);
	else if (**line == '<')
		flag = add_redir_in(line, head);
	else if (**line == '>')
		flag = add_redir_out(line, head);
	else if (last_token_type(*head) == TOKEN_HERE_DOC)
		*line = read_heredoc_delimiter(*line, head, &flag);
	else
		*line = read_word(*line, head, sh, &flag);
	if (!*line || !flag)
		return (delete_token_lst(head), 0);
	return (1);
}

int	lexer(char *line, t_token **head, t_shell *sh)
{
	while (ft_is_space(*line))
		line++;
	while (*line)
	{
		if (!lexer_state(&line, head, sh))
			return (0);
	}
	return (1);
}
