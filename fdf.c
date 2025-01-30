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

//parsing incluant les couleurs
//projections isometrique
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
	int		**map;
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	if (argc != 2)
		return (0);
	map = get_map(argv[1]); //ordre des lignes est inverse  y max[0][0] xmax [0][1]
	mlx = mlx_init();
	mlx_win = my_new_window(mlx);
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	top_view(map, mlx_win, img, mlx);
	mlx_loop(mlx);
	while(1)
		pause();
	return (free_map(map, map[0][0]), free(map), 0);
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
void top_view(int **map, void *mlx_win, t_data img, void *mlx)
{
	int scale;
	int z_range;
	int y;
	int x;
	int draw_x;
	int draw_y;

	scale = map_scale(map);
	x = 0;
	y = 1;
	z_range = height_range(map);
	while (y <= map[0][0])
	{
		while(x < map[0][1])
		{
			if(map[y][x])
			{
				draw_x = ((1920 - (int)(map[0][1] * scale)) / 2) + (int)(x * scale);
				draw_y = ((1080 - (int)(map[0][0] * scale)) / 2) + (int)(y * scale);
				my_mlx_pixel_put(&img, draw_x, draw_y, 16777215);
			}
			x++;
		}
		x = 0;
		y++;
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
}
int height_color (int z)
{

}
float map_scale(int **map)
{
	float	scale_x;
	float	scale_y;

	scale_x = ((float)1920 / 2) / (float)map[0][0];
	scale_y = ((float)1080 / 2) / (float)map[0][1];
	if(scale_x < scale_y)
		return (scale_x);
	else
		return(scale_y);
}

void	free_map(int **map, int y)
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
