/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cub_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmesnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 10:57:40 by hmesnard          #+#    #+#             */
/*   Updated: 2021/04/21 19:16:40 by hmesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_path(char *line, char **path)
{
	size_t	i;

	if (*path)
		return (error("Duplicate texture line", NULL, NULL));
	i = 0;
	while (ft_isalpha(line[i]))
		i++;
	while (ft_isspace(line[i]))
		i++;
	*path = ft_strdup(line + i);
	if (!*path)
		return (error("Failed to get texture path", NULL, NULL));
	return (1);
}

int	get_color(char *line, int *color)
{
	size_t	i;
	int		rgb[3];

	if (*color != (int)0xFFFFFFFF)
		return (error("Duplicate color line", NULL, NULL));
	i = 0;
	while (ft_isalpha(line[i]))
		i++;
	skip_spaces(line, &i);
	rgb[0] = ft_atoi(line + i);
	while (ft_isdigit(line[i]))
		i++;
	skip_spaces(line, &i);
	i++;
	skip_spaces(line, &i);
	rgb[1] = ft_atoi(line + i);
	while (ft_isdigit(line[i]))
		i++;
	skip_spaces(line, &i);
	i++;
	skip_spaces(line, &i);
	rgb[2] = ft_atoi(line + i);
	*color = (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
	return (1);
}

int	get_res(char *line, t_ipos *res, char *rbool)
{
	size_t	i;

	if (*rbool)
		return (error("Duplicate resolution line", NULL, NULL));
	i = 0;
	while (ft_isalpha(line[i]))
		i++;
	skip_spaces(line, &i);
	res->x = ft_atoi(line + i);
	while (ft_isdigit(line[i]))
		i++;
	skip_spaces(line, &i);
	res->y = ft_atoi(line + i);
	*rbool = 1;
	if (res->x == 0 || res->y == 0)
		return (error("Invalid resolution line", NULL, NULL));
	return (1);
}

int	get_cub_path(t_cub *cub, char *line)
{
	if (is_id(line, "NO"))
	{
		if (!get_path(line, &cub->no))
			return (0);
	}
	else if (is_id(line, "SO"))
	{
		if (!get_path(line, &cub->so))
			return (0);
	}
	else if (is_id(line, "WE"))
	{
		if (!get_path(line, &cub->we))
			return (0);
	}
	else if (is_id(line, "EA"))
	{
		if (!get_path(line, &cub->ea))
			return (0);
	}
	else if (is_id(line, "S"))
		if (!get_path(line, &cub->s))
			return (0);
	return (1);
}

int	get_cub_value(t_cub *cub, char *line)
{
	while (ft_isspace(*line))
		line++;
	if (!valid_line(line))
		return (0);
	else if (is_id(line, "R"))
	{
		if (!get_res(line, &cub->r, &cub->rbool))
			return (0);
	}
	else if (is_id(line, "NO") || is_id(line, "SO") || is_id(line, "WE")
		|| is_id(line, "EA") || is_id(line, "S"))
	{
		if (!get_cub_path(cub, line))
			return (0);
	}
	else if (is_id(line, "F"))
	{
		if (!get_color(line, &cub->fcl))
			return (0);
	}
	else if (is_id(line, "C"))
		if (!get_color(line, &cub->ccl))
			return (0);
	return (1);
}
