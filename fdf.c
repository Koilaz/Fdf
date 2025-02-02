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

 int	main(int argc, char **argv)
{
	t_bi_d	*map;
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	float		rx;
	float		ry;

	ry = -0.523599f;
	rx = 0.523599f;
	if (argc != 2)
		return (0);
	map = map_iso(table_to_struct(get_map(argv[1])), rx, ry); //ordre des lignes est inverse  y max[0][0] xmax [0][1]
	mlx = mlx_init();
	mlx_win = my_new_window(mlx);
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	//top_view(map, mlx_win, img, mlx);
	put_iso_point(map, mlx_win, img, mlx);
	mlx_loop(mlx);
	while(1)
		pause();
	return (free(map), 0);
}
void put_iso_point(t_bi_d *map, void *mlx_win, t_data img, void *mlx)
{
	int i;
	float scale;
	int draw_x;
	int draw_y;

	scale = m_scale(map[0].y, map[0].x);
	i = 1;
	while(i <= map[0].x * map[0].y)// <= ?
	{
		//printf("xp;%f  yp:%f x:%d  y:%d z:%d\n", map[i].xp, map[i].yp, map[i].x, map[i].y, map[i].z);
		draw_x = (1920 / 2) + (int)(map[i].xp * scale);
		draw_y = (1080 / 2) + (int)(map[i].yp * scale);
		if (draw_x >= 0 && draw_x < 1920 && draw_y >= 0 && draw_y < 1080)
			my_mlx_pixel_put(&img, draw_x, draw_y, map[i].color);
		i++;
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
}
int z_max(t_bi_d *map)
{
	int z_max;
	int i;

	z_max = 1;
	i = 1;
	while(i < map[0].x * map[0].y)
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

t_bi_d *map_iso(t_tri_d *mapt, float rx, float ry)
{
	int i;
	t_bi_d *mapb;

	mapb = malloc((mapt[0].x * mapt[0].y + 1) * sizeof(t_bi_d));
	if(!mapb)
		return(NULL);
	i = 1;
	mapb[0].x = mapt[0].x;
	mapb[0].y = mapt[0].y;
	printf("width:%d  height:%d", mapt[0].y, mapt[0].x);
	while (i <= mapt[0].x * mapt[0].y)
	{
		mapb[i].x = mapt[i].x;
		mapb[i].y = mapt[i].y;
		mapb[i].z = mapt[i].z;
		mapb[i].color = mapt[i].color;
		i++;
	}
	mapb[0].z = z_max(mapb);
	mapb = apply_rotation(mapb, rx, ry);
	return (free(mapt), mapb);
}
t_bi_d *apply_rotation(t_bi_d *map, float rx, float ry)
{
	int i;
	t_bi_d rt;
	float z_scale;

	z_scale = 1 / (float)map[0].z * (map[0].x / 10.0f);
	i = 1;
	while (i <= map[0].x * map[0].y)
	{
		rt = rota(map[i], ry, rx, z_scale);
		map[i].xp = rt.xp;
		map[i].yp = rt.yp;
		i++;
	}
	return (map);
}

float m_scale(int y, int x)
{
	float	scale_x;
	float	scale_y;

	scale_x = 960 / (float)x;
	scale_y = 540 / (float)y;
	if(scale_x < scale_y)
		return (scale_x);
	else
		return(scale_y);

}
t_bi_d rota(t_bi_d p, float ry, float rx, float z_scale)
{
	t_bi_d	rp;
	float tz;
	float scaled_z;

	scaled_z = p.z * z_scale;
	rp.xp = p.x * cos(ry) + scaled_z * sin(ry);
	tz = -p.x * sin(ry) + scaled_z * cos(ry);
	rp.yp = (p.y * cos(rx) - tz * sin(rx));
	return(rp);
}
/* float rot_y(t_tri_d p, float rx, float ry)
{
	float y;

	y = p.y * cos(rx) + p.x * sin(ry) * sin(rx) - ((float)p.z / 10)*cos(ry) * sin(rx);
	return(y);
} */

t_tri_d *table_to_struct(t_pix **map)
{
	t_tri_d *point;
	int x;
	int y;
	int i;

	point = malloc(((map[0][0]).z * (map[0][1]).z + 1) * sizeof(t_tri_d));
	if(!point)
		exit_fdf(map); //malloc a securise
	point[0] = put_dimension((map[0][1]).z, (map [0][0]).z);
	i = 1;
	x = 0;
	y = 1;
	while (y <= (map[0][0]).z)
	{
		while(x < (map[0][1]).z)
		{
			point[i].x = x;
			point[i].y = y;
			point[i].z = map[y][x].z;
			point[i].color = map[y][x].color;
			i++;
			x++;
		}
		x = 0;
		y++;
	}
	return(free_map(map, (map[0][0]).z), free(map),point);
}
t_tri_d put_dimension(int x_range, int y_range)
{
	t_tri_d zero;

	zero.x = x_range;
	zero.y = y_range;
	return(zero);
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
void top_view(t_pix **map, void *mlx_win, t_data img, void *mlx)
{
	int scale;
	int y;
	int x;
	int draw_x;
	int draw_y;

	scale = map_scale(map);
	x = 0;
	y = 1;
	while (y <= (map[0][0]).z)
	{
		while(x < (map[0][1]).z)
		{
			draw_x = ((1920 - (int)((map[0][1]).z * scale)) / 2) + (int)(x * scale);
			draw_y = ((1080 - (int)((map[0][0]).z * scale)) / 2) + (int)(y * scale);
			my_mlx_pixel_put(&img, draw_x, draw_y, map[y][x].color);
			x++;
		}
		x = 0;
		y++;
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
}

float map_scale(t_pix **map)
{
	float	scale_x;
	float	scale_y;

	scale_x = ((float)1920 / 2) / (float)(map[0][0]).z;
	scale_y = ((float)1080 / 2) / (float)(map[0][1]).z;
	if(scale_x < scale_y)
		return (scale_x);
	else
		return(scale_y);
}

void	free_map(t_pix **map, int y)
{
	while (y >= 0)
	{
		free(map[y]);
		y--;
	}
}

/* int	main(int argc, char **argv)
{
	int	**map;

	if (argc != 2)
		return (0);
	map = get_map(argv[1]);
	int y = 1;
	int x = 0;
	printf("y = %d \n", map[0][0]);
	printf("x = %d \n", map[0][1]);
	while (y <= map[0][0])
	{
        while(x <= map [0][1])
        {
		printf("%d ", map[y][x]);
        x++;
        }
        x = 0;
        printf("\n");
        y--;
	}
	free_map(map, map[0][0]);
	free(map);
	return (0);
} */
