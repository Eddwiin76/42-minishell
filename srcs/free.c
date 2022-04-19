/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 14:49:00 by tpierre           #+#    #+#             */
/*   Updated: 2020/12/18 10:48:11 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_free_for_ft_pipe(void)
{
	free(g_m.global_split_types);
	g_m.global_split_types = 0;
	free(g_m.global_split_execute);
	g_m.global_split_execute = 0;
	ft_tabdel((void **)g_m.global_split);
	return (0);
}

void	ft_free_for_ft_execve(int i, char **cmd, char *error, char **tab)
{
	g_status = 127;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd(": ", 2);
	if (i == 1)
		ft_putstr_fd("command not found", 2);
	if (i == 2)
		ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
	ft_tabdel((void **)g_m.commands);
	ft_tabdel((void **)g_m.global_split);
	ft_tabdel((void **)cmd);
	ft_tabdel((void **)tab);
	ft_exit();
}

void	ft_free_for_ft_handle_fork(void)
{
	ft_tabdel((void **)g_m.commands);
	ft_tabdel((void **)g_m.args);
	ft_tabdel((void **)g_m.global_split);
	ft_exit();
}
