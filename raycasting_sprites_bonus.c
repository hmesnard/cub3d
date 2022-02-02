/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_sprites.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmesnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 13:27:47 by hmesnard          #+#    #+#             */
/*   Updated: 2021/04/21 16:40:52 by hmesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_sprite(t_d *d, t_spr *spr, int stripe, int y)
{
	while (stripe < spr->dend.x)
	{
		spr->tex.x = (int)(256 * (stripe - (-spr->res.x / 2 + spr->screenX))
				* d->t[4].x / spr->res.x) / 256;
		if (0 < spr->trans.y && spr->trans.y < d->zbuffer[stripe]
			&& 0 <= stripe && stripe < d->i.x)
		{
			y = spr->dstart.y;
			while (y < spr->dend.y)
			{
				spr->d = y * 256 - d->i.y * 128 + spr->res.y * 128;
				spr->tex.y = ((spr->d * d->t[4].y) / spr->res.y) / 256;
				if (0 <= spr->tex.x && spr->tex.x < d->t[4].x
					&& 0 <= spr->tex.y && spr->tex.y < d->t[4].y)
				{
					pixel_get(&d->t[4], spr->tex.x, spr->tex.y, &spr->color);
					if (spr->color)
						pixel_put(&d->i, stripe, y, shadow(spr->color,
								((10 - spr->trans.y) / 10)));
				}
				y++;
			}
		}
		stripe++;
	}
}

void	set_sprite_vars(t_d *d, t_spr *spr, int i)
{
	spr->spos.x = d->s[d->sorder[i]].x - d->p.x;
	spr->spos.y = d->s[d->sorder[i]].y - d->p.y;
	spr->invDet = 1.0 / (d->cam.x * d->dir.y - d->dir.x * d->cam.y);
	spr->trans.x = spr->invDet
		* (d->dir.y * spr->spos.x - d->dir.x * spr->spos.y);
	spr->trans.y = spr->invDet
		* (-d->cam.y * spr->spos.x + d->cam.x * spr->spos.y);
	spr->screenX = (int)((d->i.x / 2) * (1 + spr->trans.x / spr->trans.y));
	spr->res.y = abs((int)(d->i.y / spr->trans.y));
	spr->dstart.y = -(spr->res.y / 2) + d->i.y / 2;
	if (spr->dstart.y < 0)
		spr->dstart.y = 0;
	spr->dend.y = spr->res.y / 2 + d->i.y / 2;
	if (spr->dend.y >= d->i.y)
		spr->dend.y = d->i.y;
	spr->res.x = abs((int)(d->i.y / spr->trans.y));
	spr->dstart.x = -(spr->res.x / 2) + spr->screenX;
	if (spr->dstart.x < 0)
		spr->dstart.x = 0;
	spr->dend.x = spr->res.x / 2 + spr->screenX;
	if (spr->dend.x >= d->i.x)
		spr->dend.x = d->i.x;
}

void	get_sprites_dist_order(t_d *d)
{
	int		i;
	int		tmp;

	i = 0;
	while (i < d->snb)
	{
		d->sorder[i] = i;
		d->sdist[i] = (pow(d->p.x - d->s[i].x, 2) + pow(d->p.y - d->s[i].y, 2));
		i++;
	}
	if (d->snb <= 1)
		return ;
	i = 0;
	while (i < d->snb - 1)
	{
		if (d->sdist[d->sorder[i]] < d->sdist[d->sorder[i + 1]])
		{
			tmp = d->sorder[i];
			d->sorder[i] = d->sorder[i + 1];
			d->sorder[i + 1] = tmp;
			if (i > 0)
				i -= 2;
		}
		i++;
	}
}

void	pixel_put(t_img *i, int x, int y, int color)
{
	char	*dst;

	dst = i->addr + (y * i->len + x * (i->bpp / 8));
	*(unsigned int *)dst = color;
}

void	pixel_get(t_img *i, int x, int y, int *color)
{
	char	*dst;

	dst = i->addr + (y * i->len + x * (i->bpp / 8));
	*color = *(unsigned int *)dst;
}
