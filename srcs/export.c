/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 15:14:03 by tpierre           #+#    #+#             */
/*   Updated: 2020/12/18 10:18:31 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../includes/minishell.h"

int		ft_check_variable(char *input)
{
	int		i;
	int		error;
	char	**tab;

	error = 0;
	if (ft_strlen(input) == 0 || input[0] == '=')
		error = 1;
	else
	{
		tab = ft_split(input, '=');
		i = -1;
		while (tab[0][++i])
			if (!ft_isalnum(tab[0][i]) || (ft_isdigit(tab[0][i]) && i == 0))
				error = 1;
		ft_tabdel((void **)tab);
	}
	if (error == 1)
	{
		ft_putstr_fd("minishell: export: « ", 1);
		ft_putstr_fd(input, 1);
		ft_putstr_fd(" » not a valid identifier\n", 1);
		g_status = 1;
		return (-1);
	}
	return (0);
}

int		ft_export_next(char *name, char *new_value)
{
	char	*tmp;
	size_t	size;

	size = ft_tabsize(g_m.env);
	g_m.env = (char **)ft_realloc((void **)g_m.env, sizeof(char *) * size,
			sizeof(char *) * (size + 2));
	if ((tmp = ft_strjoin(name, "=")) == NULL)
		return (1);
	if ((g_m.env[size] = ft_strjoin(tmp, new_value)) == NULL)
	{
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}

int		ft_export(char *name, char *new_value)
{
	int		i;
	int		found;
	char	*tmp;

	i = -1;
	found = 0;
	while (g_m.env[++i])
	{
		if ((tmp = ft_strjoin(name, "=")) == NULL)
			return (1);
		if (ft_strncmp(g_m.env[i], tmp, ft_strlen(tmp)) == 0)
		{
			free(g_m.env[i]);
			if ((g_m.env[i] = ft_strjoin(tmp, new_value)) == NULL)
			{
				free(tmp);
				return (1);
			}
			found = 1;
		}
		free(tmp);
	}
	if (found == 0 && (ft_export_next(name, new_value)) == 1)
		return (1);
	return (0);
}

void	ft_handle_export_next(char **input, int j)
{
	char	*tmp1;
	char	*tmp2;
	int		i;

	i = ft_strchr_index(input[j], '=');
	tmp1 = ft_substr(input[j], 0, i);
	tmp2 = ft_substr(input[j], i + 1, ft_strlen(input[j]) - i - 1);
	if (tmp1 == NULL || tmp2 == NULL || ft_export(tmp1, tmp2) == 1)
	{
		free(tmp1);
		free(tmp2);
		ft_error("Memory allocation failed");
	}
	ft_export_bis(tmp1, tmp2);
	free(tmp1);
	free(tmp2);
}

void	ft_handle_export(char **input)
{
	int		j;

	j = 0;
	if (!input[1])
		ft_sort_env();
	else
	{
		while (input[++j])
			if (ft_check_variable(input[j]) != -1)
			{
				if (ft_strchr(input[j], '=') != NULL && input[j][0] != '=')
				{
					ft_handle_export_next(input, j);
				}
				else if (ft_strchr(input[j], '=') == NULL)
					ft_export_export(input[j]);
				g_status = 0;
			}
	}
}

/*
**export ZZZZ=ezfe ZZ ZZZ= ZZZZZZZZZ!=efz
*/
