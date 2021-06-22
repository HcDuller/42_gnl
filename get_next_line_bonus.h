#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>

void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlen(const char *s);
char	*pre_break(char *str);
char	*pos_break(char *str);
int		has_break(char *p);
int		get_next_line(int fd, char **line);

#endif