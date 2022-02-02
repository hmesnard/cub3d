/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cub_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmesnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 13:08:26 by hmesnard          #+#    #+#             */
/*   Updated: 2021/04/21 17:10:44 by hmesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	overflow(char *line, size_t max)
{
	int					i;
	unsigned long long	nb;

	i = 0;
	nb = 0;
	if (!('0' <= line[i] && line[i] <= '9'))
		return (1);
	while ('0' <= line[i] && line[i] <= '9')
	{
		nb = nb * 10 + (line[i++] - 48);
		if (nb > max)
			return (1);
	}
	return (0);
}

int	overflow_colors(char *line)
{
	size_t	i;

	i = 0;
	if (overflow(line + i, UCHAR_MAX))
		return (1);
	while (ft_isdigit(line[i]))
		i++;
	skip_spaces(line, &i);
	if (line[i] == ',')
		i++;
	skip_spaces(line, &i);
	if (overflow(line + i, UCHAR_MAX))
		return (1);
	while (ft_isdigit(line[i]))
		i++;
	skip_spaces(line, &i);
	if (line[i] == ',')
		i++;
	skip_spaces(line, &i);
	if (overflow(line + i, UCHAR_MAX))
		return (1);
	return (0);
}

void	skip_spaces(char *line, size_t *i)
{
	while (ft_isspace(line[*i]))
		(*i)++;
}

int	line_isspace(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] && line[i] != '\n')
		if (!ft_isspace(line[i++]))
			return (0);
	return (1);
}

int	is_id(char *line, char *id)
{
	size_t	i;

	i = 0;
	while (id[i])
	{
		if (id[i] != line[i])
			return (0);
		i++;
	}
	if (ft_isspace(line[i]))
		return (1);
	else
		return (0);
}
