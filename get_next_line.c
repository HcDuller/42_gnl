/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcduller <hcduller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 15:44:01 by hcduller          #+#    #+#             */
/*   Updated: 2021/06/18 18:49:01 by hcduller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	has_break(char *p)
{
	while (*p)
	{
		if ((unsigned char)*p == '\n')
			return (1);
		p++;
	}
	return (0);
}

char	*str_append(char *base, char *append)
{
	char	*new_str;
	char	*aux;
	char	*freer;

	if (append && base)
	{
		new_str = (char *)ft_calloc(ft_strlen(base) + ft_strlen(append) + 1, 1);
		if (!new_str)
			return (NULL);
		aux = new_str;
		freer = base;
		while (*base)
			*aux++ = *base++;
		while (*append)
			*aux++ = *append++;
		free(freer);
		return (new_str);
	}
	return (base);
}

char	*str_pre_pend(char *base, char *pre)
{
	char	*new_str;
	char	*aux;

	if (base && pre)
	{
		new_str = (char *)ft_calloc(ft_strlen(base) + ft_strlen(pre) + 1, 1);
		if (!new_str)
			return (NULL);
		aux = new_str;
		while (*pre)
			*aux++ = *pre++;
		while (*base)
			*aux++ = *base++;
		free(base);
		return (new_str);
	}
	return (base);
}

char	*pre_break(char *str)
{
	char	*aux;
	char	*new_str;

	aux = str;
	while (*aux && *aux != '\n')
		aux++;
	aux = (char *)ft_calloc((aux - str) + 1, 1);
	new_str = aux;
	if (!aux)
		return (NULL);
	while (*str && *str != '\n')
		*aux++ = *str++;
	return (new_str);
}

char	*pos_break(char *str)
{
	char	*break_index;
	char	*aux;
	char	*new_str;

	break_index = str;
	aux = str;
	new_str = NULL;
	while (*break_index && *break_index != '\n')
		break_index++;
	while (*aux)
		aux++;
	if ((aux - break_index) > 0)
	{
		new_str = (char *)ft_calloc((aux - break_index) + 1, 1);
		aux = new_str;
		while (*++break_index)
			*aux++ = *break_index;
	}
	free(str);
	return (new_str);
}

int	get_next_line(int fd, char **line)
{
	static char	*my_line;
	char		*readings;
	int			r_size;

	if (fd < 0 || !line)
	{
		*line = (NULL);
		return (-1);
	}
	if (!my_line)
		my_line = (char *)ft_calloc(1, 1);
	readings = (char *)ft_calloc(BUFFER_SIZE + 1, 1);
	while (!has_break(my_line))
	{
		r_size = read(fd, readings, BUFFER_SIZE);
		if (r_size == -1)
		{
			*line = NULL;
			free(readings);
			free(my_line);
			return (-1);
		}
		if (r_size == 0 && *my_line == 0)
		{
			*line = str_append(my_line, "");
			my_line = NULL;
			free(readings);
			return (0);
		}
		if (r_size == 0 && !has_break(my_line))
		{
			*line = pre_break(my_line);
			my_line = pos_break(my_line);
			free(readings);
			return (0);
		}
		my_line = str_append(my_line, readings);
		str_clean(readings);
	}
	*line = pre_break(my_line);
	my_line = pos_break(my_line);
	free(readings);
	return (1);
}
