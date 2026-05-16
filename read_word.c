/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoung <sjoung@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 00:00:00 by sjoung            #+#    #+#             */
/*   Updated: 2026/03/31 00:00:00 by sjoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*read_single_quote(char **line)
{
	int		i;
	char	*tmp;

	(*line)++;
	i = 0;
	while ((*line)[i] && (*line)[i] != '\'')
		i++;
	if (!(*line)[i])
		return (NULL);
	tmp = ft_substr(*line, 0, i);
	*line += i + 1;
	return (tmp);
}

static char	*read_double_quote(char **line, t_shell *sh)
{
	char	*result;
	char	*tmp;

	(*line)++;
	result = ft_strdup("");
	while (result && **line && **line != '"')
	{
		if (**line == '$')
			tmp = expand_variable(line, sh);
		else
		{
			tmp = ft_char_to_str(**line);
			(*line)++;
		}
		result = ft_strjoin_free(result, tmp);
	}
	if (!result || **line != '"')
		return (free(result), NULL);
	(*line)++;
	return (result);
}

static char	*read_plain(char **line)
{
	int		i;
	char	*tmp;

	i = 0;
	while ((*line)[i] && !ft_is_space((*line)[i])
		&& !ft_is_operator((*line)[i]) && (*line)[i] != '\''
		&& (*line)[i] != '"' && (*line)[i] != '$')
		i++;
	tmp = ft_substr(*line, 0, i);
	*line += i;
	return (tmp);
}

static char	*read_piece(char **line, t_shell *sh)
{
	if (**line == '\'')
		return (read_single_quote(line));
	if (**line == '"')
		return (read_double_quote(line, sh));
	if (**line == '$')
		return (expand_variable(line, sh));
	return (read_plain(line));
}

char	*read_word(char *line, t_token **head, t_shell *sh, int *flag)
{
	char	*result;
	char	*tmp;

	result = ft_strdup("");
	while (result && *line && !ft_is_space(*line) && !ft_is_operator(*line))
	{
		tmp = read_piece(&line, sh);
		if (!tmp)
		{
			free(result);
			return (NULL);
		}
		result = ft_strjoin_free(result, tmp);
	}
	if (!result || !add_token_lst(head, TOKEN_WORD, result))
		*flag = 0;
	return (line);
}
