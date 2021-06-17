/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcduller <hcduller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 15:44:03 by hcduller          #+#    #+#             */
/*   Updated: 2021/06/17 00:04:37 by hcduller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlen(const char *s);
void	ft_bzero(void *s, size_t n);

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

void	ft_bzero(void *s, size_t n)
{
	char	*p;

	p = (char *)s;
	while (n > 0)
	{
		*(p + --n) = (char)0;
	}
}
