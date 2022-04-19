/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabmaxlen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 16:51:52 by tpierre           #+#    #+#             */
/*   Updated: 2020/07/12 17:12:16 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_tabmaxlen(char **tab)
{
	int		i;
	size_t	maxsize;

	i = -1;
	maxsize = 0;
	while (tab[++i])
		if (maxsize < ft_strlen(tab[i]))
			maxsize = ft_strlen(tab[i]);
	return (maxsize);
}
