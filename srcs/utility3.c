/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 18:42:36 by tpierre           #+#    #+#             */
/*   Updated: 2020/12/17 18:59:14 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_add_to_int_tab(char *str, int i, int count)
{
	g_m.global_split_types = (int *)ft_realloc(g_m.global_split_types,
			sizeof(int) * count, sizeof(int) * (count + 2));
	if (str[i] == '|')
		g_m.global_split_types[count] = 1;
	else if (str[i] == '<')
		g_m.global_split_types[count] = 2;
	else if (str[i] == '>' && str[i + 1] == '>')
		g_m.global_split_types[count] = 3;
	else if (str[i] == '>' && str[i + 1] != '>')
		g_m.global_split_types[count] = 4;
}

void	ft_handle_back_chevron(void)
{
	int		i;
	char	*tmp;

	i = -1;
	while (g_m.global_split_types[++i])
	{
		if (g_m.global_split_types[i] == 2)
		{
			tmp = ft_strdup(g_m.global_split[i + 1]);
			free(g_m.global_split[i + 1]);
			g_m.global_split[i + 1] = ft_strtrim(g_m.global_split[i], " ");
			g_m.global_split_types[i] = 1;
			free(g_m.global_split[i]);
			g_m.global_split[i] = ft_strjoin("cat ", tmp);
			free(tmp);
		}
		else
		{
			tmp = ft_strdup(g_m.global_split[i]);
			free(g_m.global_split[i]);
			g_m.global_split[i] = ft_strdup(tmp);
			free(tmp);
		}
	}
}

void	ft_create_global_split_execute(void)
{
	int	i;
	int	size;

	size = 0;
	i = -1;
	while (g_m.global_split_types[++i])
		size++;
	g_m.global_split_execute = (int *)ft_calloc(sizeof(int), size + 2);
	i = -1;
	while (g_m.global_split_types[++i])
	{
		if (i == 0)
			g_m.global_split_execute[i] = 2;
		if (g_m.global_split_types[i] == 1)
			g_m.global_split_execute[i + 1] = 2;
		else if (g_m.global_split_types[i] == 11)
		{
			g_m.global_split_types[i] = 1;
			g_m.global_split_execute[i] = 2;
			g_m.global_split_execute[i + 1] = 1;
		}
		else
			g_m.global_split_execute[i + 1] = 1;
	}
	g_m.global_split_execute[i + 1] = 0;
}

void	ft_handle_fucked_up_case(void)
{
	int	i;
	int	l;

	l = ft_find_last_file();
	i = -1;
	while (++i <= l)
	{
		if (ft_strlen(g_m.global_split[l]) == ft_strlen(g_m.global_split[i]) &&
				ft_strncmp(g_m.global_split[i], g_m.global_split[l],
				ft_strlen(g_m.global_split[l])) == 0)
		{
			if (g_m.global_split_types[i - 1] == 4)
			{
				g_m.global_split_types[i - 1] = 3;
				g_m.global_split_types[l - 1] = 4;
			}
		}
	}
}

int		ft_check_empty_arg(void)
{
	int i;

	i = -1;
	while (g_m.global_split[++i])
	{
		if (i > 0 && ft_strlen(g_m.global_split[i]) == 0)
		{
			if (g_m.global_split_types[i - 1] == 4
					|| g_m.global_split_types[i - 1] == 3)
				ft_print_error_unexpected_token('>');
			else if (g_m.global_split_types[i - 1] == 2)
				ft_print_error_unexpected_token('<');
			else if (g_m.global_split_types[i - 1] == 1)
				ft_print_error_unexpected_token('|');
			return (1);
		}
	}
	return (0);
}
