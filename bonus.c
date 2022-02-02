/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmesnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 13:35:17 by hmesnard          #+#    #+#             */
/*   Updated: 2021/04/22 10:25:44 by hmesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_dpos	rot(t_dpos v, double angle);

int	shadow(int color, double prop)
{
	if (prop < 0)
		prop = 0;
	else if (prop > 1)
		prop = 1;
	return (((int)(((color & 0x00FF0000) >> 16) * prop) << 16)
			| ((int)(((color & 0x0000FF00) >> 8) * prop) << 8)
			| (int)((color & 0x000000FF) * prop));
}

int	mouse_motion(int x, int y, t_d *d)
{
	if (x > (2 * d->i.x / 3) && x < d->i.x && y > 0 && y < d->i.y)
	{
		d->key.mouseleft = 0;
		d->key.mouseright = 1;
	}
	else if (x > 0 && x < (d->i.x / 3) && y > 0 && y < d->i.y)
	{
		d->key.mouseleft = 1;
		d->key.mouseright = 0;
	}
	else
	{
		d->key.mouseleft = 0;
		d->key.mouseright = 0;
	}
	return (1);
}

void	draw_lifebar(t_d *d)
{
	int	y;
	int	x;

	y = 0;
	while (y < d->i.y / 40)
	{
		x = 0;
		while (x < (int)((d->life / 50.0) * d->i.x))
			pixel_put(&d->i, x++, y, 0x00FF0000);
		y++;
	}
}
