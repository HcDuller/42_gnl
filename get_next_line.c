/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcduller <hcduller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 15:44:01 by hcduller          #+#    #+#             */
/*   Updated: 2021/06/16 03:22:48 by hcduller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static ssize_t	str_cat(char **s1, char *s2);
static int		reader(char **stack, char **pseudo_buf, int *size, int fd);
static int		piller(char **stack, char **pseudo_buf, ssize_t *size, int fd);
static void		*ft_free(void *ptr);

int	get_next_line(int fd, char **line)
{
	static char		*pseudo_buf;
	static ssize_t	size;

	if (!*line)
		*line = ft_calloc(1, 1);
	if (pseudo_buf)
	{
		return (piller(line, &pseudo_buf, &size, fd));
	}
	else
	{
		return (reader(line, &pseudo_buf, &size, fd));
	}
	return (-1);
}

static	void	*ft_free(void *ptr)
{
	free(ptr);
	return (NULL);
}

static	int	piller(char **stack, char **pseudo_buf, ssize_t *size, int fd)
{
	ssize_t			concat;
	char			*temp;

	concat = str_cat(stack, *pseudo_buf);
	if (concat != -1)
	{
		if (concat == *size)
		{
			*pseudo_buf = ft_free(*pseudo_buf);
			return (get_next_line(fd, stack));
		}
		*size = *size - (concat + 1);
		if (*size > 0)
		{
			temp = ft_substr(*pseudo_buf, concat + 1, *size);
			free(*pseudo_buf);
			*pseudo_buf = temp;
			return (1);
		}
		*pseudo_buf = ft_free(*pseudo_buf);
		return (0);
	}
	*pseudo_buf = ft_free(*pseudo_buf);
	return (-1);
}

static	int	reader(char **stack, char **pseudo_buf, int *size, int fd)
{
	*pseudo_buf = ft_calloc(BUFFER_SIZE + 1, 1);
	if (*pseudo_buf)
	{
		*size = read(fd, *pseudo_buf, BUFFER_SIZE);
		if (*size == -1)
		{
			free(*pseudo_buf);
			return (-1);
		}
		if (*size == 0)
		{
			free(*pseudo_buf);
			return (0);
		}
		return (get_next_line(fd, stack));
	}
	return (-1);
}

static	ssize_t	str_cat(char **s1, char *s2)
{
	ssize_t	cts[3];
	char	*r;

	cts[0] = 0;
	cts[1] = 0;
	cts[2] = 0;
	while ((char)(*s1)[cts[0]])
		cts[0]++;
	while (s2[cts[1]] && cts[1] < BUFFER_SIZE && s2[cts[1]] != '\n')
		cts[1]++;
	r = (char *)ft_calloc(cts[0] + cts[1]-- + 1, 1);
	if (r)
	{
		while (cts[1] >= 0)
		{
			r[cts[0] + cts[1]--] = s2[cts[1]];
			cts[2]++;
		}
		while (cts[0] + cts[1] >= 0)
			r[cts[0]-- + cts[1]] = (*s1)[cts[0] + cts[1]];
		free(*s1);
		*s1 = r;
		return (cts[2]);
	}
	return (-1);
}
