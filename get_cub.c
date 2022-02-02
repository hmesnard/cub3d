/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cub.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmesnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 10:55:20 by hmesnard          #+#    #+#             */
/*   Updated: 2021/04/21 19:16:17 by hmesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"

int	init_cub_gnl(t_cub *cub, t_gnl *gnl, char **av)
{
	cub->rbool = 0;
	cub->r.x = 0;
	cub->r.y = 0;
	cub->no = NULL;
	cub->so = NULL;
	cub->we = NULL;
	cub->ea = NULL;
	cub->s = NULL;
	cub->fcl = 0xFFFFFFFF;
	cub->ccl = 0xFFFFFFFF;
	cub->map = NULL;
	gnl->fd = open(av[1], O_RDONLY);
	if (gnl->fd < 0)
		return (error("Open fail", NULL, NULL));
	gnl->ret = 1;
	gnl->line = NULL;
	return (1);
}

int	skip_space_lines(t_gnl *gnl)
{
	while (1)
	{
		gnl->ret = get_next_line(gnl->fd, &gnl->line);
		if (gnl->ret < 0)
			return (error("GNL error before getting map", NULL, NULL));
		else if (!gnl->ret)
			return (error("EOF before getting map", gnl->line, NULL));
		if (!line_isspace(gnl->line))
			break ;
		free(gnl->line);
	}
	return (1);
}

int	strjoin_map(char **save, const char *buf)
{
	char	*res;
	int		lensave;
	int		lenbuf;

	lensave = ft_strlen(*save);
	lenbuf = ft_strlen(buf);
	res = malloc((lensave + lenbuf + 2) * sizeof(char));
	if (!res)
	{
		free(*save);
		return (0);
	}
	ft_memmove(res, *save, lensave);
	res[lensave] = '\n';
	ft_memmove(res + lensave + 1, buf, lenbuf);
	res[lensave + 1 + lenbuf] = '\0';
	free(*save);
	*save = res;
	return (1);
}

int	get_map(t_gnl gnl, char ***map)
{
	char	*strmap;

	strmap = NULL;
	if (!skip_space_lines(&gnl))
		return (0);
	while (gnl.ret && !line_isspace(gnl.line))
	{
		if (!strjoin_map(&strmap, gnl.line))
			return (error("Strjoin fail while getting map", strmap, gnl.line));
		free(gnl.line);
		gnl.ret = get_next_line(gnl.fd, &gnl.line);
		if (gnl.ret < 0)
			return (error("GNL error while getting map", strmap, NULL));
	}
	if (!strjoin_map(&strmap, gnl.line))
		return (error("Strjoin fail while getting map", strmap, gnl.line));
	free(gnl.line);
	if (!split_map(strmap, map))
		return (error("Split_map fail", strmap, NULL));
	free(strmap);
	if (!valid_map(*map))
		return (0);
	return (1);
}

int	get_cub(char **av, t_cub *cub)
{
	t_gnl	gnl;

	if (!init_cub_gnl(cub, &gnl, av))
		return (0);
	while (gnl.ret && (!cub->no || !cub->so || !cub->we || !cub->ea || !cub->s
			|| !cub->rbool
			|| cub->fcl == (int)0xFFFFFFFF || cub->ccl == (int)0xFFFFFFFF))
	{
		gnl.ret = get_next_line(gnl.fd, &gnl.line);
		if (gnl.ret < 0)
			return (error("GNL error while getting elems", NULL, NULL));
		else if (valid_id(gnl.line))
		{
			if (!get_cub_value(cub, gnl.line))
				return (error(NULL, gnl.line, NULL));
		}
		else if (!line_isspace(gnl.line))
			return (error("Invalid line in elems", gnl.line, NULL));
		free(gnl.line);
	}
	if (!get_map(gnl, &cub->map))
		return (0);
	close(gnl.fd);
	return (1);
}
