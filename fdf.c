/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarck <lmarck@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:32:19 by leo               #+#    #+#             */
/*   Updated: 2025/01/23 13:32:19 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// algo DDA placer les lignes
// gerer les Hook

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
int main(int argc, char **argv)
{
    t_map_data		map;
	t_mlx_params	mlx_params;

    if (argc != 2)
        return (0);
    map = table_to_struct(get_map(argv[1]));
	mlx_params = my_mlx_init();
	isometric_view(map, mlx_params);
	mlx_loop_hook(mlx_params.mlx,redraw, &mlx_params);
    mlx_loop(mlx_params.mlx);
    return (0);
}
void isometric_view(t_map_data map, t_mlx_params mlx_params)
{
	map.rx = -0.61548;
	map.ry = 0.785398;
	map.h_scale = 10;
	map = normalize_height(map);
	map = make_projection(map);
	display_projection (map, mlx_params);
}

t_mlx_params my_mlx_init(void)
{	
	t_mlx_params mlx_params;
	int win_width;
	int win_height;

	win_width = 1920;
	win_height = 1080;
	mlx_params.mlx = mlx_init();
    if (!mlx_params.mlx)
        exit(1);
    mlx_params.mlx_win = mlx_new_window(mlx_params.mlx, win_width, win_height, "Fil de fer");
    if (!mlx_params.mlx_win)
        exit(1);
    mlx_params.img.img = mlx_new_image(mlx_params.mlx, win_width, win_height);
    if (!mlx_params.img.img)
        exit(1);
    mlx_params.img.addr = mlx_get_data_addr(mlx_params.img.img,
                            &mlx_params.img.bits_per_pixel,
                            &mlx_params.img.line_length,
                            &mlx_params.img.endian);
    return (mlx_params);
}
/* void draw_seg(t_bi_d p1, t_bi_d p2, t_data *dt, float scl, t_bi_d mz)
{
	float dx;
	float dy;
	float x_inc;
	float y_inc;
	float x;
	float y;
	int i;

	dx = p2.xp - p1.xp;
	dy = p2.yp - p1.yp;
	p1.xr = big(ft_abs(dx), ft_abs(dy));
	x_inc = dx / (float)p1.xr;
    y_inc = dy / (float)p1.xr;
	x = p1.xp;
	y = p1.yp;
	i = 0;
	while (i <= p1.xr)
	{
		dx = 1920 / 2 + (int)((x - mz.xp) * scl); 
		dy = 1080 / 2 + (int)((y - mz.yp) * scl);
		my_mlx_pixel_put(dt, (int)dx, (int)dy, p1.color);
        x += x_inc;
        y += y_inc;
        i++;
	}
}
void connect_point(t_bi_d *map, t_data *data, float scale)
{
	int i;

	i = 1;
	while (i < map[0].x * map[0].y)
	{
		if(i % map[0].x)
			draw_seg(map[i], map [i+1], data, scale, map[0]);
		if(i < (map[0].y - 1) * map[0].x)
			draw_seg(map[i], map[i + map[0].x], data, scale, map[0]);
		i++;
	}
} */
int big(float dx, float dy)
{
	if(dx >= dy)
		return (dx);
	return (dy);
}
int redraw(void *param)
{
    t_mlx_params *mlxp = (t_mlx_params *)param;
    mlx_put_image_to_window(mlxp->mlx, mlxp->mlx_win, mlxp->img.img, 0, 0);
    return (0);
}

int z_max(t_tri_d *map, int xr, int yr)
{
	int z_max;
	int i;

	z_max = 1;
	i = 0;
	while(i < xr * yr)
	{
	if(z_max < ft_abs(map[i].z))
		z_max = ft_abs(map[i].z);
	i++;
	}
	if (z_max)
		return (z_max);
	else
		return (1);
}
int	ft_abs(int i)
{
	if (i < 0)
		i = -i;
	return (i);
}

