/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 13:50:20 by tpierre           #+#    #+#             */
/*   Updated: 2020/12/18 10:38:01 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_has_builtin(char **cmd)
{
	if (ft_strcmp(cmd[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd[0], "export") == 0)
		return (cmd[1] ? 1 : 0);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		return (1);
	return (0);
}

int		ft_directory_index(void)
{
	int		i;
	char	**tab;

	i = -1;
	while (g_m.global_split_execute[++i])
	{
		tab = ft_split(g_m.global_split[i], ' ');
		ft_decode_command(tab);
		ft_remove_quotes(tab);
		if (g_m.global_split_execute[i] == 1)
		{
			if (open(tab[0], O_DIRECTORY, 0666) >= 0)
				return (ft_print_error_directory(tab));
			else if (open(tab[0], ft_compute_flag(i), 0666) < 0)
			{
				ft_tabdel((void **)tab);
				ft_handle_file_error();
			}
		}
		ft_tabdel((void **)tab);
	}
	return (0);
}

int		ft_pipe(char *command)
{
	int		i;
	char	*has_pipe;

	has_pipe = ft_strchr(command, '|');
	if (ft_multiple_split_part_1(command) == 1)
		return (1);
	if (ft_directory_index() == 1)
		return (ft_free_for_ft_pipe());
	i = (ft_strlen(g_m.global_split[0]) == 0 ? 0 : -1);
	while (g_m.global_split[++i])
	{
		ft_split_args(i);
		if (has_pipe == NULL && ft_has_builtin(g_m.args))
			ft_parse_command(g_m.args, g_m.global_split[i]);
		else if (g_m.has_error == 0 && ((i == 0) || (g_status == 0 && i > 0)))
			ft_handle_fork(i, g_m.global_split[i]);
		if (g_status != 0 && i == 0)
		{
			ft_tabdel((void **)g_m.args);
			break ;
		}
		g_m.has_error = 0;
		ft_tabdel((void **)g_m.args);
	}
	return (ft_free_for_ft_pipe());
}
