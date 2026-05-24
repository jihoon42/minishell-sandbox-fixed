/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoung <sjoung@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 00:00:00 by sjoung            #+#    #+#             */
/*   Updated: 2026/03/31 00:00:00 by sjoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

int	main(int argc, char **argv, char **envp)
{
	t_shell	sh;

	(void)argc;
	(void)argv;
	sh.env = dup_env(envp);
	if (!sh.env)
		return (1);
	sh.last_exit = 0;
	sh.should_exit = 0;
	sh.is_interactive = isatty(STDIN_FILENO);
	sh.ambiguous_redirect = 0;
	sh.term_saved = 0;
	g_signal = 0;
	disable_echoctl(&sh);
	setup_signals();
	run_loop(&sh);
	restore_terminal(&sh);
	free_env(sh.env);
	rl_clear_history();
	return (sh.last_exit);
}
