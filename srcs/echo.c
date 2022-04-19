/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 15:40:38 by tpierre           #+#    #+#             */
/*   Updated: 2020/12/16 13:02:04 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_echo_n(char **input, int *i)
{
	int n;
	int j;

	n = 0;
	while (input[*i + 1] && (input[*i] &&
			(ft_strncmp(input[*i + 1], "-n", 2) == 0)))
	{
		j = 2;
		while (input[*i + 1][j] && input[*i + 1][j] == 'n')
			j++;
		if (input[*i + 1][j] == 0)
			n = 1;
		else
			return (n);
		(*i)++;
	}
	return (n);
}

void	ft_handle_echo(char **input)
{
	int i;
	int n;

	i = 0;
	n = ft_echo_n(input, &i);
	while (input[++i])
	{
		ft_putstr_fd(input[i], 1);
		if (input[i + 1])
			ft_putstr_fd(" ", 1);
	}
	if (n == 0)
		ft_putchar_fd('\n', 1);
	g_status = 0;
}
