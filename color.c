/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarck <lmarck@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:25:03 by lmarck            #+#    #+#             */
/*   Updated: 2025/02/10 19:02:14 by lmarck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	color_altitude(int z)
{
	if (z >= 10)
		return (16777215);
	if (z > 7)
		return (10066329);
	if (z > 5)
		return (20480);
	if (z > 1)
		return (30720);
	if (z >= 0)
		return (16764006);
	if (z > -2)
		return (65535);
	if (z > -7)
		return (18355);
	else
		return (2670);
	return (0);
}

int	ft_htoi(char *str)
{
	long	nt;
	int		n ;
	int		i;

	nt = 0;
	i = 0;
	while (is_white_space(str[i]))
		i++;
	if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
		i = i + 2;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
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

int	col_grad(t_tri_d p1, t_tri_d p2, float steps, int i)
{
	float	t;
	t_color	c;
	t_color	c1;
	t_color	c2;

	if (steps < 2)
		return (p1.color);
	t = (float)i / (steps - 1);
	c1 = i_to_col(p1.color);
	c2 = i_to_col(p2.color);
	c.r = (int)(c1.r + (c2.r - c1.r) * t);
	c.g = (int)(c1.g + (c2.g - c1.g) * t);
	c.b = (int)(c1.b + (c2.b - c1.b) * t);
	return (col_to_i(c));
}

t_color	i_to_col(int ic)
{
	t_color	c;

	c.r = (ic >> 16) & 0xFF;
	c.g = (ic >> 8) & 0xFF;
	c.b = ic & 0xFF;
	return (c);
}

int	col_to_i(t_color c)
{
	int	ic;

	ic = 0;
	ic |= c.r << 16;
	ic |= c.g << 8;
	ic |= c.b;
	return (ic);
}
