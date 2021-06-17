/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcduller <hcduller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 15:44:01 by hcduller          #+#    #+#             */
/*   Updated: 2021/06/16 23:31:04 by hcduller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_bzero(void *s, size_t n);
void	split_at_break(char **pre, char **pos);
void	concat(char **line, char *buf);
int		has_break(char *s);

int	has_break(char *s)
{
	int	c;

	c = 0;
	while (*s)
	{
		if (*s == '\n')
			return (1);
		s++;
	}
	return (0);
}

void	concat(char **line, char *buf)
{
	size_t	ls[3];
	char	*t;

	if (!*line)
		*line = ft_calloc(1, 1);
	ls[0] = ft_strlen(*line);
	ls[1] = ft_strlen(buf);
	ls[2] = 0;
	if (ls[0] + ls[1])
	{
		t = (char *)ft_calloc(ls[0] + ls[1] + 1, 1);
		while (ls[2] < ls[0])
		{
			t[ls[2]] = (*line)[ls[2]];
			ls[2]++;
		}
		while (ls[2] < ls[0] + ls[1])
		{
			t[ls[2]] = buf[(ls[2] - ls[0])];
			ls[2]++;
		}
		free(*line);
		*line = t;
	}
}

void	split_at_break(char **pre, char **pos)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	free(*pos);
	while ((*pre)[i] && (*pre)[i] != '\n')
		i++;
	(*pre)[i] = '\0';
	*pos = ft_calloc(BUFFER_SIZE + 1, 1);
	i++;
	while ((*pre)[i])
	{
		(*pos)[j++] = (*pre)[i];
		(*pre)[i++] = '\0';
	}
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

int	get_next_line(int fd, char **line)
{
	static char	*perm;
	char		*buf;
	int			read_value;

	if (!perm)
		perm = ft_calloc(BUFFER_SIZE + 1, 1);
	buf = ft_calloc(BUFFER_SIZE + 1, 1);
	while (!has_break(buf) && !has_break(perm))
	{
		concat(line, perm);
		ft_bzero(perm, BUFFER_SIZE);
		concat(line, buf);
		ft_bzero(buf, BUFFER_SIZE);
		read_value = read(fd, buf, BUFFER_SIZE);
		if (read_value <= 0)
		{
			free(buf);
			free(perm);
			free(*line);
			*line = NULL;
			return (read_value);
		}
	}
	concat(&buf, perm);
	split_at_break(&buf, &perm);
	concat(line, buf);
	free(buf);
	return (1);
}
