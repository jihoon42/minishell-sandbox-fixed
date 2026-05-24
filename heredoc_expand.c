/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkim2 <jkim2@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 00:00:00 by jkim2             #+#    #+#             */
/*   Updated: 2026/05/25 00:00:00 by jkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_heredoc_line(char *line, t_shell *sh)
{
	char	*result;
	char	*tmp;

	result = ft_strdup("");
	while (result && *line)
	{
		if (*line == '$')
			tmp = expand_variable(&line, sh);
		else
		{
			tmp = ft_char_to_str(*line);
			line++;
		}
		result = ft_strjoin_free(result, tmp);
	}
	return (result);
}

static char	*delim_quoted(char **line, int *had_q)
{
	int		i;
	char	quote;
	char	*tmp;

	quote = **line;
	*had_q = 1;
	(*line)++;
	i = 0;
	while ((*line)[i] && (*line)[i] != quote)
		i++;
	if (!(*line)[i])
		return (NULL);
	tmp = ft_substr(*line, 0, i);
	*line += i + 1;
	return (tmp);
}

static char	*delim_piece(char **line, int *had_q)
{
	int		i;
	char	*tmp;

	if (**line == '\'' || **line == '"')
		return (delim_quoted(line, had_q));
	i = 0;
	while ((*line)[i] && !ft_is_space((*line)[i])
		&& !ft_is_operator((*line)[i])
		&& (*line)[i] != '\'' && (*line)[i] != '"')
		i++;
	tmp = ft_substr(*line, 0, i);
	*line += i;
	return (tmp);
}

char	*read_heredoc_delimiter(char *line, t_token **head, int *flag)
{
	char	*result;
	char	*tmp;
	int		had_q;

	result = ft_strdup("");
	had_q = 0;
	while (result && *line && !ft_is_space(*line) && !ft_is_operator(*line))
	{
		tmp = delim_piece(&line, &had_q);
		if (!tmp)
			return (free(result), NULL);
		result = ft_strjoin_free(result, tmp);
	}
	if (!result || !add_token_lst(head, TOKEN_WORD, result, had_q))
		*flag = 0;
	return (line);
}
