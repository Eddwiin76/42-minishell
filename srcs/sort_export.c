/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 15:49:01 by mlaraki           #+#    #+#             */
/*   Updated: 2020/11/30 12:29:06 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_sorted_print_env_next(char *tmp1, char *tmp2, int j)
{
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(tmp1, 1);
	if (j)
	{
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(tmp2, 1);
		ft_putchar_fd('"', 1);
	}
}

void	ft_sorted_print_env(char **sorted_env)
{
	int		i;
	int		j;
	char	*tmp1;
	char	*tmp2;

	i = -1;
	while (sorted_env[++i])
	{
		j = ft_strchr_index(sorted_env[i], '=');
		if (j != -1)
		{
			tmp1 = ft_substr(sorted_env[i], 0, j);
			tmp2 = ft_substr(sorted_env[i], j + 1,
					ft_strlen(sorted_env[i]) - j - 1);
			ft_sorted_print_env_next(tmp1, tmp2, j);
			free(tmp1);
			free(tmp2);
		}
		else
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(sorted_env[i], 1);
		}
		ft_putstr_fd("\n", 1);
	}
}

void	ft_sort_env_next(size_t size, char **sorted_env)
{
	size_t	i;
	size_t	j;
	char	*tmp;

	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size - 1)
			if (ft_strcmp(sorted_env[j], sorted_env[j + 1]) > 0)
			{
				tmp = sorted_env[j];
				sorted_env[j] = sorted_env[j + 1];
				sorted_env[j + 1] = tmp;
			}
	}
}

void	ft_sort_env(void)
{
	size_t	i;
	char	**sorted_env;
	size_t	size;

	size = ft_tabsize(g_m.env_export);
	if ((sorted_env = (char **)malloc(sizeof(char *) * (size + 1))) == NULL)
		ft_error("Memory allocation failed");
	i = -1;
	while (++i < size)
		if ((sorted_env[i] = ft_strdup(g_m.env_export[i])) == NULL)
		{
			ft_tabdel((void **)sorted_env);
			ft_error("Memory allocation failed");
		}
	sorted_env[i] = NULL;
	ft_sort_env_next(size, sorted_env);
	ft_sorted_print_env(sorted_env);
	ft_tabdel((void **)sorted_env);
	g_status = 0;
}
