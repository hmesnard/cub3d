/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmesnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 16:27:33 by hmesnard          #+#    #+#             */
/*   Updated: 2021/04/21 21:14:35 by hmesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	win_close(t_d *d)
{
	free_structs(0, NULL, d);
	exit(0);
}

int	key_press(int keycode, t_d *d)
{
	if (keycode == 13)
		d->key.up = 1;
	else if (keycode == 0)
		d->key.left = 1;
	else if (keycode == 1)
		d->key.down = 1;
	else if (keycode == 2)
		d->key.right = 1;
	else if (keycode == 123)
		d->key.lleft = 1;
	else if (keycode == 124)
		d->key.lright = 1;
	else if (keycode == 53)
		win_close(d);
	return (0);
}

int	key_release(int keycode, t_d *d)
{
	if (keycode == 13)
		d->key.up = 0;
	else if (keycode == 0)
		d->key.left = 0;
	else if (keycode == 1)
		d->key.down = 0;
	else if (keycode == 2)
		d->key.right = 0;
	else if (keycode == 123)
		d->key.lleft = 0;
	else if (keycode == 124)
		d->key.lright = 0;
	return (0);
}

int	loop_function(t_d *d)
{
	if (((d->key.up || d->key.down) && !(d->key.up && d->key.down))
		|| ((d->key.left || d->key.right) && !(d->key.left && d->key.right)))
		move(d);
	if ((d->key.lleft || d->key.lright) && !(d->key.lleft && d->key.lright))
		turn(d);
	get_new_frame(d);
	mlx_put_image_to_window(d->mlx, d->win, d->i.img, 0, 0);
	return (0);
}

void	hooks(t_d *d)
{
	mlx_do_key_autorepeatoff(d->mlx);
	mlx_hook(d->win, 17, 1L << 17, &win_close, d);
	mlx_hook(d->win, 2, 1L << 0, &key_press, d);
	mlx_hook(d->win, 3, 1L << 1, &key_release, d);
	mlx_loop_hook(d->mlx, &loop_function, d);
}
