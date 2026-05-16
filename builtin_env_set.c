/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_set.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkim2 <jkim2@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 20:45:00 by jkim2             #+#    #+#             */
/*   Updated: 2026/05/16 20:45:00 by jkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	env_index(char **env, char *key)
{
	int		i;

	i = 0;
	while (env && env[i])
	{
		if (check_env_key(env[i], key))
			return (i);
		i++;
	}
	return (-1);
}

static char	*make_env_entry(char *key, char *value)
{
	char	*tmp;
	char	*entry;

	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (NULL);
	entry = ft_strjoin(tmp, value);
	free(tmp);
	return (entry);
}

int	env_set(char ***env, char *key, char *value)
{
	char	**new_env;
	int		i;
	int		pos;

	pos = env_index(*env, key);
	if (pos >= 0)
	{
		new_env = *env;
		free(new_env[pos]);
		new_env[pos] = make_env_entry(key, value);
		return (new_env[pos] == NULL);
	}
	i = argv_cnt(*env);
	new_env = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (1);
	pos = -1;
	while (++pos < i)
		new_env[pos] = (*env)[pos];
	new_env[i] = make_env_entry(key, value);
	new_env[i + 1] = NULL;
	free(*env);
	*env = new_env;
	return (new_env[i] == NULL);
}

int	env_unset(char ***env, char *key)
{
	int	i;
	int	j;

	i = env_index(*env, key);
	if (i < 0)
		return (0);
	free((*env)[i]);
	j = i;
	while ((*env)[j])
	{
		(*env)[j] = (*env)[j + 1];
		j++;
	}
	return (0);
}
