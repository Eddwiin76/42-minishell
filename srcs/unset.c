/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 13:16:30 by tpierre           #+#    #+#             */
/*   Updated: 2020/12/17 19:11:45 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_handle_unset_next(char **input, int j)
{
	int		i;
	int		found;

	i = -1;
	found = 0;
	while (g_m.env_export[++i])
		if (ft_get_var_name_in_unset(input[j], g_m.env_export[i]) == 0)
			found = 1;
	if (found == 1)
		ft_unset_export_next(input, j);
}

void	ft_handle_unset(char **input)
{
	int		i;
	int		j;
	int		found;

	j = 0;
	while (input[++j] != NULL)
	{
		if (ft_check_variable_unset(input[j]) == -1)
		{
			g_status = 1;
			continue ;
		}
		i = -1;
		found = 0;
		while (g_m.env[++i])
			if (ft_get_var_name_in_unset(input[j], g_m.env[i]) == 0)
				found = 1;
		if (found == 1)
			ft_unset_next(input, j);
		ft_handle_unset_next(input, j);
		g_status = 0;
	}
	if (j == 1)
		g_status = 0;
}
