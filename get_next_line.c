/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcduller <hcduller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 15:44:01 by hcduller          #+#    #+#             */
/*   Updated: 2021/06/16 19:05:51 by hcduller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	piler(char **s0, char **s1, ssize_t rsize);
static void	*ft_free(void *ptr);
static void	memswap(char **s0, char **s1);
static int	pile_controller(char **line, char **buffer, int fd);

int	get_next_line(int fd, char **line)
{
	static char	*ps_buf;
	int			r;

	if (!ps_buf)
		ps_buf = (char *)ft_calloc(BUFFER_SIZE + 1, 1);
	if (ps_buf)
	{
		if (!*line)
			*line = (char *)ft_calloc(1, 1);
		return (pile_controller(line, &ps_buf, fd));
	}
	return (-1);
}

void	*ft_free(void *ptr)
{
	free(ptr);
	return (NULL);
}

void	memswap(char **s0, char **s1)
{
	free(*s0);
	*s0 = *s1;
}

int	piler(char **s0, char **s1, ssize_t rsize)
{
	size_t	l[4];
	char	*t;

	l[0] = ft_strlen(*s0);
	l[1] = rsize;
	l[2] = l[0] + l[1];
	l[3] = 0;
	t = (char *)ft_calloc(l[2] + 1, 1);
	if (t)
	{
		while (l[3] < l[0])
			*(t + l[3]++) = (*s0)[l[3]];
		while ((l[3] - l[0]) < l[1] && (*s1)[l[3] - l[0]] != '\n')
			*(t + l[3]++) = (*s1)[l[3] - l[0]];
		memswap(s0, &t);
		if (l[3] == l[2])
		{
			if (l[3] == ft_strlen(*s1) + l[0])
				return (1);
			t = ft_substr(*s1, l[3] - l[0] + 1, l[1] - (l[3] - l[0] + 1));
			memswap(s1, &t);
			return (0);
		}
	}
	return (-1);
}

int	pile_controller(char **line, char **buffer, int fd)
{
	size_t	bl[2];
	int		rs[2];

	bl[0] = ft_strlen_custom(*buffer);
	bl[1] = ft_strlen(*buffer);
	if (bl[0] || bl[1])
	{
		rs[0] = piler(line, buffer, (ssize_t)bl[0]);
		if (rs[0] == 0)
			return (1);
		if (rs[0] == -1)
			return (-1);
	}
	if (*buffer)
	{
		free(*buffer);
		*buffer = (char *)ft_calloc(BUFFER_SIZE + 1, 1);
	}
	rs[1] = read(fd, *buffer, BUFFER_SIZE);
	if (rs[1] > 0)
	{
		return (pile_controller(line, buffer, fd));
	}
	*line = ft_free(*line);
	return (0);
}
