/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 15:42:42 by tpierre           #+#    #+#             */
/*   Updated: 2020/12/17 15:16:36 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_encode_input(char *input)
{
	int		i;
	int		quote;
	int		double_quote;

	quote = 0;
	double_quote = 0;
	i = -1;
	while (input[++i])
	{
		if (i > 0 && input[i - 1] == '\\' &&
				((input[i] == '\'' && !double_quote && !quote) ||
				(input[i] == '"' && !quote)))
			input[i - 1] = 3;
		else if (ft_escape_backslashes(i, input, quote, double_quote))
			(void)i;
		else if (input[i] == '\'')
			ft_handle_quote(&quote, &double_quote, &input[i]);
		else if (input[i] == '"')
			ft_handle_double_quote(&quote, &double_quote, &input[i]);
		else
			ft_handle_char_in_quotes(quote, double_quote, &input[i]);
	}
	if (quote || double_quote)
		return (-1);
	return (0);
}

void	ft_parse_command(char **cmd, char *input)
{
	if (ft_strcmp(cmd[0], "echo") == 0)
		ft_handle_echo(cmd);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		ft_handle_pwd();
	else if (ft_strcmp(cmd[0], "cd") == 0)
		ft_handle_cd(cmd);
	else if (ft_strcmp(cmd[0], "export") == 0)
		ft_handle_export(cmd);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		ft_handle_unset(cmd);
	else if (ft_strcmp(cmd[0], "env") == 0)
		ft_print_env();
	else if (ft_strcmp(cmd[0], "exit") == 0)
		ft_handle_exit(cmd);
	else if (ft_strcmp(cmd[0], "$?") == 0)
	{
		ft_putnbr_fd(g_status, 1);
		ft_putstr_fd(" : command not found\n", 1);
		g_status = 127;
	}
	else if (ft_strlen(cmd[0]) != 0)
	{
		ft_execve(cmd, input);
		g_m.has_error = 1;
	}
}

void	ft_parse(void)
{
	int		i;
	char	*tmp;

	if ((ft_encode_input(g_m.global_input)) == -1)
	{
		ft_putstr_fd("minishell : quote is not properly closed\n", 1);
		free(g_m.global_input);
		return ;
	}
	if ((g_m.global_input = ft_check_global_input(g_m.global_input)) == NULL)
		return ;
	g_m.global_input = ft_replace_multiple_spaces(g_m.global_input);
	g_m.commands = ft_split(g_m.global_input, ';');
	free(g_m.global_input);
	i = -1;
	while (g_m.commands[++i])
	{
		tmp = ft_strtrim(g_m.commands[i], " ;");
		free(g_m.commands[i]);
		g_m.commands[i] = ft_parse_variable(tmp);
		free(tmp);
		ft_pipe(g_m.commands[i]);
	}
	ft_tabdel((void **)g_m.commands);
}
