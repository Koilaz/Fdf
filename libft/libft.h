/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 20:46:26 by lmarck            #+#    #+#             */
/*   Updated: 2024/11/05 13:02:19 by lmarck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

void		ft_bzero(void *ptr, size_t n);
int			ft_atoi(const char *str);
int			ft_toupper( int character );
int			ft_tolower( int character );

//memory block
void		*ft_memcpy( void *dest, const void *src, size_t n);
void		*ft_memset( void *pointer, int value, size_t count);
void		*ft_memmove( void *dest, const void *src, size_t n);
int			ft_memcmp( const void *ptr1, const void *ptr2, size_t size );
void		*ft_memchr( const void *mblk, int sdchr, size_t size );
void		*ft_calloc(size_t nmemb, size_t size);
//is
int			ft_isdigit(int character);
int			ft_isascii(int character);
int			ft_isalpha( int character );
int			ft_isalnum(int character);
int			ft_isprint(int c);
//String
char		*ft_strchr(const char *string, int searchedChar );
size_t		ft_strlcat(char *dest, const char *src, size_t size );
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
size_t		ft_strlen(const char *theString);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char *big, const char *lit, size_t len);
char		*ft_strrchr( const char *string, int searchedChar);
char		*ft_strdup(const char *src);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
char		*ft_itoa(int n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
//bonus
t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *nw);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *nw);
void		ft_lstdelone(t_list *lst, void (*del)(void*));
void		ft_lstclear(t_list **lst, void (*del)(void*));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif
