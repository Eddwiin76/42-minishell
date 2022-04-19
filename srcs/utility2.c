/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 17:33:23 by tpierre           #+#    #+#             */
/*   Updated: 2020/12/18 10:38:01 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../includes/minishell.h"

char	*ft_replace_multiple_spaces(char *input)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = -1;
	tmp = NULL;
	while (input[i])
	{
		tmp = (char *)ft_realloc(tmp, sizeof(char) * j + 1,
				sizeof(char) * j + 2);
		if (input[i] != ' ')
			tmp[++j] = input[i++];
		else if (input[i] == ' ')
		{
			tmp[++j] = input[i];
			while (input[i] == ' ')
				i++;
		}
	}
	tmp[++j] = '\0';
	free(input);
	input = ft_strdup(tmp);
	free(tmp);
	return (input);
}

int		ft_find_last_file(void)
{
	int		i;
	int		last_index;

	i = -1;
	last_index = -1;
	while (g_m.global_split_execute[++i])
	{
		if (g_m.global_split_execute[i] == 1)
			last_index = i;
	}
	return (last_index);
}

int		ft_find_last_command(void)
{
	int		i;
	int		last_index;

	i = -1;
	last_index = -1;
	while (g_m.global_split_execute[++i])
	{
		if (g_m.global_split_execute[i] == 2)
			last_index = i;
		if (g_m.global_split_execute[i] == 1)
			break ;
	}
	return (last_index);
}

int		ft_compute_flag(int i)
{
	if (i > 0)
	{
		if (g_m.global_split_types[i - 1] == 4)
			return (O_WRONLY | O_CREAT | O_TRUNC);
		else if (g_m.global_split_types[i - 1] == 3)
			return (O_WRONLY | O_CREAT | O_APPEND);
	}
	return (-1);
}
