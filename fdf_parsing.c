/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:00:53 by lmarck            #+#    #+#             */
/*   Updated: 2025/02/03 15:48:35 by leo              ###   ########.fr       */
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
	int		fd;
	int		y;
	t_pix	**map;

	y = map_size(file);
	map = malloc((y + 1) * sizeof(t_pix *));
	if (!map)
		return (0);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit_fdf(map);
	map[0] = malloc(2 * sizeof(t_pix));
	if (!map[0])
		return (NULL);
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
void exit_fdf(t_pix **map)
{
	free_map(map, (map[0][0]).z);
	free(map);
	write(2, "open2failed", 12);
	exit(0);
}
t_pix **rev_map_line(t_pix **map)
{
	int i;
	int y;
	t_pix *line;

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
		map[y] = ft_calloc(range, sizeof(t_pix));
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
	int i;

	i = 0;
	split = ft_split(point, ',');
	pixel.z = ft_atoi(split[0]);
	if (split[1])
		pixel.color = ft_htoi(split[1]);
	else
		pixel.color = color_altitude(pixel.z);
	while(split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (pixel);
}
int color_altitude(int z)
{
	if (z >= 10)
		return(16777215);
	if (z > 7)
		return(10066329);
	if (z > 5)
		return(20480);
	if (z > 1)
		return(30720);
	if (z >= 0)
		return(16764006);
	if (z > -2)
		return(65535);
	if (z > -7)
		return(18355);
	else
		return(2670);
}

int ft_htoi(char *str)
{
	long	nt;
	int		n ;
	int		i;

	nt = 0;
	i = 0;
	if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
		i = i + 2;
	while(str[i])
	{
		if(str[i] >= '0' && str[i] <= '9')
			n = str[i] - '0';
		else if (str[i] >= 'A' && str[i] <= 'F')
			n = str[i] - 'A' + 10;
		else if (str[i] >= 'a' && str[i] <= 'f')
			n = str[i] - 'a' + 10;
		else
			return (0);
		nt = 16 * nt + n;
		i++;
	}
	return ((int)nt);
}

int	x_range(char **line)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	return (i);
}
