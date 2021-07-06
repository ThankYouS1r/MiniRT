#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>

# define BUFFER_SIZE		10

int			get_next_line(int fd, char **line);
size_t		ft_strlen_gnl(const char *s);
char		*ft_strjoin_gnl(char const *s1, char const *s2);
char		*ft_strchr_gnl(const char *s, int c);
void		*ft_malloc_gnl(size_t size);

#endif
