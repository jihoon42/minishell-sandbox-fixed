/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_logical.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkim2 <jkim2@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 06:35:19 by jkim2             #+#    #+#             */
/*   Updated: 2026/05/17 06:35:30 by jkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*combine_path(char *current, char *path)
{
	char	*tmp;
	char	*combined;

	if (path[0] == '/')
		return (ft_strdup(path));
	tmp = ft_strjoin(current, "/");
	if (!tmp)
		return (NULL);
	combined = ft_strjoin(tmp, path);
	free(tmp);
	return (combined);
}

static int	resolve_components(char **parts)
{
	int		r;
	int		w;
	char	*cur;

	r = 0;
	w = 0;
	while (parts[r])
	{
		cur = parts[r];
		parts[r++] = NULL;
		if (!cur[0] || ft_strcmp(cur, ".") == 0)
			free(cur);
		else if (ft_strcmp(cur, "..") == 0)
		{
			free(cur);
			if (w > 0)
				free(parts[--w]);
		}
		else
			parts[w++] = cur;
	}
	parts[w] = NULL;
	return (w);
}

static char	*build_string(char **parts, int n)
{
	char	*result;
	char	*tmp;
	int		i;

	if (n == 0)
		return (ft_strdup("/"));
	result = ft_strdup("");
	i = 0;
	while (result && i < n)
	{
		tmp = ft_strjoin(result, "/");
		free(result);
		if (!tmp)
			return (NULL);
		result = ft_strjoin(tmp, parts[i++]);
		free(tmp);
	}
	return (result);
}

char	*build_logical_pwd(char *current_pwd, char *path)
{
	char	*combined;
	char	**parts;
	char	*result;
	int		n;

	combined = combine_path(current_pwd, path);
	if (!combined)
		return (NULL);
	parts = ft_split(combined, '/');
	free(combined);
	if (!parts)
		return (NULL);
	n = resolve_components(parts);
	result = build_string(parts, n);
	free(parts);
	return (result);
}
