/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmesnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 17:50:29 by hmesnard          #+#    #+#             */
/*   Updated: 2021/04/20 12:42:35 by hmesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_line(const char *s)
{
	char	*res;
	int		i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	res = malloc((i + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*get_save(char *s)
{
	char	*res;
	int		reslen;
	int		i;
	int		j;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	reslen = 0;
	if (s[i])
		reslen = ft_strlen(s + i + 1);
	res = malloc((reslen + 1) * sizeof(char));
	if (!res)
		return (NULL);
	j = 0;
	if (s[i])
		i++;
	while (s[i])
		res[j++] = s[i++];
	res[j] = '\0';
	free(s);
	return (res);
}

int	free_end(int return_value, char **line, char **save, char **buf)
{
	if (line)
	{
		free(*line);
		*line = NULL;
	}
	if (save)
	{
		free(*save);
		*save = NULL;
	}
	if (buf)
	{
		free(*buf);
		*buf = NULL;
	}
	return (return_value);
}

int	get_next_line2(char **line, char **save, int readret)
{
	*line = get_line(*save);
	if (!*line)
		return (free_end(-1, NULL, save, NULL));
	*save = get_save(*save);
	if (!*save)
		return (free_end(-1, line, save, NULL));
	if (!readret)
		return (free_end(0, NULL, save, NULL));
	return (1);
}

int	get_next_line(int fd, char **line)
{
	static char	*save;
	char		*buf;
	int			readret;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE < 1)
		return (-1);
	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!line || !buf)
		return (free_end(-1, NULL, &save, NULL));
	readret = 1;
	while (!nl(save) && readret)
	{
		readret = read(fd, buf, BUFFER_SIZE);
		if (readret == -1)
			return (free_end(-1, NULL, &save, &buf));
		buf[readret] = '\0';
		save = strjoin_free(save, buf);
		if (!save)
			return (free_end(-1, NULL, &save, &buf));
	}
	free(buf);
	return (get_next_line2(line, &save, readret));
}
