/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 15:21:07 by tpierre           #+#    #+#             */
/*   Updated: 2019/12/05 14:18:41 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t lendst;
	size_t lensrc;

	lendst = 0;
	while (dst[lendst] && lendst < dstsize)
		lendst++;
	lensrc = ft_strlen(src);
	if (dstsize == 0)
		return (lensrc);
	else if ((dstsize - 1) < lendst)
		lensrc += dstsize;
	else
		lensrc += lendst;
	if (lendst < dstsize)
	{
		while (lendst < dstsize - 1 && *src)
			dst[lendst++] = *src++;
		dst[lendst] = '\0';
	}
	return (lensrc);
}
