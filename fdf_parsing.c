/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarck <lmarck@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:00:53 by lmarck            #+#    #+#             */
/*   Updated: 2025/01/30 16:46:04 by lmarck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	map_size(char *file)
{
	int		fd;
	int		y;
	char	*line;
	int		argx;

	argx = 0;
	y = 0;
	line = "not NULL";
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (write(2, "open_1 failed\n", 14), 0);
	while (line)
	{
		line = get_next_line(fd, 0);
		if (!line)
			break ;
		if (argx && line && argx != count_x(line, ' '))
			return (free(line), 0);
		argx = count_x(line, ' ');
		free(line);
		y++;
	}
	close(fd);
	line = get_next_line(fd, 1);
	return (y);
}

int	count_x(const char *s, const char c)
{
	int	i;
	int	n;

	n = 0;
	i = 1;
	if (s[0] == '\0' || s == NULL)
		return (0);
	if (s[0] != c)
		n++;
	while (s[i])
	{
		if (s[i] != c && s[i - 1] == c)
			n++;
		i++;
	}
	return (n);
}

t_pix	**get_map(char *file)
{
	int	fd;
	int	y;
	int	**map;

	y = map_size(file);
	map = malloc((y + 1) * sizeof(t_pix *));
	if (!map)
		return (0);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (write(2, "open2_failed\n", 14), NULL);
	map[0] = malloc(2 * sizeof(int));
	if (!map[0])
		return (NULL);
	map[0][0] = y;
	while (y >= 0)
	{
		map = fill_line(y, fd, map, 0);
		y--;
	}
	map = rev_map_line(map);
	close(fd);
	return (map);
}
t_pix **rev_map_line(t_pix **map)
{
	int i;
	int y;
	int *line;

	i = 1;
	y = (map[0][0]).z;
	while(i < y)
	{
		line = map[i];
		map[i] = map[y];
		map[y] = line;
		y--;
		i++;
	}
	return(map);
}


t_pix	**fill_line(int y, int fd, t_pix **map, int x)
{
	static int	range;
	char		*line;
	char		**splited_line;

	if (y)
	{
		line = get_next_line(fd, 0);
		splited_line = ft_split(line, ' ');
		if (!range)
			range = x_range(splited_line);
		map[y] = ft_calloc(range, sizeof(int));
		if (!map[y])
			return (free(splited_line), free(line), NULL);
		while (splited_line[x])
		{
			map[y][x] = get_pix(splited_line[x]);
			free(splited_line[x]);
			x++;
		}
		free(line);
		free(splited_line);
	}
	else if (y == 0)
		(map[0][1]).z = range;
	return (map);
}

t_pix get_pix(char *point)
{
	t_pix pixel;
	char **split;

	split = ft_split(point, ',');
	pixel.z = ft_atoi(split[0]);
	if (split[1])
		pixel.color = ft_htoi(split[1]);
	else
		pixel.color = color_altitude(pixel.z);
	return (pixel);
}
int ft_htoi(char *str)
{
	int nt;
	int n ;
	int i;

	if(ft_strlen(str) != 8)
		return (0);
	nt = 0;
	i = 2;
	while(i < 8)
	{
		if(str[i] >= '0' && str[i] <= '9');
			n = str[i] - '0';
		if (str[i] >= 'A' && str[i] <= 'F');
			n = str[i] - 'A' + 10;
		nt = n + nt;
		nt = 10 * nt;
	}
	return (nt);
}

int	x_range(char **line)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	return (i);
}
