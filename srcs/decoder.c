/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decoder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 15:09:54 by tpierre           #+#    #+#             */
/*   Updated: 2020/12/18 10:38:01 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_decode_command(char **str)
{
	int		i;
	int		j;
	char	c;

	i = -1;
	while (str[++i])
	{
		j = -1;
		while (str[i][++j])
		{
			c = str[i][j];
			if (c == 1)
				str[i][j] = ' ';
			if (c == 2)
				str[i][j] = ';';
			if (c == 4)
				str[i][j] = '$';
			if (c == 5)
				str[i][j] = '|';
			if (c == 7)
				str[i][j] = '>';
			if (c == 8)
				str[i][j] = '<';
		}
	}
}

char	*ft_join_splits(char **strs)
{
	char	*result;
	int		i;
	int		j;
	int		k;

	i = -1;
	j = 0;
	while (strs[++i])
	{
		k = -1;
		while (strs[i][++k])
			j++;
	}
	if (!(result = (char *)ft_calloc(sizeof(char), j + 1)))
		return (NULL);
	i = -1;
	j = 0;
	while (strs[++i])
	{
		k = -1;
		while (strs[i][++k])
			result[j++] = strs[i][k];
	}
	return (result);
}

char	*ft_remove_quotes(char **str)
{
	char	**splits;
	int		i;

	i = -1;
	while (str[++i])
	{
		if (ft_strchr(str[i], 3))
		{
			splits = ft_split(str[i], 3);
			free(str[i]);
			str[i] = ft_join_splits(splits);
			ft_tabdel((void **)splits);
		}
	}
	return (NULL);
}
