/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarck <lmarck@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:53:06 by lmarck            #+#    #+#             */
/*   Updated: 2025/02/10 21:10:13 by lmarck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <unistd.h>
# include <stddef.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
# include "mlx.h"

# define ESC_KEY      65307
# define ARROW_UP     65362
# define ARROW_DOWN   65364
# define ARROW_LEFT   65361
# define ARROW_RIGHT  65363
# define PLUS_KEY   65451
# define MINUS_KEY  65453
# define SPACE_KEY 32
# define A_KEY 97
# define Q_KEY 113
# define S_KEY 115
# define W_KEY 119
# define D_KEY 100
# define E_KEY 101
# define T_KEY 116
# define SCROLL_UP    4
# define SCROLL_DOWN  5

typedef struct s_trif
{
	float	x;
	float	y;
	float	z;
}				t_trif;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}				t_color;

typedef struct s_tri_d
{
	int		x;
	int		y;
	int		z;
	float	scl_z;
	int		color;
	float	xp;
	float	yp;
}				t_tri_d;

typedef struct s_map_data
{
	t_tri_d	*cloud;
	int		yp_v_range;
	int		xp_v_range;
	int		yp_v_max;
	int		yp_v_min;
	int		xp_v_min;
	int		xp_v_max;
	int		xc_range;
	int		yc_range;
	float	rx;
	float	ry;
	float	rz;
	float	ds;
	float	h_scale;
	int		offset_x;
	int		offset_y;
	int		z_max;
	int		z_min;
}				t_map_data;

typedef struct s_pix
{
	int	z;
	int	color;
}				t_pix;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_mlx_params
{
	void		*mlx;
	void		*mlx_win;
	t_data		img;
	t_map_data	map;
	float		zoom;
	int			tx;
	int			ty;
}	t_mlx_params;

t_pix			**get_map(char *file);
int				map_size(char *file);
int				x_range(char **line);
void			free_map(t_pix **map, int y);
t_pix			**fill_line(int y, int fd, t_pix **map, int x);
int				count_x(const char *s);
t_pix			**rev_map_line(t_pix **map);
t_pix			get_point(char *point);
t_map_data		table_to_struct(t_pix **map);
t_tri_d			transfer_data(t_pix point, int x, int y);

//mlx
void			clear_image(t_data *img, int width, int height);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
t_mlx_params	my_mlx_init(void);
int				redraw(void *param);

//projection
t_map_data		isometric_view(t_map_data map, t_mlx_params mlx_params);
int				z_max(t_tri_d *map, int xr, int yr);
t_map_data		normalize_height(t_map_data map);
int				display_projection(t_map_data map, t_mlx_params mlxp);
t_map_data		make_projection(t_map_data map);
float			get_d_scale(t_map_data map);
t_tri_d			rotate_point(t_tri_d pt, float ry, float rx, float rz);
t_map_data		get_range(t_map_data map, int i);
void			connect_point(t_map_data map, t_mlx_params mlxp);
float			get_maxf(float a, float b);
void			dda(t_tri_d p1, t_tri_d p2, t_map_data map, t_mlx_params mlxp);
void			topview(t_mlx_params *p);

//color
int				col_to_i(t_color c);
int				ft_htoi(char *str);
int				color_altitude(int z);
t_color			i_to_col(int ic);
int				col_grad(t_tri_d p1, t_tri_d p2, float steps, int i);

// utils
int				ft_abs(int i);
void			exit_fdf1(t_pix **map);
void			exit_fdf(t_mlx_params *mlxp);
int				get_min(int a, int b);
int				get_max(int a, int b);
void			free_map(t_pix **map, int y);
int				is_white_space(char c);

/* HOOKS */
int				key_press_hook(int keycode, void *param);
int				mouse_press_hook(int button, int x, int y, void *param);
int				close_window(void *param);
int				extra_press_hook(int keycode, void *param);

#endif
