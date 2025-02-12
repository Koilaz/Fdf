/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarck <lmarck@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 20:17:42 by lmarck            #+#    #+#             */
/*   Updated: 2025/02/10 16:43:30 by lmarck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <unistd.h>
# include <stddef.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>

void	*ft_memset( void *pointer, int value, size_t count);
void	*ft_calloc(size_t nmemb, size_t size);
char	*get_next_line(int fd);
size_t	ft_strlen(const char *str);
char	*new_read(char *buf, int fd, int nb_read, char *tmp);
char	*ft_join(char *buf, char *str);
char	*ft_strchr(const char *string, int searchedChar);
void	ft_bufleft(char *buf);

#endif
