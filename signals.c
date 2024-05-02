/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:41:46 by jhuber            #+#    #+#             */
/*   Updated: 2024/05/02 16:31:26 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int signum, siginfo_t *info, void *context) // Handles SIGINT, The process was “interrupted”. This happens when you press Control+C on the controlling terminal.
{
	(void)context;
	(void)info;
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signal_global(int signum) // Corrects the global variable mid Process.
{
	if (signum == SIGQUIT)
		g_global = SIGQUIT;
	if (signum == SIGINT)
		g_global = SIGINT;
}

void	make_sigaction(void) // This makes sigaction, catching signals and redirecting them to their handler functions, work in progress.
{
	struct sigaction	sa;

	sa.sa_sigaction = &handle_sigint;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&(sa.sa_mask));
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	handler_cd(t_mnshll *minsh) // This is about Control+D
{
	if (!(minsh->input))
		free_exit_procces(minsh, "exit\n");
}

void	check_global_end(void) // checks for any Signals after the process has finished.
{
	if (!g_global)
		return ;
	if (g_global == SIGQUIT)
		ft_putstr_fd("Quit\n", 2);
	if (g_global == SIGINT)
		printf("\n");
	g_global = 0;
}
