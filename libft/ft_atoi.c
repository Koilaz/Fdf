/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:51:18 by lmarck            #+#    #+#             */
/*   Updated: 2024/11/03 16:29:29 by lmarck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	j;
	int	nb;

	i = 0;
	nb = 0;
	j = 0;
	while ((str[i] <= '\r' && str[i] >= '\t') || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			j++;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb + str[i] - '0';
		i ++;
		if (str[i] >= '0' && str[i] <= '9')
			nb = 10 * nb;
	}
	if (j % 2)
		return (-nb);
	return (nb);
}
