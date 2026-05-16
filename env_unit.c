/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_unit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoung <sjoung@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 00:00:00 by sjoung            #+#    #+#             */
/*   Updated: 2026/03/31 00:00:00 by sjoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_env_key(char *s, char *key)
{
	char	*p;

	p = s;
	while (*p && *p != '=')
		p++;
	if (!*p)
		return (NULL);
	if (ft_strncmp(s, key, p - s) == 0 && !key[p - s])
		return (p + 1);
	return (NULL);
}

char	*get_env_key(char **line)
{
	int		i;
	char	*key;

	i = 0;
	while (ft_isalnum((*line)[i]) || (*line)[i] == '_')
		i++;
	key = ft_substr(*line, 0, i);
	*line += i;
	return (key);
}

char	*get_env_value(char **envp, char *key)
{
	int		i;
	char	*result;

	i = 0;
	while (envp && envp[i])
	{
		result = check_env_key(envp[i], key);
		if (result)
			return (ft_strdup(result));
		i++;
	}
	return (ft_strdup(""));
}
