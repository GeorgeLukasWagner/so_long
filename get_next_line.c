/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwagner <gwagner@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:40:43 by gwagner           #+#    #+#             */
/*   Updated: 2024/07/09 16:15:32 by gwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	getindex(char **s_buf)
{
	int	i;

	i = 0;
	while ((*s_buf)[i] && (*s_buf)[i] != '\n')
		i++;
	if ((*s_buf)[i] == '\n')
		i++;
	return (i);
}

static char	*filltheline(char **s_buf)
{
	char	*line;
	char	*temp;
	int		i;
	int		j;

	i = getindex(s_buf);
	j = -1;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	while (++j < i)
		line[j] = (*s_buf)[j];
	line[j] = '\0';
	temp = ft_strdup(*s_buf + i);
	if (!temp)
	{
		free(line);
		*s_buf = NULL;
		return (NULL);
	}
	free(*s_buf);
	*s_buf = temp;
	return (line);
}

static int	readdata(int fd, char **s_buf)
{
	char	buf[BUFFER_SIZE + 1];
	char	*temp;
	int		read_bytes;

	read_bytes = 1;
	while (read_bytes > 0 && !ft_strchr(*s_buf, '\n'))
	{
		read_bytes = read(fd, buf, BUFFER_SIZE);
		if (read_bytes < 0)
			return (-1);
		buf[read_bytes] = '\0';
		temp = ft_strjoin(*s_buf, buf);
		free(*s_buf);
		*s_buf = temp;
		if (!*s_buf)
			return (-1);
	}
	return (read_bytes);
}

static void	*freebuf(char **s_buf)
{
	free(*s_buf);
	*s_buf = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*s_buf;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!s_buf)
		s_buf = ft_strdup("");
	if (!s_buf)
		return (NULL);
	if (readdata(fd, &s_buf) < 0)
	{
		free(s_buf);
		s_buf = NULL;
		return (NULL);
	}
	if (!*s_buf)
		return (freebuf(&s_buf));
	line = filltheline(&s_buf);
	if (!line)
	{
		free(s_buf);
		s_buf = NULL;
	}
	return (line);
}
