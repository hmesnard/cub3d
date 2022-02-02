/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmesnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 17:26:06 by hmesnard          #+#    #+#             */
/*   Updated: 2021/04/21 21:18:00 by hmesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"

int	ft_isspace(int c)
{
	if ((9 <= c && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	check_args_errors(int ac, char **av)
{
	if (ac < 2)
		return (error("No file given", NULL, NULL));
	else if (ac > 3)
		return (error("Too many arguments", NULL, NULL));
	else if (ac == 3 && ft_strcmp(av[2], "--save"))
		return (error("Second argument is not \"--save\"", NULL, NULL));
	else if (ft_strlen(av[1]) < 4
		|| ft_strcmp(av[1] + ft_strlen(av[1]) - 4, ".cub"))
		return (error("Invalid file name", NULL, NULL));
	return (1);
}

int	main(int ac, char **av)
{
	t_d		d;
	t_cub	cub;

	if (!check_args_errors(ac, av))
		return (0);
	if (!get_cub(av, &cub))
		return (free_structs(0, &cub, NULL));
	if (!init_data(&d, &cub))
		return (free_structs(0, &cub, &d));
	hooks(&d);
	if (ac == 3)
	{
		get_new_frame(&d);
		make_bmp(d);
		free_structs(0, NULL, &d);
	}
	else
	{
		system("afplay sounds/mymusic.mp4 &>/dev/null &");
		mlx_loop(d.mlx);
	}
	return (0);
}
