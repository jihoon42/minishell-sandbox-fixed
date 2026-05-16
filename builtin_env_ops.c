/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_ops.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkim2 <jkim2@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 20:45:00 by jkim2             #+#    #+#             */
/*   Updated: 2026/05/16 20:45:00 by jkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(char **env)
{
	int	i;

	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

char	**dup_env(char **src)
{
	char	**dst;
	int		i;

	i = 0;
	while (src[i])
		i++;
	dst = (char **)malloc(sizeof(char *) * (i + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (src[i])
	{
		dst[i] = ft_strdup(src[i]);
		if (!dst[i])
			return (dst[i] = NULL, free_env(dst), NULL);
		i++;
	}
	dst[i] = NULL;
	return (dst);
}

char	*env_get(char **env, char *key)
{
	int		i;
	char	*value;

	i = 0;
	while (env && env[i])
	{
		value = check_env_key(env[i], key);
		if (value)
			return (value);
		i++;
	}
	return (NULL);
}

int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
