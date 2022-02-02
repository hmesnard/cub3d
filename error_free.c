/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmesnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 17:15:39 by hmesnard          #+#    #+#             */
/*   Updated: 2021/04/21 21:13:26 by hmesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	error(char *str, void *to_free1, void *to_free2)
{
	if (str)
		printf("Error\n%s\n", str);
	if (to_free1)
		free(to_free1);
	if (to_free2)
		free(to_free2);
	return (0);
}

void	free_map(char **map)
{
	size_t	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_cub(t_cub *cub)
{
	if (cub->no)
		free(cub->no);
	if (cub->so)
		free(cub->so);
	if (cub->we)
		free(cub->we);
	if (cub->ea)
		free(cub->ea);
	if (cub->s)
		free(cub->s);
	if (cub->map)
		free_map(cub->map);
}

void	free_data(t_d *d)
{
	size_t	i;

	i = 0;
	while (i < 5)
	{
		if (d->t[i].img)
			mlx_destroy_image(d->mlx, d->t[i].img);
		i++;
	}
	if (d->i.img)
		mlx_destroy_image(d->mlx, d->i.img);
	if (d->zbuffer)
		free(d->zbuffer);
	if (d->sorder)
		free(d->sorder);
	if (d->sdist)
		free(d->sdist);
	if (d->s)
		free(d->s);
	if (d->win)
		mlx_destroy_window(d->mlx, d->win);
	if (d->map)
		free_map(d->map);
}

int	free_structs(int ret, t_cub *cub, t_d *d)
{
	if (cub)
		free_cub(cub);
	if (d)
		free_data(d);
	return (ret);
}
