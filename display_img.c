/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_img.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarck <lmarck@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:34:58 by lmarck            #+#    #+#             */
/*   Updated: 2025/02/12 15:47:48 by lmarck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	display_projection(t_map_data map, t_mlx_params mlxp)
{
	int	sx;
	int	sy;
	int	i;

	map.ds = get_d_scale(map);
	map = get_range(map, 0);
	map.offset_x = (1920 - (map.xp_v_range * map.ds))
		/ 2 - (map.xp_v_min * map.ds);
	map.offset_y = (1080 - (map.yp_v_range * map.ds))
		/ 2 - (map.yp_v_min * map.ds);
	i = 0;
	while (i < map.xc_range * map.yc_range)
	{
		sx = (int)(map.cloud[i].xp * map.ds * mlxp.zoom
				+ map.offset_x + mlxp.tx);
		sy = (int)(map.cloud[i].yp * map.ds * mlxp.zoom
				+ map.offset_y + mlxp.ty);
		if (sx >= 0 && sx < 1920 && sy >= 0 && sy < 1080)
			my_mlx_pixel_put(&mlxp.img, sx, sy, map.cloud[i].color);
		i++;
	}
	connect_point(map, mlxp);
	return (0);
}

float	get_d_scale(t_map_data map)
{
	float	scale_x;
	float	scale_y;

	map = get_range(map, 0);
	scale_x = 960.0f / map.xp_v_range;
	scale_y = 540.0f / map.yp_v_range;
	if (scale_x < scale_y)
		return (scale_x);
	else
		return (scale_y);
}

t_map_data	get_range(t_map_data map, int i)
{
	int	xpmin;
	int	xpmax;
	int	ypmin;
	int	ypmax;

	xpmin = map.cloud[0].xp;
	xpmax = map.cloud[0].xp;
	ypmin = map.cloud[0].yp;
	ypmax = map.cloud[0].yp;
	while (i < map.xc_range * map.yc_range)
	{
		xpmin = get_min(map.cloud[i].xp, xpmin);
		ypmin = get_min(map.cloud[i].yp, ypmin);
		xpmax = get_max(map.cloud[i].xp, xpmax);
		ypmax = get_max(map.cloud[i].yp, ypmax);
		i++;
	}
	map.xp_v_min = xpmin;
	map.xp_v_max = xpmax;
	map.yp_v_min = ypmin;
	map.yp_v_max = ypmax;
	map.xp_v_range = (xpmax - xpmin);
	map.yp_v_range = (ypmax - ypmin);
	return (map);
}

t_map_data	make_projection(t_map_data map)
{
	int	i;

	i = 0;
	while (i < map.xc_range * map.yc_range)
	{
		map.cloud[i] = rotate_point(map.cloud[i], map.rx, map.ry, map.rz);
		i++;
	}
	return (map);
}

t_tri_d	rotate_point(t_tri_d pt, float rx, float ry, float rz)
{
	t_trif	p;
	float	tmpx;
	float	tmpy;
	float	tmpz;

	p.x = pt.x;
	p.y = pt.y;
	p.z = pt.scl_z;
	tmpy = p.y * cosf(rx) - p.z * sinf(rx);
	tmpz = p.y * sinf(rx) + p.z * cosf(rx);
	tmpx = p.x * cosf(ry) + tmpz * sinf(ry);
	tmpz = -p.x * sinf(ry) + tmpz * cosf(ry);
	p.x = tmpx * cosf(rz) - tmpy * sinf(rz);
	p.y = tmpx * sinf(rz) + tmpy * cosf(rz);
	pt.xp = p.x;
	pt.yp = p.y;
	return (pt);
}
