/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 15:17:19 by tpierre           #+#    #+#             */
/*   Updated: 2020/11/12 16:43:43 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	define BUFFER_SIZE 4096
#	include "../includes/minishell.h"

int		ft_has_line(char **str, char **line)
{
	int		i;
	char	*temp;

	i = 0;
	while ((*str)[i] != '\0' && (*str)[i] != '\n')
		i++;
	if (!(temp = ft_strdup(*str)))
		return (-1);
	free(*str);
	if (!(*line = ft_substr(temp, 0, i)))
	{
		free(temp);
		return (-1);
	}
	if (!(*str = ft_strdup(temp + i + 1)))
	{
		free(temp);
		return (-1);
	}
	free(temp);
	return (1);
}

int		ft_eof(char **str, char **line)
{
	*line = ft_strdup(*str);
	free(*str);
	*str = NULL;
	return (0);
}

int		ft_handle_error(char **str, char **buffer)
{
	free(*str);
	free(*buffer);
	return (-1);
}

char	*ft_read(char **str, char **buffer)
{
	char *temp;

	temp = ft_strjoin(*str, *buffer);
	free(*str);
	str = &temp;
	return (*str);
}

int		get_next_line(int fd, char **line)
{
	char	*buffer;
	int		rsize;

	if (!(buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	if (line == NULL || fd < 0 || read(fd, buffer, 0) < 0 || BUFFER_SIZE < 1)
		return (ft_handle_error(&g_str, &buffer));
	if (g_str == NULL)
		g_str = ft_strdup("");
	while (!(ft_strchr(g_str, '\n')) &&
		(rsize = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[rsize] = '\0';
		g_str = ft_read(&g_str, &buffer);
	}
	free(buffer);
	if (ft_strchr(g_str, '\n'))
		return (ft_has_line(&g_str, line));
	else
		return (ft_eof(&g_str, line));
}
