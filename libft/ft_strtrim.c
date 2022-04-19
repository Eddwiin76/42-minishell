/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 12:46:44 by tpierre           #+#    #+#             */
/*   Updated: 2019/12/06 13:05:54 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	lastoccurrence(char const *s1, char const *set, int i)
{
	int j;

	j = 0;
	while (set[j])
	{
		if (set[j] == s1[i])
			return (lastoccurrence(s1, set, i - 1));
		j++;
	}
	return (i);
}

static int	firstoccurrence(char const *s1, char const *set, int i)
{
	int j;

	j = 0;
	while (set[j])
	{
		if (set[j] == s1[i])
			return (firstoccurrence(s1, set, i + 1));
		j++;
	}
	return (i);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		f1;
	int		f2;
	char	*result;

	if (s1 == NULL || set == NULL)
		return (NULL);
	i = 0;
	f1 = firstoccurrence(s1, set, i);
	if (ft_strlen(s1) == 0 || (f1 == (int)ft_strlen(s1) && f1 != 0))
		f2 = f1 - 1;
	else
		f2 = lastoccurrence(s1, set, ft_strlen(s1) - 1);
	if (!(result = (char *)malloc(sizeof(char) * ((f2 - f1) + 2))))
		return (NULL);
	while (f1 <= f2)
		result[i++] = s1[f1++];
	result[i] = '\0';
	return (result);
}
