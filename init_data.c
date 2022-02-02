/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmesnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 09:49:25 by hmesnard          #+#    #+#             */
/*   Updated: 2021/04/21 21:13:44 by hmesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_dpos	*add_sprite(t_d *d, t_ipos p)
{
	t_dpos	*res;
	int		i;

	d->snb++;
	res = malloc(d->snb * sizeof(t_dpos));
	if (!res)
	{
		free(d->s);
		return (0);
	}
	i = 0;
	while (++i < d->snb)
		res[i - 1] = d->s[i - 1];
	res[d->snb - 1].x = p.x + 0.5;
	res[d->snb - 1].y = p.y + 0.5;
	free(d->s);
	return (res);
}

void	init_map_data(t_d *d)
{
	t_ipos	p;
	char	c;

	p.y = 0;
	while (d->map[p.y])
	{
		p.x = 0;
		while (d->map[p.y][p.x])
		{
			c = d->map[p.y][p.x];
			if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
			{
				d->map[p.y][p.x] = '0';
				d->p = (t_dpos){p.x + 0.5, p.y + 0.5};
				d->dir.x = (c == 'E') - (c == 'W');
				d->dir.y = (c == 'S') - (c == 'N');
				d->cam.x = d->dir.y * -(2.0 / 3.0);
				d->cam.y = d->dir.x * (2.0 / 3.0);
			}
			else if (c == '2')
				d->s = add_sprite(d, p);
			p.x++;
		}
		p.y++;
	}
}

void	first_init(t_d *d, t_cub *cub)
{
	size_t	i;

	i = 0;
	while (i < 5)
		d->t[i++].img = NULL;
	d->i.img = NULL;
	d->fcl = cub->fcl;
	d->ccl = cub->ccl;
	d->map = cub->map;
	cub->map = NULL;
	d->mlx = NULL;
	d->win = NULL;
	d->key.up = 0;
	d->key.down = 0;
	d->key.left = 0;
	d->key.right = 0;
	d->key.lleft = 0;
	d->key.lright = 0;
	d->key.mouseleft = 0;
	d->key.mouseright = 0;
	d->snb = 0;
	d->zbuffer = NULL;
	d->sorder = NULL;
	d->sdist = NULL;
	d->s = NULL;
}

int	init_tex(t_d *d, t_cub *cub)
{
	d->t[0].img = mlx_xpm_file_to_image(d->mlx,
			cub->no, &d->t[0].x, &d->t[0].y);
	d->t[1].img = mlx_xpm_file_to_image(d->mlx,
			cub->so, &d->t[1].x, &d->t[1].y);
	d->t[2].img = mlx_xpm_file_to_image(d->mlx,
			cub->we, &d->t[2].x, &d->t[2].y);
	d->t[3].img = mlx_xpm_file_to_image(d->mlx,
			cub->ea, &d->t[3].x, &d->t[3].y);
	d->t[4].img = mlx_xpm_file_to_image(d->mlx,
			cub->s, &d->t[4].x, &d->t[4].y);
	if (!d->t[0].img || !d->t[1].img || !d->t[2].img
		|| !d->t[3].img || !d->t[4].img)
		return (error("Failed to load texture", NULL, NULL));
	d->t[0].addr = mlx_get_data_addr(
			d->t[0].img, &d->t[0].bpp, &d->t[0].len, &d->t[0].e);
	d->t[1].addr = mlx_get_data_addr(
			d->t[1].img, &d->t[1].bpp, &d->t[1].len, &d->t[1].e);
	d->t[2].addr = mlx_get_data_addr(
			d->t[2].img, &d->t[2].bpp, &d->t[2].len, &d->t[2].e);
	d->t[3].addr = mlx_get_data_addr(
			d->t[3].img, &d->t[3].bpp, &d->t[3].len, &d->t[3].e);
	d->t[4].addr = mlx_get_data_addr(
			d->t[4].img, &d->t[4].bpp, &d->t[4].len, &d->t[4].e);
	return (1);
}

int	init_data(t_d *d, t_cub *cub)
{
	first_init(d, cub);
	d->life = 50;
	d->mlx = mlx_init();
	if (!d->mlx)
		return (error("MLX fail", NULL, NULL));
	mlx_get_screen_size(d->mlx, &d->screenx, &d->screeny);
	d->i.x = cub->r.x;
	d->i.y = cub->r.y;
	if (d->i.x > d->screenx)
		d->i.x = d->screenx;
	if (d->i.y > d->screeny)
		d->i.y = d->screeny;
	d->win = mlx_new_window(d->mlx, d->i.x, d->i.y, "cub3d");
	d->i.img = mlx_new_image(d->mlx, d->i.x, d->i.y);
	if (!d->win || !d->i.img)
		return (error("MLX fail", NULL, NULL));
	d->i.addr = mlx_get_data_addr(d->i.img, &d->i.bpp, &d->i.len, &d->i.e);
	init_map_data(d);
	d->zbuffer = malloc(d->i.x * sizeof(double));
	d->sorder = malloc(d->snb * sizeof(int));
	d->sdist = malloc(d->snb * sizeof(double));
	if (!init_tex(d, cub) || !d->zbuffer || !d->sorder || !d->sdist)
		return (0);
	return (free_structs(1, cub, NULL));
}
