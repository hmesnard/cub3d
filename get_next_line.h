/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmesnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 17:50:38 by hmesnard          #+#    #+#             */
/*   Updated: 2021/04/20 12:46:38 by hmesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFFER_SIZE 10

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

char	*get_line(const char *s);

char	*get_save(char *s);

int		free_end(int return_value, char **line, char **save, char **buf);

int		get_next_line(int fd, char **line);

void	*ft_memmove(void *dest, const void *src, size_t n);

size_t	ft_strlen(const char *s);

char	*strjoin_free(char *save, const char *buf);

int		nl(const char *s);

#endif
