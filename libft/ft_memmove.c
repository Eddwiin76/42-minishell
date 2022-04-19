/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 15:18:21 by tpierre           #+#    #+#             */
/*   Updated: 2019/12/06 10:40:56 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char *d;
	char *s;
	char tmp;

	d = (char *)dst;
	s = (char *)src;
	if (dst == NULL && src == NULL)
		return (NULL);
	if (d > s)
		while (len--)
		{
			tmp = *(s + len);
			*(d + len) = tmp;
		}
	else
		while (len--)
		{
			tmp = *s++;
			*d++ = tmp;
		}
	return (dst);
}
