/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cub_valid_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmesnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 13:06:58 by hmesnard          #+#    #+#             */
/*   Updated: 2021/04/21 19:00:19 by hmesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t	end_res_line(char *line)
{
	size_t	i;

	i = 0;
	while (ft_isalpha(line[i]))
		i++;
	skip_spaces(line, &i);
	if (overflow(line + i, INT_MAX))
		return (0);
	while (ft_isdigit(line[i]))
		i++;
	skip_spaces(line, &i);
	if (overflow(line + i, INT_MAX))
		return (0);
	while (ft_isdigit(line[i]))
		i++;
	skip_spaces(line, &i);
	return (i);
}

size_t	end_path_line(char *line)
{
	size_t	i;

	i = 0;
	while (ft_isalpha(line[i]))
		i++;
	skip_spaces(line, &i);
	while (line[i] && !ft_isspace(line[i]))
		i++;
	skip_spaces(line, &i);
	return (i);
}

size_t	end_color_line(char *line)
{
	size_t	i;

	i = 0;
	while (ft_isalpha(line[i]))
		i++;
	skip_spaces(line, &i);
	if (overflow_colors(line + i))
		return (0);
	while (ft_isdigit(line[i]))
		i++;
	skip_spaces(line, &i);
	if (line[i++] != ',')
		return (0);
	skip_spaces(line, &i);
	while (ft_isdigit(line[i]))
		i++;
	skip_spaces(line, &i);
	if (line[i++] != ',')
		return (0);
	skip_spaces(line, &i);
	while (ft_isdigit(line[i]))
		i++;
	skip_spaces(line, &i);
	return (i);
}

int	valid_line(char *line)
{
	if (is_id(line, "R") && line[end_res_line(line)] != '\0')
		return (error("Invalid resolution line", NULL, NULL));
	else if ((is_id(line, "NO") || is_id(line, "SO") || is_id(line, "WE")
			|| is_id(line, "EA") || is_id(line, "S"))
		&& line[end_path_line(line)] != '\0')
		return (error("Invalid texture line", NULL, NULL));
	else if ((is_id(line, "F") || is_id(line, "C"))
		&& line[end_color_line(line)] != '\0')
		return (error("Invalid color line", NULL, NULL));
	return (1);
}

int	valid_id(char *line)
{
	while (ft_isspace(*line))
		line++;
	if (is_id(line, "R") || is_id(line, "NO") || is_id(line, "SO")
		|| is_id(line, "WE") || is_id(line, "EA") || is_id(line, "S")
		|| is_id(line, "F") || is_id(line, "C"))
		return (1);
	return (0);
}
