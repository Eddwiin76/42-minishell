/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaraki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 17:07:32 by mlaraki           #+#    #+#             */
/*   Updated: 2020/01/13 12:47:29 by mlaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_getlength(int nb)
{
	int length;

	length = 0;
	if (nb < 0)
		nb = nb * -1;
	while (nb > 0)
	{
		nb = nb / 10;
		length++;
	}
	return (length);
}

char	*ft_itoa(int n)
{
	int		size;
	int		negative;
	char	*result;

	size = ft_getlength(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	else if (n == 0)
		return (ft_strdup("0"));
	negative = n < 0 ? 1 : 0;
	size = n < 0 ? size + 1 : size;
	n = n < 0 ? -n : n;
	if (!(result = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	if (negative)
		result[0] = '-';
	result[size] = '\0';
	while (size - negative > 0)
	{
		result[size - 1] = n % 10 + '0';
		n = n / 10;
		size--;
	}
	return (result);
}
