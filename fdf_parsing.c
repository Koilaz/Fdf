/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarck <lmarck@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:00:53 by lmarck            #+#    #+#             */
/*   Updated: 2025/01/27 20:24:02 by lmarck           ###   ########.fr       */
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

int	**get_map(char *file)
{
	int	fd;
	int	y;
	int	**map;

	y = map_size(file);
	map = malloc((y + 1) * sizeof(int *));
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
	close(fd);
	return (map);
}

int	**fill_line(int y, int fd, int **map, int x)
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
			map[y][x] = ft_atoi(splited_line[x]);
			free(splited_line[x]);
			x++;
		}
		free(line);
		free(splited_line);
	}
	else if (y == 0)
		map[0][1] = range;
	return (map);
}

int	x_range(char **line)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	return (i);
}
