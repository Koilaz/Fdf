
#ifndef FDF_H
# define FDF_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <unistd.h>
# include <stddef.h>
# include "stdio.h"
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"

int **get_map(char *file);
int map_size(char *file);
int x_range (char **line);
void free_map(int **map);
int **fill_line(int y, int fd, int **map);

#endif