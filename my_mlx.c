/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarck <lmarck@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:21:05 by lmarck            #+#    #+#             */
/*   Updated: 2025/02/10 21:14:57 by lmarck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	clear_image(t_data *img, int width, int height)
{
	int		y;
	int		x;
	char	*dst;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			dst = img->addr
				+ (y * img->line_length + x * (img->bits_per_pixel / 8));
			*(unsigned int *)dst = 0x000000;
			x++;
		}
		y++;
	}
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	close_window(void *param)
{
	t_mlx_params	*p;

	p = (t_mlx_params *)param;
	mlx_destroy_image(p->mlx, p->img.img);
	mlx_destroy_window(p->mlx, p->mlx_win);
	mlx_destroy_display(p->mlx);
	free(p->mlx);
	exit_fdf(p);
	return (0);
}

t_mlx_params	my_mlx_init(void)
{
	t_mlx_params	mlx_params;

	mlx_params.mlx = mlx_init();
	if (!mlx_params.mlx)
		exit(1);
	mlx_params.mlx_win = mlx_new_window(mlx_params.mlx, 1920, 1080, "fdf");
	if (!mlx_params.mlx_win)
		exit(1);
	mlx_params.img.img = mlx_new_image(mlx_params.mlx, 1920, 1080);
	if (!mlx_params.img.img)
		exit(1);
	mlx_params.img.addr = mlx_get_data_addr(mlx_params.img.img,
			&mlx_params.img.bits_per_pixel,
			&mlx_params.img.line_length,
			&mlx_params.img.endian);
	mlx_params.zoom = 1;
	mlx_params.tx = 0;
	mlx_params.ty = 0;
	return (mlx_params);
}
