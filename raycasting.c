/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmesnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 13:26:41 by hmesnard          #+#    #+#             */
/*   Updated: 2021/04/21 16:46:06 by hmesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ver_line(t_d *d, t_rc *rc, int x)
{
	int	y;

	y = 0;
	rc->pstep = 1.0 * d->t[rc->texnum].y / rc->height;
	rc->texPos = (rc->dstart - d->i.y / 2 + rc->height / 2) * rc->pstep;
	while (y < d->i.y)
	{
		if (rc->dstart <= y && y < rc->dend)
		{
			rc->tex.y = (int)rc->texPos;
			rc->texPos += rc->pstep;
			pixel_get(&d->t[rc->texnum], rc->tex.x, rc->tex.y, &rc->color);
			pixel_put(&d->i, x, y, rc->color);
		}
		else if (rc->dstart > y)
			pixel_put(&d->i, x, y, d->ccl);
		else
			pixel_put(&d->i, x, y, d->fcl);
		y++;
	}
}

void	set_draw_vars(t_d *d, t_rc *rc)
{
	rc->height = (int)(d->i.y / rc->perp);
	rc->dstart = -rc->height / 2 + d->i.y / 2;
	if (rc->dstart < 0)
		rc->dstart = 0;
	rc->dend = rc->height / 2 + d->i.y / 2;
	if (rc->dend >= d->i.y)
		rc->dend = d->i.y;
	if (rc->hrz && rc->step.y == -1)
		rc->texnum = 1;
	if (rc->hrz && rc->step.y == 1)
		rc->texnum = 0;
	if (!rc->hrz && rc->step.x == 1)
		rc->texnum = 2;
	if (!rc->hrz && rc->step.x == -1)
		rc->texnum = 3;
	if (rc->hrz)
		rc->wallX = d->p.x + rc->perp * rc->ray.x;
	else
		rc->wallX = d->p.y + rc->perp * rc->ray.y;
	rc->wallX -= floor(rc->wallX);
	rc->tex.x = (int)(rc->wallX * (double)d->t[rc->texnum].x);
	if ((!rc->hrz && rc->ray.x < 0) || (rc->hrz && rc->ray.y > 0))
		rc->tex.x = d->t[rc->texnum].x - rc->tex.x - 1;
}

void	do_dda(t_d *d, t_rc *rc)
{
	while (1)
	{
		if (rc->side.x < rc->side.y)
		{
			rc->side.x += rc->dlt.x;
			rc->map.x += rc->step.x;
			rc->hrz = 0;
		}
		else
		{
			rc->side.y += rc->dlt.y;
			rc->map.y += rc->step.y;
			rc->hrz = 1;
		}
		if (d->map[rc->map.y][rc->map.x] == '1')
			break ;
	}
	if (rc->hrz)
		rc->perp = (rc->map.y - d->p.y + (1 - rc->step.y) / 2) / rc->ray.y;
	else
		rc->perp = (rc->map.x - d->p.x + (1 - rc->step.x) / 2) / rc->ray.x;
}

void	set_raycasting_vars(t_d *d, t_rc *rc, int x)
{
	rc->ray.x = d->dir.x + d->cam.x * (2 * x / (double)(d->i.x - 1) - 1);
	rc->ray.y = d->dir.y + d->cam.y * (2 * x / (double)(d->i.x - 1) - 1);
	rc->map.x = (int)d->p.x;
	rc->map.y = (int)d->p.y;
	rc->dlt.x = fabs(1 / rc->ray.x);
	rc->dlt.y = fabs(1 / rc->ray.y);
	rc->step.x = -1 + (rc->ray.x >= 0) * 2;
	rc->step.y = -1 + (rc->ray.y >= 0) * 2;
	if (rc->ray.x < 0)
		rc->side.x = (d->p.x - rc->map.x) * rc->dlt.x;
	else
		rc->side.x = (rc->map.x + 1.0 - d->p.x) * rc->dlt.x;
	if (rc->ray.y < 0)
		rc->side.y = (d->p.y - rc->map.y) * rc->dlt.y;
	else
		rc->side.y = (rc->map.y + 1.0 - d->p.y) * rc->dlt.y;
}

void	get_new_frame(t_d *d)
{
	int		i;
	t_rc	rc;
	t_spr	spr;

	i = 0;
	while (i < d->i.x)
	{
		set_raycasting_vars(d, &rc, i);
		do_dda(d, &rc);
		set_draw_vars(d, &rc);
		draw_ver_line(d, &rc, i);
		d->zbuffer[i] = rc.perp;
		i++;
	}
	get_sprites_dist_order(d);
	i = 0;
	while (i < d->snb)
	{
		set_sprite_vars(d, &spr, i);
		draw_sprite(d, &spr, spr.dstart.x, 0);
		i++;
	}
}
