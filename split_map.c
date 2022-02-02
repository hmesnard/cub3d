/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmesnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 14:04:27 by hmesnard          #+#    #+#             */
/*   Updated: 2021/04/20 15:35:25 by hmesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmesnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 12:06:42 by hmesnard          #+#    #+#             */
/*   Updated: 2021/04/20 14:04:14 by hmesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_split_values(const char *str, size_t *nbmots, size_t *maxlen)
{
	size_t	i;
	size_t	linelength;

	i = 0;
	*nbmots = 0;
	*maxlen = 0;
	while (str[i])
	{
		while (str[i] == '\n')
			i++;
		if (!(str[i] == '\n') && str[i])
		{
			linelength = 0;
			while (!(str[i] == '\n') && str[i] != 0)
			{
				linelength++;
				i++;
			}
			if (*maxlen < linelength)
				*maxlen = linelength;
			(*nbmots)++;
		}
	}
}

static void	fill_res(const char *str, char **res)
{
	int	i;
	int	mot;
	int	lettre;

	i = 0;
	mot = 0;
	while (str[i])
	{
		while (str[i] == '\n')
			i++;
		if (!(str[i] == '\n') && str[i] != 0)
		{
			lettre = 0;
			while (!(str[i] == '\n') && str[i] != 0)
			{
				res[mot][lettre] = str[i];
				lettre++;
				i++;
			}
			res[mot][lettre] = 0;
			mot++;
		}
	}
}

static int	make_map_better(char **res, size_t maxlen)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (res[y])
	{
		x = 0;
		while (res[y][x])
		{
			if (ft_isspace(res[y][x]))
				res[y][x] = ' ';
			x++;
		}
		while (x < maxlen)
			res[y][x++] = ' ';
		res[y][x] = '\0';
		y++;
	}
	return (1);
}

int	split_map(char *str, char ***map)
{
	size_t	nb;
	size_t	maxlen;
	size_t	i;

	if (!str)
		return (0);
	str--;
	while (line_isspace(++str))
		while (*str && *str != '\n')
			str++;
	get_split_values(str, &nb, &maxlen);
	*map = malloc((nb + 1) * sizeof(char *));
	if (!*map)
		return (0);
	(*map)[nb] = 0;
	i = 0;
	while (i < nb)
	{
		(*map)[i] = malloc((maxlen + 1) * sizeof(char));
		if (!(*map)[i++])
			return (0);
	}
	fill_res(str, *map);
	return (make_map_better(*map, maxlen));
}
