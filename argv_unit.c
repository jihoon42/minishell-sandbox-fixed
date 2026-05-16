/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_unit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoung <sjoung@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 00:00:00 by sjoung            #+#    #+#             */
/*   Updated: 2026/03/31 00:00:00 by sjoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	argv_cnt(char **argv)
{
	int	i;

	i = 0;
	if (!argv)
		return (0);
	while (argv[i])
		i++;
	return (i);
}

char	**add_argv(t_exec *exec, char *s)
{
	char	**data;
	int		i;
	int		size;

	size = argv_cnt(exec->argv);
	data = (char **)malloc(sizeof(char *) * (size + 2));
	if (!data)
		return (NULL);
	i = 0;
	while (i < size)
	{
		data[i] = exec->argv[i];
		i++;
	}
	data[i] = ft_strdup(s);
	data[i + 1] = NULL;
	free(exec->argv);
	exec->argv = data;
	return (data);
}

void	argv_free(char **argv)
{
	int	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}
