/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 16:12:07 by mlaraki           #+#    #+#             */
/*   Updated: 2020/11/12 16:28:30 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_update_env_pwd(void)
{
	char pwd[4096];
	char *oldpwd;

	if ((oldpwd = ft_find_env("PWD")) == NULL)
		oldpwd = ft_strdup("");
	ft_export("OLDPWD", oldpwd);
	getcwd(pwd, 4096);
	ft_export("PWD", pwd);
	free(oldpwd);
}

void	ft_cd_home(void)
{
	char *env_value;

	env_value = ft_find_env("HOME");
	if (env_value == NULL)
	{
		g_status = 1;
		ft_putstr_fd("minishell: cd: « HOME » undefined\n", 1);
	}
	else
	{
		g_status = 0;
		chdir(env_value);
		ft_update_env_pwd();
		free(env_value);
	}
}

void	ft_cd_to(char *path)
{
	if (chdir(path) < 0)
	{
		ft_putstr_fd("minishell: cd: ", 1);
		ft_putstr_fd(path, 1);
		ft_putstr_fd(": No such file or directory\n", 1);
		g_status = 1;
	}
	else
	{
		g_status = 0;
		ft_update_env_pwd();
	}
}

void	ft_handle_cd_next(char **input)
{
	char *env_home;
	char *dest;
	char *tmp;

	env_home = ft_find_env("HOME");
	if (env_home == NULL)
	{
		ft_putstr_fd("minishell: cd: « HOME » undefined\n", 1);
		g_status = 1;
		free(env_home);
		return ;
	}
	if ((dest = malloc(sizeof(char) * ((ft_strlen(input[1]) - 1)
			+ ft_strlen(env_home) + 1))) == NULL)
		ft_error("Memory allocation failed");
	ft_strcpy(dest, env_home);
	tmp = ft_substr(input[1], 1, ft_strlen(input[1]));
	ft_strcat(dest, tmp);
	ft_cd_to(dest);
	free(dest);
	free(tmp);
	free(env_home);
}

void	ft_handle_cd(char **input)
{
	int argsize;
	int input_len;

	argsize = ft_tabsize(input);
	if (argsize > 2)
	{
		g_status = 1;
		ft_putstr_fd("minishell: cd: too many arguments\n", 1);
	}
	else if (argsize == 1)
		ft_cd_home();
	else
	{
		input_len = ft_strlen(input[1]);
		if (input_len == 1 && input[1][0] == '~')
			ft_cd_home();
		else if (input_len >= 2 && input[1][0] == '~' && input[1][1] == '/')
			ft_handle_cd_next(input);
		else
			ft_cd_to(input[1]);
	}
}
