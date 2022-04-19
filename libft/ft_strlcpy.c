/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 15:22:49 by tpierre           #+#    #+#             */
/*   Updated: 2019/11/18 18:37:03 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t i;

	if (!dst || !src)
		return (0);
	if (dstsize > 0)
	{
		i = 0;
		while (((char *)src)[i] && i < (dstsize - 1))
		{
			((char *)dst)[i] = ((char *)src)[i];
			i++;
		}
		((char *)dst)[i] = '\0';
	}
	return (ft_strlen(src));
}
