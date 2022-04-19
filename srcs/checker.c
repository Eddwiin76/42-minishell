/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 13:03:36 by user42            #+#    #+#             */
/*   Updated: 2020/12/17 12:14:54 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_check_side_chars(char *tmp)
{
	size_t	i;
	char	**vars;

	vars = ft_split(">$ ;; || <> >< << >>> |; ( ) ", ' ');
	i = -1;
	while (vars[++i])
		if (ft_strnstr(tmp, vars[i], ft_strlen(tmp)) != NULL)
		{
			if (vars[i][0] == '>' && vars[i][1] == '$')
				ft_print_error_ambiguous_redirect();
			else
			{
				if (vars[i][0] == '|' && vars[i][1] == ';')
					ft_print_error_unexpected_token(vars[i][1]);
				else if (vars[i][0] == ';' && vars[i][1] == ';')
					ft_print_error_unexpected_token_x2(vars[i][0]);
				else
					ft_print_error_unexpected_token(vars[i][0]);
			}
			ft_tabdel((void **)vars);
			return (1);
		}
	ft_tabdel((void **)vars);
	return (0);
}

int		ft_check_unexpected_token(char *tmp)
{
	if (ft_strlen(tmp) == 0)
		return (0);
	if (tmp[0] == ';' || tmp[0] == '|' ||
		(tmp[0] == '<' && tmp[1] == '\0') || (tmp[0] == '>' && tmp[1] == '\0'))
	{
		ft_print_error_unexpected_token(tmp[0]);
		return (0);
	}
	if (ft_check_side_chars(tmp) == 1)
		return (0);
	return (1);
}

char	*ft_check_global_input_next(char *input, char *tmp)
{
	if (ft_check_unexpected_token(tmp) == 0)
	{
		free(input);
		free(tmp);
		return (NULL);
	}
	free(tmp);
	tmp = ft_strtrim(input, " ");
	free(input);
	return (tmp);
}

char	*ft_check_global_input(char *input)
{
	char	*tmp;
	char	*tmp2;
	char	**tab;
	int		i;

	tab = ft_split(input, ' ');
	if (tab[0] != NULL)
	{
		tmp = ft_strdup(tab[0]);
		i = 0;
		while (tab[++i])
		{
			tmp2 = ft_strjoin(tmp, tab[i]);
			free(tmp);
			tmp = ft_strdup(tmp2);
			free(tmp2);
		}
	}
	else
		tmp = ft_strdup("");
	ft_tabdel((void **)tab);
	return (ft_check_global_input_next(input, tmp));
}
