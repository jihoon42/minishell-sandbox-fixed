/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoung <sjoung@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 00:00:00 by sjoung            #+#    #+#             */
/*   Updated: 2026/03/31 00:00:00 by sjoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_variable(char **line, t_shell *sh)
{
	char	*key;
	char	*value;

	(*line)++;
	if (**line == '?')
	{
		(*line)++;
		return (ft_itoa(sh->last_exit));
	}
	if (ft_isdigit(**line))
	{
		(*line)++;
		return (ft_strdup(""));
	}
	if (ft_isalpha(**line) || **line == '_')
	{
		key = get_env_key(line);
		value = get_env_value(sh->env, key);
		free(key);
		return (value);
	}
	return (ft_strdup("$"));
}
