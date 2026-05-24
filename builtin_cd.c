/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkim2 <jkim2@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 06:45:31 by jkim2             #+#    #+#             */
/*   Updated: 2026/05/17 07:04:38 by jkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_logical_pwd(t_shell *sh)
{
	char	*pwd;
	char	cwd[1024];

	pwd = env_get(sh->env, "PWD");
	if (is_current_pwd(pwd))
		return (ft_strdup(pwd));
	if (getcwd(cwd, sizeof(cwd)))
		return (ft_strdup(cwd));
	return (ft_strdup(""));
}

static void	cd_update_env(t_shell *sh, char *old_logical, char *path)
{
	char	*new_logical;
	char	cwd[1024];

	new_logical = build_logical_pwd(old_logical, path);
	env_set(&sh->env, "OLDPWD", old_logical);
	if (new_logical && *new_logical)
		env_set(&sh->env, "PWD", new_logical);
	else if (getcwd(cwd, sizeof(cwd)))
		env_set(&sh->env, "PWD", cwd);
	free(new_logical);
}

static char	*resolve_cd_path(t_exec *cmd, t_shell *sh)
{
	char	*path;

	if (!cmd->argv[1])
	{
		path = env_get(sh->env, "HOME");
		if (!path)
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (path);
	}
	if (cmd->argv[1][0] == '-' && cmd->argv[1][1] == '\0')
	{
		path = env_get(sh->env, "OLDPWD");
		if (!path)
			return (ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2), NULL);
		ft_putendl_fd(path, 1);
		return (path);
	}
	return (cmd->argv[1]);
}

int	builtin_cd(t_exec *cmd, t_shell *sh)
{
	char	*path;
	char	*old_logical;

	if (cmd->argv[1] && cmd->argv[2])
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), 1);
	if (cmd->argv[1] && cmd->argv[1][0] == '\0')
		return (0);
	path = resolve_cd_path(cmd, sh);
	if (!path)
		return (1);
	old_logical = get_logical_pwd(sh);
	if (chdir(path) != 0)
	{
		free(old_logical);
		ft_putstr_fd("minishell: cd: ", 2);
		perror(path);
		return (1);
	}
	cd_update_env(sh, old_logical, path);
	free(old_logical);
	return (0);
}
