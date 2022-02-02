/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmesnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 17:27:24 by hmesnard          #+#    #+#             */
/*   Updated: 2021/04/22 11:57:29 by hmesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

# include "mlx.h"

# include <math.h>

typedef struct s_gnl
{
	int			fd;
	char		*line;
	int			ret;
}				t_gnl;

typedef struct s_ipos
{
	int		x;
	int		y;
}				t_ipos;

typedef struct s_dpos
{
	double		x;
	double		y;
}				t_dpos;

typedef struct s_cub
{
	t_ipos		r;
	char		rbool;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*s;
	int			fcl;
	int			ccl;
	char		**map;
}				t_cub;

typedef struct s_rc
{
	t_dpos		ray;
	t_ipos		map;
	t_dpos		side;
	t_dpos		dlt;
	t_ipos		step;
	int			hrz;
	double		perp;
	int			height;
	int			dstart;
	int			dend;
	int			color;
	int			texnum;
	double		wallX;
	t_ipos		tex;
	double		pstep;
	double		texPos;
}				t_rc;

typedef struct s_spr
{
	t_dpos		spos;
	double		invDet;
	t_dpos		trans;
	int			screenX;
	t_ipos		res;
	t_ipos		dstart;
	t_ipos		dend;
	t_ipos		tex;
	int			d;
	int			color;
}				t_spr;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			len;
	int			e;
	int			x;
	int			y;
}				t_img;

typedef struct s_key
{
	char		up;
	char		down;
	char		left;
	char		right;
	char		lleft;
	char		lright;
	char		mouseleft;
	char		mouseright;
}				t_key;

typedef struct s_d
{
	int			fcl;
	int			ccl;
	char		**map;
	void		*mlx;
	void		*win;
	t_img		i;
	int			screenx;
	int			screeny;
	t_img		t[5];
	t_key		key;
	t_dpos		p;
	t_dpos		dir;
	t_dpos		cam;
	int			snb;
	double		*zbuffer;
	int			*sorder;
	double		*sdist;
	t_dpos		*s;
	int			life;
}				t_d;

//main.c

int		ft_isspace(int c);

//get_cub.c

int		get_cub(char **av, t_cub *cub);

//get_cub_valid_line.c

int		valid_line(char *line);
int		valid_id(char *line);

//get_cub_value.c

int		get_cub_value(t_cub *cub, char *line);

//get_cub_utils.c

int		is_id(char *line, char *id);
int		line_isspace(char *line);
void	skip_spaces(char *line, size_t *i);
int		overflow_colors(char *line);
int		overflow(char *line, size_t max);

//split_map.c

int		split_map(char *str, char ***map);

//valid_map.c

int		valid_map(char **map);

//init_data.c

int		init_data(t_d *d, t_cub *cub);

//hooks.c

void	hooks(t_d *d);

//move_turn.c

void	move(t_d *d);
void	turn(t_d *d);

//raycasting.c

void	get_new_frame(t_d *d);

//raycasting_sprites.c

void	get_sprites_dist_order(t_d *d);
void	set_sprite_vars(t_d *d, t_spr *spr, int i);
void	draw_sprite(t_d *d, t_spr *spr, int stripe, int y);
void	pixel_put(t_img *i, int x, int y, int color);
void	pixel_get(t_img *i, int x, int y, int *color);

//make_bmp.c

int		make_bmp(t_d d);

//error_free.c

int		error(char *str, void *to_free1, void *to_free2);
int		free_structs(int ret, t_cub *cub, t_d *d);

//utils.c

int		ft_strcmp(const char *s1, const char *s2);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_atoi(const char *nptr);
char	*ft_strdup(const char *s);

//bonus.c

int		shadow(int color, double prop);

#endif
