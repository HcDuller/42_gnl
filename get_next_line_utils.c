/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcduller <hcduller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 15:44:03 by hcduller          #+#    #+#             */
/*   Updated: 2021/06/16 19:43:13 by hcduller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void			*ft_calloc(size_t count, size_t size);
size_t			ft_strlen(const char *s);
char			*ft_substr(char const *s, unsigned int start, size_t len);
size_t			ft_strlen_custom(const char *s);
static size_t	smaller(size_t a, size_t b);

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	char	*p;

	ptr = malloc(count * size);
	if (ptr)
	{
		p = (char *)ptr;
		while (count > 0)
			*(p + --count) = 0;
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

size_t	ft_strlen_custom(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != '\0' && s[i] != '\n')
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
