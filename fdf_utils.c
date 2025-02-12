/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarck <lmarck@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:19:06 by lmarck            #+#    #+#             */
/*   Updated: 2025/02/10 19:23:23 by lmarck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	is_white_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\v' || c == '\f')
		return (1);
	return (0);
}

int	count_x(const char *s)
{
	int	i;
	int	n;

	n = 0;
	i = 0;
	if (s[0] == '\0' || s == NULL)
		return (0);
	while (is_white_space(s[i]))
		i++;
	while (s[i])
	{
		if ((ft_isdigit(s[i]) || s[i] == '-')
			&& i > 1 && is_white_space(s[i - 1]))
			n++;
		i++;
	}
	return (n);
}

void	free_map(t_pix **map, int y)
{
	while (y >= 0)
	{
		free(map[y]);
		y--;
	}
}

void	exit_fdf1(t_pix **map)
{
	free_map(map, (map[0][0]).z);
	free(map);
	write(2, "open2failed", 12);
	exit(0);
}

void	exit_fdf(t_mlx_params *mlxp)
{
	free(mlxp->map.cloud);
	exit(0);
}
