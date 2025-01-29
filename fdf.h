
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

int **get_map(char *file);
int map_size(char *file);
int x_range (char **line);
void free_map(int **map, int y);
int **fill_line(int y, int fd, int **map, int x);
int	count_x(const char *s, const char c);

void *my_new_window(void *mlx);
void top_view(int **map, void *mlx_win, t_data img, void *mlx);
float map_scale(int **map);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

#endif
