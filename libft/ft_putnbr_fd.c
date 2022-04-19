/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 14:21:42 by tpierre           #+#    #+#             */
/*   Updated: 2020/10/09 01:45:20 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int nbr;

	nbr = n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		nbr = -n;
	}
	if (nbr > 9)
		ft_putnbr_fd((nbr / 10), fd);
	ft_putchar_fd(((nbr % 10) + 48), fd);
}

void	ft_putunbr_fd(unsigned int nbr, int fd)
{
	if (nbr > 9)
	{
		ft_putunbr_fd((nbr / 10), fd);
		ft_putchar_fd(((nbr % 10) + 48), fd);
	}
	else
		ft_putchar_fd((nbr + 48), fd);
}

void	ft_puthexa_fd(unsigned int nbr, int fd)
{
	if (nbr > 15)
	{
		ft_puthexa_fd((nbr / 16), fd);
		ft_puthexa_fd((nbr % 16), fd);
	}
	else if (nbr < 10)
		ft_putchar_fd((nbr + 48), fd);
	else
		ft_putchar_fd((nbr + 87), fd);
}

void	ft_putuhexa_fd(unsigned int nbr, int fd)
{
	if (nbr > 15)
	{
		ft_putuhexa_fd((nbr / 16), fd);
		ft_putuhexa_fd((nbr % 16), fd);
	}
	else if (nbr < 10)
		ft_putchar_fd((nbr + 48), fd);
	else
		ft_putchar_fd((nbr + 55), fd);
}

void	ft_putadr_fd(unsigned long nbr, int fd)
{
	if (nbr > 15)
	{
		ft_putadr_fd((nbr / 16), fd);
		ft_putadr_fd((nbr % 16), fd);
	}
	else if (nbr < 10)
		ft_putchar_fd((nbr + 48), fd);
	else
		ft_putchar_fd((nbr + 87), fd);
}
