/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 14:41:08 by tpierre           #+#    #+#             */
/*   Updated: 2020/12/17 10:46:25 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_handle_case_variable(char *input, int *i, char **final, int *j)
{
	char	tmp[4096];
	char	*env_value;
	int		k;

	k = 0;
	while (++(*i) < (int)ft_strlen(input) && ft_isalnum(input[*i]))
	{
		tmp[k] = input[*i];
		k++;
	}
	tmp[k] = '\0';
	env_value = ft_find_env(tmp);
	k = -1;
	if (env_value != NULL)
		while (env_value[++k])
		{
			if (!(final[0] = (char *)ft_realloc((void *)final[0],
					sizeof(char) * (*j + 1), sizeof(char) * (*j + 2))))
				ft_error("Memory Allocation Failed");
			final[0][*j] = env_value[k];
			(*j)++;
		}
	free(env_value);
	(*i)--;
}

void	ft_add_char(char **final, char c, int *j)
{
	if (!(final[0] = (char *)ft_realloc((void *)final[0],
			sizeof(char) * (*j + 1), sizeof(char) * (*j + 2))))
		ft_error("Memory Allocation Failed");
	final[0][*j] = c;
	(*j)++;
}

void	ft_handle_case_exit_status(int *i, char **final, int *j)
{
	char	*tmp;
	int		k;

	(*i)++;
	tmp = ft_itoa(g_status);
	k = -1;
	while (tmp[++k])
		ft_add_char(final, tmp[k], j);
	free(tmp);
}

void	ft_parse_variable_next(int *i, char **final, int *j, char *input)
{
	if (input[*i + 1] == '?')
		ft_handle_case_exit_status(i, final, j);
	else if (ft_isdigit(input[*i + 1]))
		(*i)++;
	else
		ft_handle_case_variable(input, i, final, j);
}

char	*ft_parse_variable(char *input)
{
	int		i;
	int		j;
	char	*final;
	char	*tmp;
	int		is_command;

	i = -1;
	j = 0;
	tmp = ft_strtrim(input, " ");
	is_command = ft_strcmp(tmp, "$?");
	free(tmp);
	if (!(final = malloc(sizeof(char) + 1)))
		ft_error("Memory Allocation Failed");
	while (++i < (int)ft_strlen(input))
	{
		if (input[i] == '$'
				&& (ft_isalnum(input[i + 1]) || input[i + 1] == '?')
				&& is_command != 0)
			ft_parse_variable_next(&i, &final, &j, input);
		else
			ft_add_char(&final, input[i], &j);
	}
	final[j] = '\0';
	return (final);
}
