/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarck <lmarck@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:32:19 by leo               #+#    #+#             */
/*   Updated: 2025/01/23 13:32:19 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int main(int argc, char **argv)
{
    int **map;

    if(argc != 2)
        return(0);
    map = get_map(argv[1]);
    int y = 1;
    int x = 0;
    printf("y = %d \n", map[0][0]);
    printf("x = %d \n", map[0][1]);
    while (y <= map[0][0])
    {
        while(x < map [0][1])
        {
        printf("%d ", map[x][y]);
        x++;
        }
        x = 0;
        write(1, "\n", 1);
        y++;
    }
    free_map(map);
    free(map);
    return (0);

}
int **get_map(char *file)
{
    int     fd;
    int     y;
    int     **map;

    y = map_size(file);
    ft_printf("y = %d\n", y); /****Debug****/
    map = ft_calloc(y + 2, sizeof(int *));
    if(!map)
        return(0);
    fd = open(file, O_RDONLY);
        if(fd < 0)
            return(write(1, "open failed2", 13), NULL);
    map[0] = malloc(2 * sizeof(int));
    if(!map[0])
        return (NULL);
    map[0][0] = y;
    while (y >= 0)
    {
        map = fill_line(y, fd, map);
        y--;
    }
    close(fd);
    return (map);
}
int **fill_line(int y, int fd, int **map)
{
    int         x;
    static int  range_max;
    int         range;
    char        *line;
    char        **splited_line;

    printf("fill line y = %d\n", y);
    if(y)
    {
        x = 0;
        line = get_next_line(fd, 0);
        splited_line = ft_split(line, ' ');
        range = x_range(splited_line);
        if (range > range_max)
            range_max = range;
        while(splited_line[x])
        {
        map[y] = ft_calloc(x_range(splited_line) + 1, sizeof(int));
        map[y][x] = ft_atoi(splited_line[x]);
        x++;
        }
    }
    else if (y == 0)
        map[0][1] = range_max;
    return (map);
}

int x_range (char **line)
{
    int i;

    i = 0;
    while(line[i])
        i++;
    return (i);
}

void free_map(int **map)
{
    int y;

    y = 0;
    while (map[y])
    {
        free(map[y]);
        y++;
    }
}

int map_size(char *file)
{   
    int     fd;
    int     y;
    char    *line;

    y = 0;
    fd = open(file, O_RDONLY);
    if(fd < 0)
        return(write(1, "open failed1", 13), 0);
    while ((line = get_next_line(fd, 0)) != NULL)     
        y++;
    close(fd);
    line = get_next_line(fd, 1);
    return(y);
}