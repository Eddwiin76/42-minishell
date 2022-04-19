/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 16:35:19 by tpierre           #+#    #+#             */
/*   Updated: 2020/12/17 10:50:33 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_handle_exit_invalid_status(char **args)
{
	ft_putstr_fd("minishell: exit: ", 1);
	ft_putstr_fd(args[1], 1);
	ft_putstr_fd(" : numeric argument required\n", 1);
	g_status = 2;
	ft_tabdel((void **)args);
	ft_tabdel((void **)g_m.commands);
	ft_tabdel((void **)g_m.global_split);
	ft_exit();
}

void	ft_handle_exit_big_next(char **args)
{
	unsigned int	tmp;
	int				nb;

	if (ft_strcmp(args[1], "9223372036854775808") >= 0)
		ft_handle_exit_invalid_status(args);
	else
	{
		nb = ft_atoi(args[1]);
		tmp = 9223372036854775808U - nb;
		g_status = 256 - tmp;
	}
}

void	ft_handle_exit_big_status(char **args)
{
	char	**status;

	if (args[1][0] == '-' && ft_strlen(args[1]) > 19)
	{
		status = ft_split(args[1], '-');
		if (ft_strcmp(status[0], "9223372036854775808") > 0)
		{
			ft_tabdel((void **)status);
			ft_handle_exit_invalid_status(args);
		}
		ft_tabdel((void **)status);
	}
	else if (ft_strlen(args[1]) > 18)
		ft_handle_exit_big_next(args);
	else
		g_status = ft_atoi(args[1]);
	ft_tabdel((void **)args);
	ft_tabdel((void **)g_m.commands);
	ft_tabdel((void **)g_m.global_split);
	ft_exit();
}

void	ft_handle_exit_correct_status(char **args, size_t size)
{
	if (size > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 1);
		ft_tabdel((void **)args);
		return ;
	}
	else
		ft_handle_exit_big_status(args);
}

void	ft_handle_exit(char **cmd)
{
	size_t	size;

	size = ft_tabsize(cmd);
	if (size == 1)
	{
		ft_tabdel((void **)cmd);
		ft_tabdel((void **)g_m.commands);
		ft_tabdel((void **)g_m.global_split);
		ft_exit();
	}
	else
	{
		if (ft_isalldigit_sign(cmd[1]))
			ft_handle_exit_correct_status(cmd, size);
		else
			ft_handle_exit_invalid_status(cmd);
	}
}
