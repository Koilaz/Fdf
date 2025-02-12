/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iput_pxc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:17:35 by lmarck            #+#    #+#             */
/*   Updated: 2024/11/15 14:48:28 by lmarck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	rec_iput_p(unsigned long adr, char *bhex, int len)
{
	if (!adr)
		return (0);
	return (rec_iput_p(adr / 16, bhex, len) + write(1, &bhex[adr % 16], 1));
}

size_t	iput_p_x(va_list ap, char format_i)
{
	char				*bhex;
	unsigned long int	adr;
	int					len;

	len = 0;
	if (format_i == 'X')
		bhex = "0123456789ABCDEF";
	else
		bhex = "0123456789abcdef";
	if (format_i == 'p')
	{
		adr = (va_arg(ap, unsigned long int));
		if (!adr)
			return (write(1, "(nil)", 5));
		len = write(1, "0x", 2);
	}
	else
		adr = (va_arg(ap, unsigned int));
	if (!adr)
		return (write(1, "0", 1));
	return (len + rec_iput_p(adr, bhex, len));
}

size_t	iput_c(va_list ap)
{
	char	c;

	c = (char)va_arg(ap, int);
	return ((write(1, &c, 1)));
}

size_t	iputstr(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (write(1, &str[i], 1))
			i++;
	}
	return (i);
}

size_t	iputchar(const char c)
{
	if (!c)
		return (0);
	return (write(1, &c, 1));
}
