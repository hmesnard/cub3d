/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmesnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 17:50:55 by hmesnard          #+#    #+#             */
/*   Updated: 2021/04/20 12:44:38 by hmesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned int	i;

	i = 0;
	if ((dest || src) && (dest != src))
	{
		if (src < dest)
			while (n--)
				*((char *)dest + n) = *((char *)src + n);
		else
		{
			while (i < n)
			{
				*((char *)dest + i) = *((char *)src + i);
				i++;
			}
		}
	}
	return (dest);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*strjoin_free(char *save, const char *buf)
{
	char	*res;
	int		lensave;
	int		lenbuf;

	lensave = ft_strlen(save);
	lenbuf = ft_strlen(buf);
	res = malloc((lensave + lenbuf + 1) * sizeof(char));
	if (!res)
		return (NULL);
	ft_memmove(res, save, lensave);
	ft_memmove(res + lensave, buf, lenbuf);
	res[lensave + lenbuf] = '\0';
	free(save);
	return (res);
}

int	nl(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		if (s[i++] == '\n')
			return (1);
	return (0);
}
