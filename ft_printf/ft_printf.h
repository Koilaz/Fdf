/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:54:16 by lmarck            #+#    #+#             */
/*   Updated: 2024/11/15 14:48:29 by lmarck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stddef.h>

int		ft_printf(const char *str, ...);
size_t	iput_c(va_list ap);
size_t	putvar(const char format_i, va_list ap);
size_t	iput_s(va_list ap);
size_t	iputchar(char c);
size_t	iput_p_x(va_list ap, const char format_i);
size_t	iputstr(char *str);
size_t	iput_d( va_list ap);
int		rec_iput_d(int i);
int		rec_iput_p(unsigned long int adr, char *bhex, int len);
size_t	iput_u(va_list ap);
int		print_str(const char *format, va_list ap);

#endif
