/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:56:53 by lmarck            #+#    #+#             */
/*   Updated: 2024/11/15 14:48:29 by lmarck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	int			len;
	va_list		ap;

	if (!format)
		return (-1);
	va_start(ap, format);
	len = print_str(format, ap);
	va_end(ap);
	return (len);
}

int	print_str(const char *format, va_list ap)
{
	size_t	i;
	int		len;
	int		lenc;

	len = 0;
	i = 0;
	while (format[i])
	{
		if (format[i] != '%')
			lenc = iputchar(format[i]);
		else
			lenc = putvar(format[++i], ap);
		if (lenc < 0)
			return (-1);
		len = len + lenc;
		i++;
	}
	return (len);
}

size_t	putvar(const char format_i, va_list ap)
{
	if (!format_i)
		return (-1);
	if (format_i == 's')
		return (iput_s(ap));
	if (format_i == 'c')
		return (iput_c(ap));
	if (format_i == 'p' || format_i == 'x' || format_i == 'X')
		return (iput_p_x(ap, format_i));
	if (format_i == '%')
		return (iputchar('%'));
	if (format_i == 'd' || format_i == 'i')
		return (iput_d(ap));
	if (format_i == 'u')
		return (iput_u(ap));
	return (-1);
}
