/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 18:20:18 by tpierre           #+#    #+#             */
/*   Updated: 2020/12/18 10:38:01 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../includes/minishell.h"

void	handle_sigint(int signal)
{
	ft_putstr_fd("\n", 1);
	if (g_pid)
		kill(g_pid, signal);
	else
	{
		g_status = 130;
		ft_prompt();
	}
}

void	handle_sigquit(int signal)
{
	if (g_pid)
	{
		kill(g_pid, signal);
		g_status = 131;
		ft_putstr_fd("\nQuit: ", 1);
		ft_putnbr_fd(signal, 1);
		ft_putstr_fd("\n", 1);
	}
}

void	ft_handle_signal(void)
{
	if (signal(SIGINT, &handle_sigint) == SIG_ERR)
		ft_putstr_fd("Could not set SIGINT handler\n", 1);
	if (signal(SIGQUIT, &handle_sigquit) == SIG_ERR)
		ft_putstr_fd("Could not set SIGQUIT handler\n", 1);
}
