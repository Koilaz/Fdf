
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

typedef	struct	s_pix {
	int	z;
	int	color;
}				t_pix;

typedef	struct	s_tri_d {
	int	x;
	int	y;
	int	z;
	int	color;
}				t_tri_d;

typedef	struct	s_bi_d {
	float	xp;
	float	yp;
	int	x;
	int	y;
	int	z;
	int	color;
}				t_bi_d;


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

void *my_new_window(void *mlx);
void top_view(t_pix **map, void *mlx_win, t_data img, void *mlx);
float map_scale(t_pix **map);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
t_pix get_pix(char *point);
int ft_htoi(char *str);
int color_altitude(int z);
void put_iso_point(t_bi_d *map, void *mlx_win, t_data img, void *mlx);
t_bi_d *map_iso(t_tri_d *mapt, float rx, float ry);
t_tri_d *table_to_struct(t_pix **map);
t_tri_d put_dimension(int x_range, int y_range);
void exit_fdf(t_pix **map);
float m_scale(int y, int x);
int	ft_abs(int i);
t_bi_d *apply_rotation(t_bi_d *map, float rx, float ry);
t_bi_d rota(t_bi_d p, float ry, float rx, float z_scale);
#endif
