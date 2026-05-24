/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkim2 <jkim2@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 06:44:30 by jkim2             #+#    #+#             */
/*   Updated: 2026/05/17 07:04:19 by jkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (!cmd->argv[1])
	{
		if (sh->is_interactive)
			ft_putstr_fd("exit\n", 2);
		return (sh->should_exit = 1, sh->last_exit);
	}
	if (!is_numeric(cmd->argv[1]))
	{
		if (sh->is_interactive)
			ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd->argv[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		sh->should_exit = 1;
		return (2);
	}
	if (cmd->argv[2])
		return (ft_putstr_fd("minishell: exit: too many arguments\n", 2), 1);
	if (sh->is_interactive)
		ft_putstr_fd("exit\n", 2);
	sh->should_exit = 1;
	return ((unsigned char)to_long(cmd->argv[1]));
}
