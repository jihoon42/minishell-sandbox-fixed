/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkim2 <jkim2@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 00:00:00 by jkim2             #+#    #+#             */
/*   Updated: 2026/05/17 00:00:00 by jkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sigint_heredoc_handler(int sig)
{
	g_signal = sig;
	write(1, "\n", 1);
	close(STDIN_FILENO);
}

void	setup_signals_heredoc(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = sigint_heredoc_handler;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
}
