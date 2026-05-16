/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_wait.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkim2 <jkim2@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 20:45:00 by jkim2             #+#    #+#             */
/*   Updated: 2026/05/16 20:45:00 by jkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_to_status(int status)
{
	int	sig;

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
		return (128 + sig);
	}
	return (1);
}

int	wait_children(pid_t last_pid)
{
	pid_t	done;
	int		status;
	int		last_status;

	last_status = 0;
	done = wait(&status);
	while (done > 0)
	{
		if (done == last_pid)
			last_status = status;
		done = wait(&status);
	}
	return (wait_to_status(last_status));
}
