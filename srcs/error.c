/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 16:01:18 by tpierre           #+#    #+#             */
/*   Updated: 2020/12/17 15:06:54 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_print_error_unexpected_token(char token)
{
	ft_putstr_fd("minishell : syntax error ", 1);
	ft_putstr_fd("near unexpected token « ", 1);
	ft_putchar_fd(token, 1);
	ft_putstr_fd(" »\n", 1);
	g_status = 2;
}

void	ft_print_error_ambiguous_redirect(void)
{
	ft_putstr_fd("minishell : ambiguous redirect", 1);
	ft_putstr_fd("\n", 1);
	g_status = 1;
}

void	ft_print_error_unexpected_token_x2(char token)
{
	ft_putstr_fd("minishell : syntax error ", 1);
	ft_putstr_fd("near unexpected token « ", 1);
	ft_putchar_fd(token, 1);
	ft_putchar_fd(token, 1);
	ft_putstr_fd(" »\n", 1);
	g_status = 2;
}

void	ft_handle_file_error(void)
{
	ft_putstr_fd("minishell : open failed\n", 1);
	g_status = 1;
	ft_exit();
}

int		ft_print_error_directory(char **tab)
{
	ft_putstr_fd("minishell: ", 1);
	ft_putstr_fd(tab[0], 1);
	ft_putstr_fd(": ", 1);
	ft_putstr_fd("is a directory", 1);
	ft_putstr_fd("\n", 1);
	g_status = 1;
	ft_tabdel((void **)tab);
	return (1);
}
