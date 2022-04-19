/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 13:01:59 by tpierre           #+#    #+#             */
/*   Updated: 2019/12/05 15:49:28 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		totalline(char const *s, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
			i++;
		count++;
	}
	return (count);
}

static int		word(char const *s, char c, int i)
{
	int size;

	size = 0;
	while (s[i] && s[i++] != c)
		size++;
	return (size);
}

static char		**del(char **tab, int j)
{
	while (j)
		free(tab[j--]);
	free(tab);
	return (NULL);
}

static char		**copy(char **tab, const char *s, char c)
{
	int i;
	int j;
	int n;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			n = 0;
			if (!(tab[j] = (char *)malloc(sizeof(char) * (word(s, c, i) + 1))))
				return (del(tab, j));
			while (s[i] && s[i] != c)
				tab[j][n++] = s[i++];
			tab[j++][n] = '\0';
		}
	}
	tab[j] = NULL;
	return (tab);
}

char			**ft_split(char const *s, char c)
{
	char	**tab;

	if (s == NULL ||
		!(tab = (char **)malloc(sizeof(char *) * (totalline(s, c) + 1))))
		return (NULL);
	return (copy(tab, s, c));
}
