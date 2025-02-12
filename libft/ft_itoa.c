/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 20:28:43 by lmarck            #+#    #+#             */
/*   Updated: 2024/11/03 16:44:09 by lmarck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long int	get_digit(int n);
char			*ft_itoa(int n);

char	*ft_itoa(int sn)
{
	char		*str;
	long int	len;
	long int	n;

	n = sn;
	len = get_digit(n);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		n = n * -1;
	}
	if (n == 0)
		str[0] = '0';
	str [len] = '\0';
	while (n)
	{
		str[--len] = (n % 10) + '0';
		n = n / 10;
	}
	return (str);
}

static long int	get_digit(const int d)
{
	size_t		s;
	long int	n;

	s = 0;
	n = d;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		s++;
		n = n * -1;
	}
	while (n)
	{
		n = n / 10;
		s++;
	}
	return (s);
}
