/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 18:59:45 by tpierre           #+#    #+#             */
/*   Updated: 2020/12/17 19:00:44 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_check_variable_unset(char *input)
{
	int		i;
	int		error;

	error = 0;
	i = -1;
	if (ft_strlen(input) == 0)
		error = 1;
	else
		while (input[++i])
			if (!ft_isalnum(input[i]) || (ft_isdigit(input[i]) && i == 0))
				error = 1;
	if (error == 1)
	{
		ft_putstr_fd("minishell: unset: « ", 1);
		ft_putstr_fd(input, 1);
		ft_putstr_fd(" » not a valid identifier\n", 1);
		g_status = 1;
		return (-1);
	}
	return (0);
}

int		ft_get_var_name_in_unset(char *name, char *env)
{
	char	**tab;

	tab = ft_split(env, '=');
	if (ft_strlen(name) == ft_strlen(tab[0])
			&& (ft_strncmp(tab[0], name, ft_strlen(name)) == 0))
	{
		ft_tabdel((void **)tab);
		return (0);
	}
	ft_tabdel((void **)tab);
	return (1);
}

void	ft_unset_next(char **input, int k)
{
	int		i;
	int		j;
	char	**new_env;

	i = -1;
	j = -1;
	if ((new_env = (char **)malloc(sizeof(char *) *
			ft_tabsize(g_m.env))) == NULL)
		ft_error("Memory allocation failed");
	while (g_m.env[++i])
	{
		if (ft_get_var_name_in_unset(input[k], g_m.env[i]) != 0)
			if ((new_env[++j] = ft_strdup(g_m.env[i])) == NULL)
			{
				ft_tabdel((void **)new_env);
				ft_error("Memory allocation failed");
			}
	}
	new_env[j + 1] = NULL;
	ft_tabdel((void **)g_m.env);
	g_m.env = new_env;
}

void	ft_unset_export_next(char **input, int k)
{
	int		i;
	int		j;
	char	**new_env;

	i = -1;
	j = -1;
	if ((new_env = (char **)malloc(sizeof(char *) *
			ft_tabsize(g_m.env_export))) == NULL)
		ft_error("Memory allocation failed");
	while (g_m.env_export[++i])
	{
		if (ft_get_var_name_in_unset(input[k], g_m.env_export[i]) != 0)
			if ((new_env[++j] = ft_strdup(g_m.env_export[i])) == NULL)
			{
				ft_tabdel((void **)new_env);
				ft_error("Memory allocation failed");
			}
	}
	new_env[j + 1] = NULL;
	ft_tabdel((void **)g_m.env_export);
	g_m.env_export = new_env;
}
