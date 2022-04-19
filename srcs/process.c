/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 13:50:20 by tpierre           #+#    #+#             */
/*   Updated: 2020/12/18 11:02:18 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_search_in_path(char *path, char *cmd, char **tmp)
{
	char	*temp;

	temp = ft_strjoin(path, "/");
	tmp[0] = ft_strjoin(temp, cmd);
	free(temp);
}

char	*get_relative_path(char *cmd)
{
	char		**paths;
	struct stat	buf;
	char		*tmp;
	char		*path;
	int			i;

	i = -1;
	if ((path = ft_find_env("PATH")) == NULL)
		return (NULL);
	paths = ft_split(path, ':');
	while (paths[++i])
	{
		ft_search_in_path(paths[i], cmd, &tmp);
		if (!stat(tmp, &buf))
		{
			free(path);
			ft_tabdel((void **)paths);
			return (tmp);
		}
		free(tmp);
	}
	free(path);
	ft_tabdel((void **)paths);
	return (NULL);
}

char	*get_path(char *cmd)
{
	struct stat	buf;

	if (!ft_strncmp("/", cmd, 1) || !ft_strncmp("./", cmd, 2))
		return (!stat(cmd, &buf) ? ft_strjoin(cmd, "") : 0);
	else
		return (get_relative_path(cmd));
}

void	ft_execve_next(char **cmd, int status, char **tab)
{
	char	*path;

	path = get_path(cmd[0]);
	if (path == NULL)
		ft_free_for_ft_execve(1, cmd, strerror(errno), tab);
	else
		status = execve(path, tab, g_m.env);
	if (status < 0)
	{
		free(path);
		ft_free_for_ft_execve(2, cmd, strerror(errno), tab);
	}
}

void	ft_execve(char **cmd, char *input)
{
	int		status;
	char	**tab;

	tab = ft_split(input, ' ');
	status = 0;
	if ((g_pid = fork()) == 0)
		ft_execve_next(cmd, status, tab);
	else if (g_pid < 0)
	{
		g_status = 127;
		ft_error("minishell: fork error\n");
	}
	else
	{
		waitpid(g_pid, &status, 0);
		if (WIFEXITED(status))
			g_status = WEXITSTATUS(status);
	}
	ft_tabdel((void **)tab);
}
