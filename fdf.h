
#ifndef FDF_H
# define FDF_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif


typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_mlx_params
{
	void    *mlx;
	void    *mlx_win;
	t_data  img;
}   t_mlx_params;

typedef	struct	s_tri_d {
	int	x;	//initial 3d cloud x value
	int	y;
	int	z;
	float scl_z; //scaled z so the maximu height is not too spread
	int	color;
	float	xp; //x position of the point on the 2d projection after applying the rotation.
	float	yp;
}				t_tri_d;

typedef struct	s_map_data {
	t_tri_d *cloud;
	int		yp_v_range; // = yp_v_max - yp_v_min; y range of the point we want to display
	int		xp_v_range; // x range of the point we want to display
	int		yp_v_max; // y max of the point we want to display and connect
	int		yp_v_min;
	int		xp_v_min;
	int		xp_v_max;
	int		xc_range;
	int		yc_range;
	float	rx;
	float	ry;
	float	ds;  //display scale applied to the projection so it can fully appear in the window, calculated in get_d_scale and should be used to display correctly the line from dda
	float	h_scale;
	int		offset_x;	//offset value to center our 2d projection, should be use again to apply the correct offset to the line from dda algorithme
	int		offset_y;
	int		z_max;
	int		z_min;
}				t_map_data;


typedef	struct	s_pix {
	int	z;
	int	color;
}				t_pix;



# include <unistd.h>
# include <stddef.h>
# include "stdio.h"
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
# include "mlx.h"

//Parsing

t_pix **get_map(char *file);
int map_size(char *file);
int x_range (char **line);
void free_map(t_pix **map, int y);
t_pix **fill_line(int y, int fd, t_pix **map, int x);
int	count_x(const char *s, const char c);
t_pix **rev_map_line(t_pix **map);
t_pix get_pix(char *point);
int ft_htoi(char *str);
int color_altitude(int z);
t_map_data table_to_struct(t_pix **map);
t_tri_d	transfer_data(t_pix point, int x, int y);

//mlx

void *my_new_window(void *mlx);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
t_mlx_params my_mlx_init(void);
int redraw(void *param);

//projection
void isometric_view(t_map_data map, t_mlx_params mlx_params);
float m_scale(int y, int x);
int z_max(t_tri_d *map, int xr, int yr);
t_map_data normalize_height(t_map_data map);
int display_projection(t_map_data map, t_mlx_params mlxp);
t_map_data make_projection(t_map_data map);
float get_d_scale(t_map_data map);
t_tri_d rotate_point(t_tri_d pt, float ry, float rx);
t_map_data get_range(t_map_data map, int i);
void connect_point(t_map_data map, t_mlx_params mlxp);
float get_maxf(float a, float b);
void dda(t_tri_d p1, t_tri_d p2, t_map_data map, t_mlx_params mlxp);

// utils
int big(float dx, float dy);
int	ft_abs(int i);
void exit_fdf(t_pix **map);
int get_min(int a, int b);
int get_max(int a, int b);
void	free_map(t_pix **map, int y);

#endif
