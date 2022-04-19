/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 14:28:44 by tpierre           #+#    #+#             */
/*   Updated: 2020/12/18 11:10:03 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_handle_fork_5(int *fd, int *fdd)
{
	int		status;

	waitpid(g_pid, &status, 0);
	if (WIFEXITED(status))
		g_status = WEXITSTATUS(status);
	*fdd = fd[0];
	close(fd[1]);
}

void	ft_handle_fork_3(int last_file_index, int *fd)
{
	char	**tab;

	tab = ft_split(g_m.global_split[last_file_index], ' ');
	ft_decode_command(tab);
	ft_remove_quotes(tab);
	if ((fd[1] = open(tab[0], ft_compute_flag(last_file_index), 0666)) < 0)
	{
		ft_tabdel((void **)tab);
		ft_handle_file_error();
	}
	ft_tabdel((void **)tab);
}

void	ft_handle_fork_4(int last_file_index, int *fd,
			int last_command_index, int i)
{
	if (g_m.global_split[i + 1] != NULL)
	{
		if (last_file_index > -1 && i == last_command_index)
			ft_handle_fork_3(last_file_index, fd);
		else if (last_file_index > -1 && i != last_file_index
				&& g_m.global_split_execute[i] == 1)
			if (open(g_m.args[0], ft_compute_flag(i), 0666) < 0)
				ft_handle_file_error();
		dup2(fd[1], 1);
		close(fd[0]);
	}
}

void	ft_handle_fork_2(int *last_file_index, int *last_command_index)
{
	*last_file_index = -1;
	*last_command_index = -1;
	if (g_m.global_split_types != NULL)
		*last_file_index = ft_find_last_file();
	if (g_m.global_split_types != NULL)
		*last_command_index = ft_find_last_command();
}

void	ft_handle_fork(int i, char *input)
{
	int			fd[2];
	static int	fdd;
	int			last_file_index;
	int			last_command_index;

	pipe(fd);
	ft_handle_fork_2(&last_file_index, &last_command_index);
	if ((g_pid = fork()) == -1)
	{
		g_status = 1;
		ft_error("fork");
	}
	else if (g_pid > 0)
		ft_handle_fork_5(fd, &fdd);
	else if (g_pid == 0)
	{
		dup2(fdd, 0);
		ft_handle_fork_4(last_file_index, fd, last_command_index, i);
		if (g_m.global_split_execute[i] == 2)
			ft_parse_command(g_m.args, input);
		ft_free_for_ft_handle_fork();
	}
}
