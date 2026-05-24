/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkim2 <jkim2@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 20:45:00 by jkim2             #+#    #+#             */
/*   Updated: 2026/05/25 08:16:56 by jkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*try_path(char *dir, char *cmd)
{
	char	*tmp;
	char	*full;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	full = ft_strjoin(tmp, cmd);
	free(tmp);
	if (!full)
		return (NULL);
	if (access(full, X_OK) == 0)
		return (full);
	free(full);
	return (NULL);
}

static char	*search_path(char *cmd, char *path_val)
{
	char	**dirs;
	char	*found;
	int		i;

	dirs = ft_split(path_val, ':');
	i = 0;
	while (dirs && dirs[i])
	{
		found = try_path(dirs[i], cmd);
		if (found)
			return (free_split(dirs), found);
		i++;
	}
	free_split(dirs);
	return (NULL);
}

char	*resolve_path(char *cmd, char **env)
{
	char	*path_val;

	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path_val = env_get(env, "PATH");
	if (!path_val)
		return (NULL);
	return (search_path(cmd, path_val));
}

void	exec_external(t_exec *cmd, t_shell *sh)
{
	char	*path;

	path = resolve_path(cmd->argv[0], sh->env);
	if (!path)
	{
		if (ft_strchr(cmd->argv[0], '/') && access(cmd->argv[0], F_OK) == 0)
		{
			ft_putstr_fd("minishell: ", 2);
			perror(cmd->argv[0]);
			exit(126);
		}
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(cmd->argv[0], 2);
		exit(127);
	}
	execve(path, cmd->argv, sh->env);
	ft_putstr_fd("minishell: ", 2);
	perror(cmd->argv[0]);
	free(path);
	exit(126);
}
