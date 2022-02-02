/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmesnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 15:41:50 by hmesnard          #+#    #+#             */
/*   Updated: 2021/04/22 12:58:52 by hmesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	make_header(t_d d, int fd)
{
	int	tmp;

	write(fd, "BM", 2);
	tmp = 14 + 40 + 4 * d.i.x * d.i.y;
	write(fd, &tmp, 4);
	tmp = 0;
	write(fd, &tmp, 2);
	write(fd, &tmp, 2);
	tmp = 54;
	write(fd, &tmp, 4);
	tmp = 40;
	write(fd, &tmp, 4);
	write(fd, &d.i.x, 4);
	write(fd, &d.i.y, 4);
	tmp = 1;
	write(fd, &tmp, 2);
	write(fd, &d.i.bpp, 2);
	tmp = 0;
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
}

int	make_bmp(t_d d)
{
	int		fd;
	t_ipos	p;

	fd = open("cub3d_screenshot.bmp", O_CREAT | O_RDWR);
	if (fd < 0)
		;
	make_header(d, fd);
	p.y = d.i.y;
	while (p.y > 0)
	{
		p.y--;
		p.x = 0;
		while (p.x < d.i.x)
		{
			write(fd, d.i.addr + (p.y * d.i.len + p.x * (d.i.bpp / 8)), 4);
			p.x++;
		}
	}
	close(fd);
	return (1);
}
