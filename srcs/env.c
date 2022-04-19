/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 16:04:19 by tpierre           #+#    #+#             */
/*   Updated: 2020/12/10 10:11:45 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_set_env(char **env)
{
	int i;

	if ((g_m.env = (char **)malloc(sizeof(char *) *
			(ft_tabsize(env) + 1))) == NULL)
		ft_error("Memory allocation failed");
	i = -1;
	while (env[++i])
	{
		if ((g_m.env[i] = ft_strdup(env[i])) == NULL)
			ft_error("Memory allocation failed");
	}
	g_m.env[i] = NULL;
	if ((g_m.env_export = (char **)malloc(sizeof(char *) *
			(ft_tabsize(env) + 1))) == NULL)
		ft_error("Memory allocation failed");
	i = -1;
	while (env[++i])
	{
		if ((g_m.env_export[i] = ft_strdup(env[i])) == NULL)
			ft_error("Memory allocation failed");
	}
	g_m.env_export[i] = NULL;
}

void	ft_print_env(void)
{
	int i;

	i = -1;
	while (g_m.env[++i])
	{
		ft_putstr_fd(g_m.env[i], 1);
		ft_putstr_fd("\n", 1);
	}
}

void	ft_print_export(void)
{
	int i;

	i = -1;
	while (g_m.env_export[++i])
	{
		ft_putstr_fd(g_m.env[i], 1);
		ft_putstr_fd("\n", 1);
	}
}
