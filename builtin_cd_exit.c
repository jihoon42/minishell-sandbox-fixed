/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkim2 <jkim2@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 20:45:00 by jkim2             #+#    #+#             */
/*   Updated: 2026/05/16 20:45:00 by jkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_cd(t_exec *cmd, t_shell *sh)
{
	char	*path;
	char	oldpwd[1024];
	char	cwd[1024];

	if (!cmd->argv[1])
		path = env_get(sh->env, "HOME");
	else
		path = cmd->argv[1];
	if (!path)
		return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
	if (!getcwd(oldpwd, sizeof(oldpwd)))
		oldpwd[0] = '\0';
	if (chdir(path) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(path);
		return (1);
	}
	env_set(&sh->env, "OLDPWD", oldpwd);
	if (getcwd(cwd, sizeof(cwd)))
		env_set(&sh->env, "PWD", cwd);
	return (0);
}

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static long	to_long(char *str)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str)
		result = result * 10 + *str++ - '0';
	return (result * sign);
}

int	builtin_exit(t_exec *cmd, t_shell *sh)
{
	if (sh->is_interactive)
		ft_putstr_fd("exit\n", 2);
	if (!cmd->argv[1])
		return (sh->should_exit = 1, sh->last_exit);
	if (!is_numeric(cmd->argv[1]))
	{
		ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
		sh->should_exit = 1;
		return (2);
	}
	if (cmd->argv[2])
		return (ft_putstr_fd("minishell: exit: too many arguments\n", 2), 1);
	sh->should_exit = 1;
	return ((unsigned char)to_long(cmd->argv[1]));
}
