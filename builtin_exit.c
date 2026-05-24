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
#include <limits.h>

static int	accumulate(char *str, unsigned long *u)
{
	int	d;

	*u = 0;
	if (!*str)
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		d = *str - '0';
		if (*u > (ULONG_MAX - d) / 10)
			return (0);
		*u = *u * 10 + d;
		str++;
	}
	return (1);
}

static int	parse_long(char *str, long *out)
{
	unsigned long	u;
	int				sign;

	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if (!accumulate(str, &u))
		return (0);
	if (sign == 1 && u > (unsigned long)LONG_MAX)
		return (0);
	if (sign == -1 && u > (unsigned long)LONG_MAX + 1UL)
		return (0);
	if (sign == 1)
		*out = (long)u;
	else
		*out = -(long)u;
	return (1);
}

int	builtin_exit(t_exec *cmd, t_shell *sh)
{
	long	n;

	if (!cmd->argv[1])
	{
		if (sh->is_interactive)
			ft_putstr_fd("exit\n", 2);
		return (sh->should_exit = 1, sh->last_exit);
	}
	if (!parse_long(cmd->argv[1], &n))
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
	return ((unsigned char)n);
}
