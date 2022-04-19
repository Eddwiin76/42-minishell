/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 16:27:04 by user42            #+#    #+#             */
/*   Updated: 2020/12/17 12:25:28 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exit(void)
{
	ft_tabdel((void **)g_m.env);
	ft_tabdel((void **)g_m.env_export);
	free(g_m.global_split_types);
	g_m.global_split_types = NULL;
	free(g_m.global_split_execute);
	g_m.global_split_execute = NULL;
	free(g_str);
	exit(g_status);
}

void	ft_error(char *error_message)
{
	ft_putstr_fd(error_message, 1);
	ft_exit();
}
