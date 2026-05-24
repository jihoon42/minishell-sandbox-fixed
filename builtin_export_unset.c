/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_unset.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkim2 <jkim2@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 20:45:00 by jkim2             #+#    #+#             */
/*   Updated: 2026/05/25 08:16:47 by jkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_export(t_shell *sh)
{
	int	i;

	i = 0;
	while (sh->env && sh->env[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(sh->env[i], 1);
		i++;
	}
	return (0);
}

static int	export_one(char *arg, t_shell *sh)
{
	char	*eq;
	char	*key;
	int		ret;

	if (!is_valid_identifier(arg))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	eq = ft_strchr(arg, '=');
	if (!eq)
		return (0);
	key = ft_strndup(arg, eq - arg);
	if (!key)
		return (1);
	ret = env_set(&sh->env, key, eq + 1);
	free(key);
	return (ret);
}

int	builtin_export(t_exec *cmd, t_shell *sh)
{
	int	i;
	int	ret;

	if (!cmd->argv[1])
		return (print_export(sh));
	i = 1;
	ret = 0;
	while (cmd->argv[i])
	{
		if (export_one(cmd->argv[i], sh))
			ret = 1;
		i++;
	}
	return (ret);
}

int	builtin_unset(t_exec *cmd, t_shell *sh)
{
	int	i;
	int	ret;

	i = 1;
	ret = 0;
	while (cmd->argv[i])
	{
		if (!is_valid_identifier(cmd->argv[i])
			|| ft_strchr(cmd->argv[i], '='))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(cmd->argv[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			ret = 1;
		}
		else
			env_unset(&sh->env, cmd->argv[i]);
		i++;
	}
	return (ret);
}
