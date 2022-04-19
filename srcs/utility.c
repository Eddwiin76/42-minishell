/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 12:58:10 by mlaraki           #+#    #+#             */
/*   Updated: 2020/12/18 10:38:01 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_find_env(char *name)
{
	int		i;
	char	*key;
	char	*value;
	int		j;

	i = -1;
	while (g_m.env[++i])
	{
		j = ft_strchr_index(g_m.env[i], '=');
		key = ft_substr(g_m.env[i], 0, j);
		value = ft_substr(g_m.env[i], j + 1, ft_strlen(g_m.env[i]) - j - 1);
		if (ft_strcmp(key, name) == 0)
		{
			free(key);
			return (value);
		}
		free(key);
		free(value);
	}
	return (NULL);
}

int		ft_isalldigit_sign(char *str)
{
	int	i;

	i = -1;
	if ((str[0] == '-' || str[0] == '+'))
		i++;
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (0);
	return (1);
}

int		ft_strchr_index(const char *s, int c)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] == c)
			return (i);
	if (s[i] == c)
		return (i);
	return (-1);
}

void	ft_split_args(int i)
{
	g_m.args = ft_split(g_m.global_split[i], ' ');
	ft_decode_command(g_m.args);
	ft_remove_quotes(g_m.args);
}
