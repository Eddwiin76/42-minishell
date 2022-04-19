/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 10:04:27 by tpierre           #+#    #+#             */
/*   Updated: 2020/12/18 10:48:52 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef MINISHELL_H
#	define MINISHELL_H

#	include "../libft/libft.h"
#	include <signal.h>
#	include <stdlib.h>
#	include <stdio.h>
#	include <unistd.h>
#	include <fcntl.h>
#	include <errno.h>
#	include <string.h>
#	include <sys/wait.h>
#	include <sys/stat.h>

char			*g_str;
int				g_status;
pid_t			g_pid;

typedef struct	s_struct
{
	char	*global_input;
	char	**env;
	char	**env_export;
	char	**commands;
	char	**args;
	char	**global_split;
	int		*global_split_execute;
	int		*global_split_types;
	int		has_error;
}				t_struct;

t_struct		g_m;

int				get_next_line(int fd, char **line);
void			ft_set_env(char **env);
void			ft_print_env(void);
void			ft_print_export(void);
void			ft_error(char *error_message);
void			ft_exit(void);
void			ft_prompt(void);
void			ft_handle_signal(void);
void			ft_parse(void);
void			ft_handle_cd(char **input);
void			ft_handle_echo(char **input);
void			ft_handle_export(char **input);
int				ft_export(char *name, char *new_value);
int				ft_export_bis(char *name, char *new_value);
int				ft_export_export(char *input);
void			ft_handle_unset(char **input);
void			ft_handle_pwd(void);
char			*ft_find_env(char *name);
void			ft_sort_env(void);
void			ft_handle_exit(char **cmd);
int				ft_isalldigit_sign(char *str);
int				ft_strchr_index(const char *s, int c);
char			*ft_parse_variable(char *input);
void			ft_handle_split_positions(char *input, int **split_tab, char c);
char			*ft_check_global_input(char *input);
char			*ft_replace_multiple_spaces(char *input);
void			ft_execve(char **cmd, char *input);
int				ft_pipe(char *input);
void			ft_parse_command(char **cmd, char *input);
char			*ft_remove_quotes(char **str);
void			ft_print_error_unexpected_token(char token);
int				ft_multiple_split_part_1(char *str);
void			ft_print_error_ambiguous_redirect(void);
void			ft_print_error_unexpected_token_x2(char token);
int				ft_find_last_file(void);
int				ft_find_last_command(void);
int				ft_compute_flag(int i);
void			ft_handle_file_error(void);
void			ft_handle_fork(int i, char *input);
int				ft_free_for_ft_pipe(void);
void			ft_split_args(int i);
int				ft_print_error_directory(char **tab);
void			ft_decode_command(char **str);
int				ft_set_escape(char *input, int i, char c);
int				ft_escape_backslashes(int i, char *input, int quote,
					int double_quote);
void			ft_handle_char_in_quotes(int quote, int dquote, char *c);
void			ft_handle_quote(int *quote, int *double_quote, char *c);
void			ft_handle_double_quote(int *quote, int *double_quote, char *c);
void			ft_free_for_ft_execve(int i, char **cmd, char *error,
					char **tab);
void			ft_add_to_int_tab(char *str, int i, int count);
void			ft_handle_back_chevron(void);
void			ft_create_global_split_execute(void);
void			ft_handle_fucked_up_case(void);
int				ft_check_empty_arg(void);
int				ft_check_variable_unset(char *input);
int				ft_get_var_name_in_unset(char *name, char *env);
void			ft_unset_next(char **input, int k);
void			ft_unset_export_next(char **input, int k);
void			ft_free_for_ft_handle_fork(void);
#	endif
