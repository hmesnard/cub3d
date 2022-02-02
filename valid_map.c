/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmesnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 16:20:57 by hmesnard          #+#    #+#             */
/*   Updated: 2021/04/21 10:27:51 by hmesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	surrounded(char **map, size_t x, size_t y)
{
	if (!y || !x || !map[y + 1] || !map[y][x + 1])
		return (0);
	else if (map[y - 1][x] == ' ' || map[y + 1][x] == ' '
			|| map[y][x - 1] == ' ' || map[y][x + 1] == ' ')
		return (0);
	return (1);
}

int	block(char **map, size_t x, size_t y, int *player)
{
	if (map[y][x] == '0' || map[y][x] == '2')
	{
		if (!surrounded(map, x, y))
			return (error("Map not surrounded", NULL, NULL));
	}
	else if (map[y][x] == 'N' || map[y][x] == 'S'
			|| map[y][x] == 'W' || map[y][x] == 'E')
	{
		if (!*player)
			*player = 1;
		else
			return (error("Duplicate player position in map", NULL, NULL));
		if (!surrounded(map, x, y))
			return (error("Map not surrounded", NULL, NULL));
	}
	else if (map[y][x] != ' ' && map[y][x] != '1')
		return (error("Invalid character im map", NULL, NULL));
	return (1);
}

int	valid_map(char **map)
{
	size_t	x;
	size_t	y;
	int		player;

	player = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (!block(map, x, y, &player))
				return (0);
			x++;
		}
		y++;
	}
	if (!player)
		return (error("Player not found in map", NULL, NULL));
	return (1);
}
