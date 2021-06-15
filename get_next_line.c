/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcduller <hcduller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 15:44:01 by hcduller          #+#    #+#             */
/*   Updated: 2021/06/15 19:44:38 by hcduller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static ssize_t	charat(char *str, char c);
static ssize_t	str_cat(char **s1, char *s2);
static int		stacker(int fd, char **stack);

int	get_next_line(int fd, char **line)
{
	if (!*line)
		*line = ft_calloc(1, 1);
	return (stacker(fd, line));
}

static	int	stacker(int fd, char **stack)
{
	static char		*pseudo_buf;
	static ssize_t	size;
	ssize_t			concat;
	char			*temp;

	if (!*stack)
		ft_calloc(1, 1);
	if (pseudo_buf)
	{
		concat = str_cat(stack, pseudo_buf);
		if (concat == -1)
		{
			free(pseudo_buf);
			return (-1);
		}
		if (concat == size)
		{
			free(pseudo_buf);
			pseudo_buf = NULL;
			return (stacker(fd, stack));
		}
		if (concat < size)
		{
			size = size - concat - 1;
			if (size > 0)
			{
				temp = ft_substr(pseudo_buf, concat + 1, size);
				free(pseudo_buf);
				pseudo_buf = temp;
				return (1);
			}
			free(pseudo_buf);
			pseudo_buf = NULL;
			return (1);
		}
	}
	else
	{
		pseudo_buf = ft_calloc(BUFFER_SIZE + 1, 1);
		if (pseudo_buf)
		{
			size = read(fd, pseudo_buf, BUFFER_SIZE);
			if (size == -1)
			{
				free(pseudo_buf);
				return (-1);
			}
			if (size == 0)
			{
				free(pseudo_buf);
				return (0);
			}
			return (stacker(fd, stack));
		}
	}
	return (-1);
}

static	ssize_t	str_cat(char **s1, char *s2)
{
	ssize_t	l1;
	ssize_t	l2;
	ssize_t	added;
	char	*r;

	l1 = 0;
	l2 = 0;
	added = 0;
	while ((char)(*s1)[l1])
		l1++;
	while (s2[l2] && l2 < BUFFER_SIZE && s2[l2] != '\n')
		l2++;
	r = (char *)ft_calloc(l1 + l2 + 1, 1);
	if (r)
	{
		l2--;
		while (l2 >= 0)
		{
			r[l1 + l2] = s2[l2];
			l2--;
			added++;
		}
		while (l1 + l2 >= 0)
		{
			r[l1 + l2] = (*s1)[l1 + l2];
			l1--;
		}
		free(*s1);
		*s1 = r;
		return (added);
	}
	return (-1);
}

static	ssize_t	charat(char *str, char c)
{
	ssize_t	i;

	i = 0;
	while (i < BUFFER_SIZE + 1 && str[i])
	{
		if ((unsigned char)str[i] == (unsigned char)c)
			return (i);
		i++;
	}
	return (-1);
}
