/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkim2 <jkim2@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 00:00:00 by sjoung            #+#    #+#             */
/*   Updated: 2026/05/22 02:31:03 by jkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_status(int status)
{
	exit(status & 0xff);
}

static void	child_process(t_exec *cmd, t_shell *sh, int prev_fd, int pipe_fd[2])
{
	setup_signals_child();
	sh->is_interactive = 0;
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmd->pipe_to_next)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	if (apply_redirections(cmd->redirs) < 0)
		exit(1);
	if (!cmd->argv || !cmd->argv[0])
		exit(0);
	if (is_builtin(cmd->argv[0]))
		exec_status(exec_builtin(cmd, sh));
	exec_external(cmd, sh);
}

int	execute_single(t_exec *cmd, t_shell *sh)
{
	pid_t	pid;
	int		status;
	int		pipe_fd[2];

	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	if (!cmd->argv || !cmd->argv[0])
		return (run_redir_only(cmd));
	if (is_builtin(cmd->argv[0]))
		return (run_parent_builtin(cmd, sh));
	setup_signals_ignore();
	pid = fork();
	if (pid == 0)
		child_process(cmd, sh, -1, pipe_fd);
	waitpid(pid, &status, 0);
	setup_signals();
	return (wait_to_status(status));
}

static int	spawn_pipeline(t_exec *cmd, t_shell *sh, int *prev_fd, pid_t *pid)
{
	int	pipe_fd[2];

	if (cmd->pipe_to_next && pipe(pipe_fd) < 0)
		return (1);
	*pid = fork();
	if (*pid == 0)
		child_process(cmd, sh, *prev_fd, pipe_fd);
	if (*prev_fd != -1)
		close(*prev_fd);
	if (cmd->pipe_to_next)
	{
		close(pipe_fd[1]);
		*prev_fd = pipe_fd[0];
	}
	return (0);
}

int	execute_pipeline(t_exec *head, t_shell *sh)
{
	int		prev_fd;
	pid_t	pid;
	int		status;

	if (!head || !head->pipe_to_next)
		return (execute_single(head, sh));
	prev_fd = -1;
	setup_signals_ignore();
	while (head)
	{
		if (spawn_pipeline(head, sh, &prev_fd, &pid) != 0)
			return (1);
		head = head->next;
	}
	status = wait_children(pid);
	setup_signals();
	return (status);
}
