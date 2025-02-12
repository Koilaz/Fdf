/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarck <lmarck@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:00:53 by lmarck            #+#    #+#             */
/*   Updated: 2025/02/10 19:22:12 by lmarck           ###   ########.fr       */
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
		return (write(2, "open_1 failed\n", 14), exit(0), 0);
	while (line)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (argx && line && argx != count_x(line))
			return (write(2, "Map not correct\n", 17), free(line), exit(0), 0);
		argx = count_x(line);
		free(line);
		y++;
	}
	close(fd);
	return (y);
}

t_pix	**get_map(char *file)
{
	int		fd;
	int		y;
	t_pix	**map;

	y = map_size(file);
	map = malloc((y + 1) * sizeof(t_pix *));
	if (!map)
		return (write(2, "Malloc failed\n", 15), exit(0), NULL);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit_fdf1(map);
	map[0] = malloc(2 * sizeof(t_pix));
	if (!map[0])
		return (write(2, "Malloc failed\n", 15), exit(0), NULL);
	(map[0][0]).z = y;
	while (y >= 0)
	{
		map = fill_line(y, fd, map, 0);
		y--;
	}
	map = rev_map_line(map);
	close(fd);
	return (map);
}

t_pix	**fill_line(int y, int fd, t_pix **map, int x)
{
	static int	range;
	char		*line;
	char		**splited_line;

	if (y)
	{
		line = get_next_line(fd);
		splited_line = ft_split(line, ' ');
		if (!range)
			range = x_range(splited_line);
		map[y] = ft_calloc(range, sizeof(t_pix));
		if (!map[y])
			return (free(splited_line), free(line), NULL);
		while (splited_line[x] && range)
		{
			map[y][x] = get_point(splited_line[x]);
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

t_pix	get_point(char *point)
{
	t_pix	tpoint;
	char	**split;
	char	*trimmed;
	int		i;

	i = 0;
	split = ft_split(point, ',');
	tpoint.z = ft_atoi(split[0]);
	trimmed = ft_strtrim(split[1], " \t\n\r");
	if (!split[1] || !*(split[1]))
		tpoint.color = color_altitude(tpoint.z);
	else
		tpoint.color = ft_htoi(trimmed);
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(trimmed);
	free(split);
	return (tpoint);
}
