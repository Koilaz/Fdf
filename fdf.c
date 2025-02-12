/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarck <lmarck@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:24:06 by lmarck            #+#    #+#             */
/*   Updated: 2025/02/10 20:30:25 by lmarck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_map_data		map;
	t_mlx_params	mlx_params;

	if (argc != 2)
		return (0);
	map = table_to_struct(get_map(argv[1]));
	mlx_params = my_mlx_init();
	mlx_params.map = isometric_view(map, mlx_params);
	mlx_hook(mlx_params.mlx_win, 2, 1L << 0, key_press_hook, &mlx_params);
	mlx_hook(mlx_params.mlx_win, 17, 0, close_window, &mlx_params);
	mlx_hook(mlx_params.mlx_win, 4, 1L << 2, mouse_press_hook, &mlx_params);
	mlx_loop_hook(mlx_params.mlx, redraw, &mlx_params);
	mlx_loop(mlx_params.mlx);
	return (0);
}

int	redraw(void *param)
{
	t_mlx_params	*p;
	t_map_data		tmp;

	p = (t_mlx_params *)param;
	clear_image(&p->img, 1920, 1080);
	mlx_clear_window(p->mlx, p->mlx_win);
	tmp = normalize_height(p->map);
	tmp = make_projection(tmp);
	display_projection(tmp, *p);
	mlx_put_image_to_window(p->mlx, p->mlx_win, p->img.img, 0, 0);
	return (0);
}

t_map_data	isometric_view(t_map_data map, t_mlx_params mlx_params)
{
	map.rx = 0.61548;
	map.ry = -0.785398;
	map.rz = 0.5;
	map.h_scale = 10;
	map = normalize_height(map);
	map = make_projection(map);
	display_projection (map, mlx_params);
	return (map);
}

void	connect_point(t_map_data map, t_mlx_params mlxp)
{
	int	i;

	i = 0;
	while (i < map.xc_range * map.yc_range)
	{
		if ((i + 1) % map.xc_range)
			dda(map.cloud[i], map.cloud[i + 1], map, mlxp);
		if (i < map.xc_range * (map.yc_range - 1))
			dda(map.cloud[i], map.cloud[i + map.xc_range], map, mlxp);
		i++;
	}
	return ;
}

void	dda(t_tri_d p1, t_tri_d p2, t_map_data map, t_mlx_params mlxp)
{
	t_trif	d;
	t_trif	e;
	float	st;
	int		i;

	d.x = (p2.xp - p1.xp) * map.ds * mlxp.zoom;
	d.y = (p2.yp - p1.yp) * map.ds * mlxp.zoom;
	st = get_maxf(ft_abs(d.x), ft_abs(d.y));
	d.z = d.x / st;
	e.x = d.y / st;
	e.y = roundf(p1.xp * map.ds * mlxp.zoom + map.offset_x + mlxp.tx);
	e.z = roundf(p1.yp * map.ds * mlxp.zoom + map.offset_y + mlxp.ty);
	i = 0;
	while (i <= (int)st)
	{
		if ((int)e.y >= 0 && (int)e.y < 1920
			&& (int)e.z >= 0 && (int)e.z < 1080)
			my_mlx_pixel_put(&mlxp.img, (int)e.y, (int)e.z,
				col_grad(p1, p2, st, i));
		e.y = e.y + d.z;
		e.z = e.z + e.x;
		i++;
	}
}
