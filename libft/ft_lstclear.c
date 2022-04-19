/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 14:40:30 by tpierre           #+#    #+#             */
/*   Updated: 2019/12/05 16:56:44 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *lbis;
	t_list *ltmp;

	if (!lst || !del)
		return ;
	lbis = *lst;
	while (lbis)
	{
		ltmp = lbis->next;
		ft_lstdelone(lbis, del);
		lbis = ltmp;
	}
	*lst = NULL;
}
