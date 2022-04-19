/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 15:09:37 by tpierre           #+#    #+#             */
/*   Updated: 2019/11/22 15:58:37 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lnew;
	t_list	*ltmp;

	if (!lst || !f || !del)
		return (NULL);
	lnew = NULL;
	while (lst)
	{
		if (!(ltmp = ft_lstnew((*f)(lst->content))))
		{
			ft_lstclear(&lnew, del);
			return (NULL);
		}
		ft_lstadd_back(&lnew, ltmp);
		lst = lst->next;
	}
	return (lnew);
}
