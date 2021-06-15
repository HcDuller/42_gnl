/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcduller <hcduller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 15:44:03 by hcduller          #+#    #+#             */
/*   Updated: 2021/06/15 14:36:53 by hcduller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_bzero(void *s, size_t n);
char	*ft_strchr(const char *s, int c);
void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	smaller(size_t a, size_t b);

void	ft_bzero(void *s, size_t n)
{
	char	*p;

	p = (char *)s;
	while (n > 0)
	{
		*(p + --n) = (char)0;
	}
}

char	*ft_strchr(const char *s, int c)
{
	char	*r;

	r = (char *)s;
	while (*r)
	{
		if (*r == (char)c)
			return (r);
		r++;
		if (*r == (char)c)
			return (r);
		if (!*r)
			return (0);
	}
	if (!*r && (char)c == 0)
		return (r);
	return (0);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (ptr)
	{
		ft_bzero(ptr, count * size);
		return (ptr);
	}
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	nl;
	size_t	sl;
	char	*ptr;

	if (!s)
		return (NULL);
	i = 0;
	sl = ft_strlen(s);
	if (sl < start)
		return (ft_calloc(1, 1));
	sl = ft_strlen(&s[start]);
	nl = smaller(sl, len);
	ptr = ft_calloc(nl + 1, sizeof(char));
	if (ptr)
	{		
		while (i < len && s[start + i])
		{
			*(ptr + i) = s[start + i];
			i++;
		}
	}
	return (ptr);
}

size_t	smaller(size_t a, size_t b)
{
	if (a < b)
		return (a);
	return (b);
}