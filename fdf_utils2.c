/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarck <lmarck@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:30:12 by lmarck            #+#    #+#             */
/*   Updated: 2025/02/10 19:00:48 by lmarck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	x_range(char **line)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	return (i);
}

int	get_min(int a, int b)
{
	if (a > b)
		return (b);
	else
		return (a);
}

int	get_max(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

int	ft_abs(int i)
{
	if (i < 0)
		i = -i;
	return (i);
}

float	get_maxf(float a, float b)
{
	if (a > b)
		return (a);
	return (b);
}
