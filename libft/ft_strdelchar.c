/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdelchar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 17:35:28 by tpierre           #+#    #+#             */
/*   Updated: 2020/10/09 01:46:43 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdelchar(char *src, char c)
{
	int		i;
	int		j;
	char	*dst;

	dst = (char *)malloc(sizeof(char) *
				(ft_strlen(src) - ft_strcountchar(src, c) + 1));
	i = 0;
	j = 0;
	while (src[i])
	{
		if (src[i] != c)
		{
			dst[j] = src[i];
			j++;
		}
		i++;
	}
	dst[j] = '\0';
	return (dst);
}
