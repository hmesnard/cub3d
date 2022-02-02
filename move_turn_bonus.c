/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_turn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmesnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 13:30:19 by hmesnard          #+#    #+#             */
/*   Updated: 2021/04/21 20:47:29 by hmesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_dpos	rot(t_dpos v, double angle)
{
	t_dpos	temp;

	temp = v;
	v.x = (cos(angle) * temp.x) + (sin(angle) * temp.y);
	v.y = (-sin(angle) * temp.x) + (cos(angle) * temp.y);
	return (v);
}

void	move(t_d *d)
{
	t_dpos	temp;
	t_dpos	tdir;

	if (d->key.up)
		tdir = rot(d->dir, (d->key.left - d->key.right) * M_PI_4);
	else if (d->key.down)
		tdir = rot(d->dir, (d->key.right - d->key.left) * M_PI_4 + M_PI);
	else
		tdir = rot(d->dir, (d->key.left - d->key.right) * M_PI_2);
	temp.x = d->p.x + tdir.x * 0.2;
	temp.y = d->p.y + tdir.y * 0.2;
	if (d->map[(int)temp.y][(int)d->p.x] == '0')
		d->p.y = temp.y;
	else
	{
		system("afplay sounds/aie.m4a &>/dev/null &");
		d->life--;
	}
	if (d->map[(int)d->p.y][(int)temp.x] == '0')
		d->p.x = temp.x;
	else
	{
		system("afplay sounds/aie.m4a &>/dev/null &");
		d->life--;
	}
}

void	turn(t_d *d)
{
	if (d->key.lleft || d->key.mouseleft)
	{
		d->dir = rot(d->dir, M_PI / 50);
		d->cam = rot(d->cam, M_PI / 50);
	}
	else
	{
		d->dir = rot(d->dir, -M_PI / 50);
		d->cam = rot(d->cam, -M_PI / 50);
	}
}
