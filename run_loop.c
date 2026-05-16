/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoung <sjoung@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 00:00:00 by sjoung            #+#    #+#             */
/*   Updated: 2026/03/31 00:00:00 by sjoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_syntax_error(t_shell *sh)
{
	ft_putstr_fd("minishell: syntax error\n", 2);
	sh->last_exit = 2;
}

static void	handle_line(char *line, t_shell *sh)
{
	t_token	*tokens;
	t_exec	*exec_list;

	tokens = NULL;
	exec_list = NULL;
	if (!lexer(line, &tokens, sh))
		return (set_syntax_error(sh));
	if (!tokens)
		return ;
	exec_list = parse_all(tokens);
	delete_token_lst(&tokens);
	if (!exec_list)
		return (set_syntax_error(sh));
	if (collect_heredocs(exec_list) == 0)
		sh->last_exit = execute_pipeline(exec_list, sh);
	else if (g_signal == SIGINT)
	{
		sh->last_exit = 130;
		g_signal = 0;
	}
	else
		sh->last_exit = 1;
	delete_exec_lst(&exec_list);
}

static void	check_signal(t_shell *sh)
{
	if (g_signal)
	{
		sh->last_exit = 128 + g_signal;
		g_signal = 0;
	}
}

void	run_loop(t_shell *sh)
{
	char	*line;

	while (!sh->should_exit)
	{
		line = readline(PROMPT);
		check_signal(sh);
		if (!line)
		{
			if (sh->is_interactive)
				write(1, "exit\n", 5);
			break ;
		}
		if (*line)
			add_history(line);
		handle_line(line, sh);
		free(line);
	}
}
