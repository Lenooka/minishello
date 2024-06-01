/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:41:46 by jhuber            #+#    #+#             */
/*   Updated: 2024/06/01 19:41:56 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int signum, siginfo_t *info, void *context)
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

void	signal_global(int signum)
{
	if (signum == SIGQUIT)
		g_global = SIGQUIT;
	if (signum == SIGINT)
		g_global = SIGINT;
}

void	make_sigaction(void)
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
		free_exit_procces(minsh, NULL);
}

void	check_global_end(void)
{
	if (!g_global)
		return ;
	if (g_global == SIGQUIT)
		ft_putstr_fd("Quit\n", 2);
	if (g_global == SIGINT)
		printf("\n");
	g_global = 0;
}