t_map_data normalize_height(t_map_data map)
{
	float scale;
	float small_side;
	int i;

	map.z_max = z_max(map.cloud, map.xc_range, map.yc_range);
	if (map.xc_range < map.yc_range)
		small_side = map.xc_range;
	else	
		small_side = map.yc_range;
	scale = (small_side / (float)map.h_scale) / (float)map.z_max;;
	i = 0;
	while (i < map.xc_range * map.yc_range)
	{
		map.cloud[i].scl_z = (float)map.cloud[i].z * scale;
		i++;
	}
	return (map);
}
int display_projection(t_map_data map, t_mlx_params mlxp)
{
	int sx;
	int sy;
	int i;

	map.ds = get_d_scale(map);
	map = get_range(map, 0);
	map.offset_x = (1920 - (map.xp_v_range * map.ds)) / 2 - (map.xp_v_min * map.ds);
	map.offset_y = (1080 - (map.yp_v_range * map.ds)) / 2 - (map.yp_v_min * map.ds);
	i = 0;
	while(i < map.xc_range * map.yc_range)
	{
		sx = (int)(map.cloud[i].xp * map.ds + map.offset_x);
		sy = (int)(map.cloud[i].yp * map.ds + map.offset_y);
		if(sx >= 0 && sx < 1920 && sy >= 0 && sy < 1080)
			my_mlx_pixel_put(&mlxp.img, sx, sy, map.cloud[i].color);
		i++;
	}
	connect_point(map, mlxp);	//apply dda algorithme to connecte all the adjacent point (x+1, y+1)
	mlx_put_image_to_window(mlxp.mlx, mlxp.mlx_win, mlxp.img.img, 0 , 0);
	return(0);
}
void connect_point(t_map_data map, t_mlx_params mlxp)
{
	int i;

	i = 0;
	while(i < map.xc_range * map.yc_range)
	{
		if((i + 1) % map.xc_range)
			dda(map.cloud[i], map.cloud[i + 1], map, mlxp);
		if(i < map.xc_range * (map.yc_range - 1))
			dda(map.cloud[i], map.cloud[i + map.xc_range], map, mlxp);
		i++;
	}
	mlx_put_image_to_window(mlxp.mlx, mlxp.mlx_win, mlxp.img.img, 0 , 0);
	return ;
}

float get_maxf(float a, float b)
{
	if(a > b)
		return(a);
	return (b);
}

void dda(t_tri_d p1, t_tri_d p2, t_map_data map, t_mlx_params mlxp)
{
	float dx;
	float dy;
	float steps;
	float x_inc;
	float y_inc;
	float	x;
	float	y;
	int		i;

	dx = (p2.xp - p1.xp) * map.ds;
	dy = (p2.yp - p1.yp) * map.ds;
	steps = get_maxf(ft_abs(dx), ft_abs(dy));
	x_inc = dx / steps;
    y_inc = dy / steps;
	x = p1.xp * map.ds + map.offset_x;
    y = p1.yp * map.ds + map.offset_y;
    i = 0;
    while (i <= (int)steps)
    {
        if ((int)x >= 0 && (int)x < 1920 && (int)y >= 0 && (int)y < 1080)
    		my_mlx_pixel_put(&mlxp.img, (int)roundf(x), (int)roundf(y), p1.color);
        x = x + x_inc;
        y = y + y_inc;
        i++;
    }
}

t_map_data make_projection(t_map_data map)
{
	int i;

	i = 0;
	while (i < map.xc_range * map.yc_range)
	{
		map.cloud[i] = rotate_point(map.cloud[i], map.rx, map.ry);
		i++;
	}
	return (map);
}
t_tri_d rotate_point(t_tri_d pt, float ry, float rx)
{
	float	tmp_z;

	pt.xp = pt.x * cos(ry) + pt.scl_z * sin(ry);
	tmp_z = -pt.x * sin(ry) + pt.scl_z * cos(ry);
	pt.yp = (pt.y * cos(rx) - tmp_z * sin(rx));
	return(pt);
}

float get_d_scale(t_map_data map)
{
	float	scale_x;
	float	scale_y;

	map = get_range(map, 0);

	scale_x = 960.0f / map.xp_v_range;
	scale_y = 540.0f / map.yp_v_range;
	if(scale_x < scale_y)
		return (scale_x);
	else
		return(scale_y);
}
t_map_data get_range(t_map_data map, int i)
{
	int xpmin;
	int xpmax;
	int ypmin;
	int ypmax;
	
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
	return(map);
}
int get_min(int a, int b)
{
	if (a > b)
		return (b);
	else
		return (a);
}
int get_max(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}


t_map_data table_to_struct(t_pix **map) //ok non verif
{
	t_map_data s_map;
	int x;
	int y;
	int i;

	s_map.cloud = malloc(((map[0][0]).z * (map[0][1]).z + 1) * sizeof(t_tri_d));
	if(!s_map.cloud)
		exit_fdf(map);
	s_map.xc_range = map[0][1].z;
	s_map.yc_range = map[0][0].z;
	i = 0;
	x = 0;
	y = 1;
	while (y <= (map[0][0]).z)
	{
		while(x < (map[0][1]).z)
		{
			s_map.cloud[i] = transfer_data(map[y][x], x, y);
			i++;
			x++;
		}
		x = 0;
		y++;
	}
	return(free_map(map, (map[0][0]).z), free(map),s_map);
}

t_tri_d	transfer_data(t_pix point, int x, int y) //ok a verif
{
	t_tri_d sp;

	sp.x = x;
	sp.y = y;
	sp.z = point.z;
	sp.color = point.color;
	return (sp);
}

void *my_new_window(void *mlx) 
{
	int win_width;
	int win_height;
	void *mlx_win;

	win_width = 1920;
	win_height = 1080;
	mlx_win = mlx_new_window(mlx, win_width, win_height, "Fil de fer");
	return(mlx_win);
}

void	free_map(t_pix **map, int y) // a modifier
{
	while (y >= 0)
	{
		free(map[y]);
		y--;
	}
}

