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

static char	*read_piece(char **line, t_shell *sh, int *keep_empty, int *had_q)
{
	int		i;
	char	*tmp;

	if (**line == '\'')
		return (*keep_empty = 1, *had_q = 1, read_single_quote(line));
	if (**line == '"')
		return (*keep_empty = 1, *had_q = 1, read_double_quote(line, sh));
	if (**line == '$')
		return (expand_variable(line, sh));
	*keep_empty = 1;
	i = 0;
	while ((*line)[i] && !ft_is_space((*line)[i])
		&& !ft_is_operator((*line)[i]) && (*line)[i] != '\''
		&& (*line)[i] != '"' && (*line)[i] != '$')
		i++;
	tmp = ft_substr(*line, 0, i);
	*line += i;
	return (tmp);
}

static char	*drop_empty(char *start, char *end, t_token *head, t_shell *sh)
{
	char	*orig;
	int		t;

	t = last_token_type(head);
	if (t < TOKEN_REDIR_IN || t > TOKEN_REDIR_APPEND)
		return (end);
	orig = ft_substr(start, 0, end - start);
	ft_putstr_fd("minishell: ", 2);
	if (orig)
	{
		ft_putstr_fd(orig, 2);
		free(orig);
	}
	ft_putstr_fd(": ambiguous redirect\n", 2);
	sh->ambiguous_redirect = 1;
	return (end);
}

char	*read_word(char *line, t_token **head, t_shell *sh, int *flag)
{
	char	*result;
	char	*tmp;
	char	*start;
	int		keep_empty;
	int		had_q;

	start = line;
	result = ft_strdup("");
	keep_empty = 0;
	had_q = 0;
	while (result && *line && !ft_is_space(*line) && !ft_is_operator(*line))
	{
		tmp = read_piece(&line, sh, &keep_empty, &had_q);
		if (!tmp)
			return (free(result), NULL);
		if (*tmp)
			keep_empty = 1;
		result = ft_strjoin_free(result, tmp);
	}
	if (result && !*result && !keep_empty)
		return (free(result), drop_empty(start, line, *head, sh));
	if (!result || !add_token_lst(head, TOKEN_WORD, result, had_q))
		*flag = 0;
	return (line);
}
