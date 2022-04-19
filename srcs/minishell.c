/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 10:12:51 by tpierre           #+#    #+#             */
/*   Updated: 2020/12/18 09:59:02 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../includes/minishell.h"

void	ft_read_command(void)
{
	int		i;
	char	b[1];

	i = get_next_line(1, &g_m.global_input);
	if (!i && !ft_strlen(g_m.global_input))
	{
		free(g_m.global_input);
		ft_tabdel((void **)g_m.env);
		ft_tabdel((void **)g_m.env_export);
		free(g_m.global_split_types);
		g_m.global_split_types = NULL;
		free(g_m.global_split_execute);
		g_m.global_split_execute = NULL;
		free(g_str);
		exit(g_status);
	}
	while (!i)
		i = read(1, b, 1);
}

void	ft_init_struct(void)
{
	g_m.global_input = NULL;
	g_m.env = NULL;
	g_m.env_export = NULL;
	g_m.commands = NULL;
	g_m.args = NULL;
	g_m.global_split = NULL;
	g_m.global_split_types = 0;
	g_m.global_split_execute = 0;
	g_m.has_error = 0;
}

int		main(int poop, char **poops, char **env)
{
	(void)poop;
	(void)poops;
	ft_init_struct();
	ft_set_env(env);
	while (42)
	{
		g_pid = 0;
		ft_prompt();
		ft_handle_signal();
		ft_read_command();
		ft_parse();
	}
	return (0);
}
