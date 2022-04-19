/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 18:03:40 by tpierre           #+#    #+#             */
/*   Updated: 2020/11/12 16:26:30 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../includes/minishell.h"

void	ft_prompt(void)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, 0);
	ft_putstr_fd("\x1b[36m", 1);
	ft_putstr_fd(pwd, 1);
	ft_putstr_fd(" ➡ \x1b[0m", 1);
	free(pwd);
}
