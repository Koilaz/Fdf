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

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

 int	main(int argc, char **argv)
{
	int	**map;
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	int y;
	int x = 0;

	if (argc != 2)
		return (0);
	map = get_map(argv[1]); //ordre des lignes est inverse  y max[0][0] xmax [0][1]
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080 * 4, "Window 1");
	img.img = mlx_new_image(mlx, map[0][1] * 4, map[0][0] * 4);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	y = map[0][0];

	while (y)
	{
		while(x < map[0][1])
		{
			if(map[y][x])
			my_mlx_pixel_put(&img, x * 2, y * 2, 16777215);
			x++;
		}
		x = 0;
		y--;
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	while(1)
		pause();

	return (free_map(map, map[0][0]), free(map), 0);
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
	int y = map[0][0];
	int x = 0;
	printf("y = %d \n", map[0][0]);
	printf("x = %d \n", map[0][1]);
	while (y > 0)
	{
        while(x < map [0][1])
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
