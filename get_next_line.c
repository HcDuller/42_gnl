/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcduller <hcduller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 15:44:01 by hcduller          #+#    #+#             */
/*   Updated: 2021/06/18 05:00:17 by hcduller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


int has_break(char *p)
{
	while(*p)
	{
		if ((unsigned char)*p++ == '\n')
			return (1);
	}
	return (0);
}

char	*str_append_end(char *base, char *append)  //retorna new_malloced concatenades base_apend // da Free em base!
{
	char *new_str;
	char *aux;
	char *freer;

	if(append && base)
	{
			new_str = (char *)ft_calloc(ft_strlen(base) + ft_strlen(append) + 1 ,1);
		if (!new_str)
			return (NULL);
		aux = new_str;
		freer = base;
		while (*base)
			*aux++ = *base++;
		while (*append)
			*aux++ = *append++;
		free(freer);
		freer = NULL;
		return (new_str);
	}
	return (base);
}

char	*str_pre_pend(char *base, char *pre_pen) //retorna new_malloced concatenades prepen_base // da Free em base!
{
	char *new_str;
	char *aux;
	char *freer;

	if(pre_pen)
	{
		new_str = (char *)ft_calloc(ft_strlen(base) + ft_strlen(pre_pen) + 1 ,1);
		if (!new_str)
			return (NULL);
		aux = new_str;
		freer = base;
		while (*pre_pen)
			*aux++ = *pre_pen++;
		while (*base)
			*aux++ = *base++;
		free(freer);
		freer = NULL;
		return (new_str);
	}
	return (base);
}

char	*pre_break(char *str) // retorna new_malloced pre break!
{
	char	*aux;
	char	*new_str;

	aux = str;
	while (*aux && *aux != '\n')
		aux++;
	aux = (char *)ft_calloc((aux - str) + 1 , 1);
	new_str = aux;
	if (!aux)
	 return (NULL);
	while (*str && *str != '\n')
		*aux++ = *str++;
	return (new_str);
}

char	*pos_break(char *str) // retorna new_malloced pos break!
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
	if (aux - break_index == 0)
		return ((char *)ft_calloc(1, 1));
	if((aux - break_index) > 0)
	{
		new_str = (char *)ft_calloc((aux - break_index) + 1, 1);
		aux = new_str;
		while (*++break_index)
			*aux++ = *break_index;	
	}
	return (new_str);
}

int	get_next_line(int fd, char **line)
{
	static char *perm;
	char		*buf;
	char		*my_line;
	int			r_size;
	
	if (fd < 0 || !line)
	{
		if(perm)
			free(perm);
		return(-1);
	}
	//if(!perm)
	//	perm = (char *)ft_calloc(1, 1); validacao da existencia da variavel diretamente em pre / pos apends
	my_line = (char *)ft_calloc(1, 1);
	if(perm)
	{
		my_line = str_pre_pend(my_line, perm);
		free(perm);
		perm = NULL;
	}
	//////// invalid
	if (has_break(my_line))
	{
		buf = pre_break(my_line);
		if(*perm != '\0')
			my_line = str_append_end(my_line, perm);
		perm = pos_break(my_line);
		*line = buf;
		free(my_line);
		if(*perm != '\0')
			return (1);
		return (0);
	}
	/////////
	buf = (char *)ft_calloc(BUFFER_SIZE + 1, 1);
	r_size = 1;
	while (r_size > 0 && !has_break(buf))
	{
		my_line = str_append_end(my_line, buf);
		ft_bzero(buf, BUFFER_SIZE);
		r_size = read(fd, buf, BUFFER_SIZE);
		if (r_size == -1)
		{
			free(buf);
			free(my_line);
			*line = NULL;
			return (-1);
		}
	}
	if(r_size == 0)//ft_strlen(my_line) >= 0 always true
	{
		*line = my_line;
		free(buf);
		return (0);
	}
	//r_size > 0 e has_break!
	perm = pre_break(buf);
	if(*perm != '\0')
		my_line = str_append_end(my_line, perm);
	free(perm);
	perm = pos_break(buf);
	free(buf);
	*line = my_line;
	return (1);
}
