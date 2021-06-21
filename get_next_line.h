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
char	*pre_break(char *str);
char	*pos_break(char *str);
int		has_break(char *p);

int		get_next_line(int fd, char **line);

#endif