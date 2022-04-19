/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 15:14:03 by tpierre           #+#    #+#             */
/*   Updated: 2020/12/17 12:18:56 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../includes/minishell.h"

int		ft_export_bis_next(char *name, char *new_value)
{
	char	*tmp;
	size_t	size;

	size = ft_tabsize(g_m.env_export);
	g_m.env_export = (char **)ft_realloc((void **)g_m.env_export, sizeof(char *)
			* size, sizeof(char *) * (size + 2));
	if ((tmp = ft_strjoin(name, "=")) == NULL)
		return (1);
	if ((g_m.env_export[size] = ft_strjoin(tmp, new_value)) == NULL)
	{
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}

int		ft_get_var_name_in_export(char *name, int i)
{
	char	**tab;

	tab = ft_split(g_m.env_export[i], '=');
	if (ft_strlen(name) == ft_strlen(tab[0])
			&& (ft_strncmp(tab[0], name, ft_strlen(name)) == 0))
	{
		ft_tabdel((void **)tab);
		return (0);
	}
	ft_tabdel((void **)tab);
	return (1);
}

int		ft_export_bis(char *name, char *new_value)
{
	int		i;
	int		found;
	char	*tmp;

	i = -1;
	found = 0;
	while (g_m.env_export[++i])
	{
		if ((tmp = ft_strjoin(name, "=")) == NULL)
			return (1);
		if (ft_get_var_name_in_export(name, i) == 0)
		{
			free(g_m.env_export[i]);
			if ((g_m.env_export[i] = ft_strjoin(tmp, new_value)) == NULL)
			{
				free(tmp);
				return (1);
			}
			found = 1;
		}
		free(tmp);
	}
	if (found == 0 && (ft_export_bis_next(name, new_value)) == 1)
		return (1);
	return (0);
}

int		ft_export_export(char *input)
{
	int		i;
	size_t	size;
	char	*tmp;

	i = -1;
	while (g_m.env_export[++i])
	{
		if ((tmp = ft_strjoin(input, "=")) == NULL)
			return (1);
		if (ft_strncmp(g_m.env_export[i], tmp, ft_strlen(tmp)) == 0)
		{
			free(tmp);
			return (0);
		}
		free(tmp);
	}
	size = ft_tabsize(g_m.env_export);
	g_m.env_export = (char **)ft_realloc((void **)g_m.env_export, sizeof(char *)
			* (size), sizeof(char *) * (size + 2));
	if ((g_m.env_export[size] = ft_strdup(input)) == NULL)
		return (1);
	return (0);
}
