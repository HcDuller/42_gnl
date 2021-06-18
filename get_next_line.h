#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlen(const char *s);
void	ft_bzero(void *s, size_t n);
void	str_clean(char *s);

int		get_next_line(int fd, char **line);

#endif