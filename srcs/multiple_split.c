/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 16:35:19 by tpierre           #+#    #+#             */
/*   Updated: 2020/12/17 18:59:09 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_multiple_split_part_3(void)
{
	if (g_m.global_split_types != 0)
	{
		if (ft_check_empty_arg() == 1)
		{
			ft_tabdel((void **)g_m.global_split);
			free(g_m.global_split_types);
			g_m.global_split_types = 0;
			return (1);
		}
		ft_handle_back_chevron();
		ft_create_global_split_execute();
		ft_handle_fucked_up_case();
	}
	else
	{
		g_m.global_split_execute = ft_calloc(sizeof(int), 2);
		g_m.global_split_execute[0] = 2;
	}
	return (0);
}

int		ft_multiple_split_part_2(char *str, int *count, int *pivot)
{
	char	*tmp;
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '|' || str[i] == '>' || str[i] == '<')
		{
			g_m.global_split = (char **)ft_realloc(g_m.global_split,
					sizeof(char *) * *count, sizeof(char *) * (*count + 2));
			tmp = ft_substr(str, *pivot, i - *pivot);
			g_m.global_split[*count] = ft_strtrim(tmp, " ");
			free(tmp);
			ft_add_to_int_tab(str, i, *count);
			if (str[i] == '>' && str[i + 1] == '>')
				*pivot = i + 2;
			else
				*pivot = i + 1;
			i++;
			g_m.global_split[*count + 1] = NULL;
			(*count)++;
		}
	}
	return (i);
}

int		ft_multiple_split_part_1(char *str)
{
	int		i;
	int		count;
	int		pivot;
	char	*tmp;

	count = 0;
	pivot = 0;
	i = ft_multiple_split_part_2(str, &count, &pivot);
	g_m.global_split = (char **)ft_realloc(g_m.global_split, sizeof(char *)
			* count, sizeof(char *) * (count + 2));
	tmp = ft_substr(str, pivot, i - pivot);
	g_m.global_split[count] = ft_strtrim(tmp, " ");
	free(tmp);
	g_m.global_split[count + 1] = NULL;
	return (ft_multiple_split_part_3());
}
