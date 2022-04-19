/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_encoder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 17:33:23 by tpierre           #+#    #+#             */
/*   Updated: 2020/12/18 10:38:01 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../includes/minishell.h"

int		ft_set_escape(char *input, int i, char c)
{
	if (input[i] == '\\' && input[i - 1] == '\\')
		input[i] = 3;
	else
	{
		input[i - 1] = 3;
		input[i] = c;
	}
	return (1);
}

int		ft_escape_backslashes(int i, char *input, int quote, int double_quote)
{
	if (i > 0 && input[i - 1] == '\\')
	{
		if (input[i] == '\\' && !quote)
			return (ft_set_escape(input, i, 3));
		else if (input[i] == '$' && !quote)
			return (ft_set_escape(input, i, 4));
		else if (input[i] == ';' && !quote && !double_quote)
			return (ft_set_escape(input, i, 2));
		else if (input[i] == '|' && !quote && !double_quote)
			return (ft_set_escape(input, i, 5));
		else if (input[i] == ' ' && !quote && !double_quote)
			return (ft_set_escape(input, i, 1));
		else if (input[i] == '>' && !quote && !double_quote)
			return (ft_set_escape(input, i, 7));
		else if (input[i] == '<' && !quote && !double_quote)
			return (ft_set_escape(input, i, 8));
		else if (!quote && !double_quote)
			return (ft_set_escape(input, i, input[i]));
	}
	return (0);
}

void	ft_handle_char_in_quotes(int quote, int dquote, char *c)
{
	if ((quote || dquote) && *c == ' ')
		*c = 1;
	if ((quote || dquote) && *c == ';')
		*c = 2;
	if (quote && *c == '$')
		*c = 4;
	if ((quote || dquote) && *c == '|')
		*c = 5;
	if ((quote || dquote) && *c == '>')
		*c = 7;
	if ((quote || dquote) && *c == '<')
		*c = 8;
}

void	ft_handle_quote(int *quote, int *double_quote, char *c)
{
	if (!*quote && !*double_quote)
	{
		*quote = 1;
		*c = 3;
	}
	else if (*quote && !*double_quote)
	{
		*quote = 0;
		*c = 3;
	}
}

void	ft_handle_double_quote(int *quote, int *double_quote, char *c)
{
	if (!*quote && !*double_quote)
	{
		*c = 3;
		*double_quote = 1;
	}
	else if (!*quote && *double_quote)
	{
		*c = 3;
		*double_quote = 0;
	}
}
