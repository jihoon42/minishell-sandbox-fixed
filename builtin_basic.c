/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_basic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkim2 <jkim2@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 20:45:00 by jkim2             #+#    #+#             */
/*   Updated: 2026/05/16 20:45:00 by jkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_n_flag(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (i > 1);
}

int	builtin_echo(t_exec *cmd)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (cmd->argv[i] && is_n_flag(cmd->argv[i]))
	{
		newline = 0;
		i++;
	}
	while (cmd->argv[i])
	{
		ft_putstr_fd(cmd->argv[i], 1);
		if (cmd->argv[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
	return (0);
}

int	builtin_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
	{
		ft_putendl_fd(cwd, 1);
		return (0);
	}
	ft_putstr_fd("minishell: pwd: error\n", 2);
	return (1);
}

int	builtin_env(t_exec *cmd, t_shell *sh)
{
	int	i;

	if (cmd->argv[1])
	{
		ft_putstr_fd("minishell: env: too many arguments\n", 2);
		return (1);
	}
	i = 0;
	while (sh->env && sh->env[i])
	{
		ft_putendl_fd(sh->env[i], 1);
		i++;
	}
	return (0);
}
