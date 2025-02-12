/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarck <lmarck@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:27:11 by lmarck            #+#    #+#             */
/*   Updated: 2025/02/10 20:11:48 by lmarck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map_data	table_to_struct(t_pix **map)
{
	t_map_data	s_map;
	int			x;
	int			y;
	int			i;

	s_map.cloud = malloc(((map[0][0]).z * (map[0][1]).z + 1) * sizeof(t_tri_d));
	if (!s_map.cloud)
		exit_fdf1(map);
	s_map.xc_range = map[0][1].z;
	s_map.yc_range = map[0][0].z;
	i = 0;
	x = 0;
	y = 1;
	while (y <= (map[0][0]).z)
	{
		while (x < (map[0][1]).z)
		{
			s_map.cloud[i] = transfer_data(map[y][x], x, y);
			i++;
			x++;
		}
		x = 0;
		y++;
	}
	return (free_map(map, (map[0][0]).z), free(map), s_map);
}

t_tri_d	transfer_data(t_pix point, int x, int y)
{
	t_tri_d	sp;

	sp.x = x;
	sp.y = y;
	sp.z = point.z;
	sp.color = point.color;
	return (sp);
}

t_map_data	normalize_height(t_map_data map)
{
	float	scale;
	float	small_side;
	int		i;

	map.z_max = z_max(map.cloud, map.xc_range, map.yc_range);
	if (map.xc_range < map.yc_range)
		small_side = map.xc_range;
	else
		small_side = map.yc_range;
	scale = (small_side / (float)map.h_scale) / (float)map.z_max;
	i = 0;
	while (i < map.xc_range * map.yc_range)
	{
		map.cloud[i].scl_z = (float)map.cloud[i].z * scale;
		i++;
	}
	return (map);
}

int	z_max(t_tri_d *map, int xr, int yr)
{
	int	z_max;
	int	i;

	z_max = 1;
	i = 0;
	while (i < xr * yr)
	{
		if (z_max < ft_abs(map[i].z))
			z_max = ft_abs(map[i].z);
		i++;
	}
	if (z_max)
		return (z_max);
	else
		return (1);
}

t_pix	**rev_map_line(t_pix **map)
{
	int		i;
	int		y;
	t_pix	*line;

	i = 1;
	y = (map[0][0]).z;
	while (i < y)
	{
		line = map[i];
		map[i] = map[y];
		map[y] = line;
		y--;
		i++;
	}
	return (map);
}
