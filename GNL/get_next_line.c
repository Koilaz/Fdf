/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:41:17 by lmarck            #+#    #+#             */
/*   Updated: 2025/01/23 21:29:56 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd,int reset)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*str;
	char		*tmp;

	if(reset)
	{
		ft_memset(buf, 0, BUFFER_SIZE + 1);
		return ("");
	}
	tmp = NULL;
	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	str = ft_calloc(1, sizeof(char));
	if (!str)
		return (NULL);
	if (!ft_strchr(buf, '\n'))
	{
		free(str);
		str = new_read(buf, fd, 1, tmp);
	}
	else
		str = ft_join(buf, str);
	if (!str || !str[0])
		return (free(str), NULL);
	return (str);
}

char	*new_read(char *buf, int fd, int nb_read, char *tmp)
{
	char	*nstr;

	nstr = ft_calloc(1, sizeof(char));
	if (!nstr)
		return (NULL);
	if (buf[0])
	{
		nstr = ft_join(buf, nstr);
		if (!nstr)
			return (free(nstr), nstr = NULL, NULL);
	}
	while (nb_read > 0)
	{
		nb_read = read(fd, buf, BUFFER_SIZE);
		buf[nb_read] = '\0';
		tmp = ft_join(buf, nstr);
		if (!tmp)
			return (NULL);
		nstr = tmp;
		if (ft_strchr(nstr, '\n'))
			break ;
	}
	if (nb_read < 0)
		return (free(nstr), nstr = NULL, NULL);
	return (nstr);
}

char	*ft_join(char *buf, char *str)
{
	int		i;
	int		j;
	int		k;
	char	*nstr;

	i = ft_strlen(str);
	j = 0;
	k = 0;
	while (buf[j] && buf[j] != '\n')
		j++;
	nstr = ft_calloc (i + j + 2, sizeof(char));
	if (!nstr)
		return (free(str), NULL);
	while (k < i)
	{
		nstr[k] = str[k];
		k++;
	}
	while (k <= (i + j))
	{
		nstr[k] = buf[k - i];
		k++;
	}
	ft_bufleft(buf);
	return (free(str), str = NULL, nstr);
}

void	ft_bufleft(char *buf)
{
	int	i;
	int	j;

	if (!buf || !buf[0])
		return ;
	i = 0;
	j = 0;
	while (buf[i] != '\n' && buf[i])
		i++;
	if (buf[i] == '\n')
		i++;
	while (buf[i])
	{
		buf[j] = buf[i];
		i++;
		j++;
	}
	buf[j] = '\0';
}
