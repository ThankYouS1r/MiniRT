#include "../includes/get_next_line.h"

void	ft_crash_gnl(const char *str, char *buff)
{
	write(2, "\033[31m", 5);
	write(2, str, ft_strlen_gnl(str));
	write(2, "\033[0m\n", 5);
	if (buff)
		free(buff);
	exit(EXIT_FAILURE);
}

char	*ft_find_reminder(char *reminder)
{
	char	*src;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!reminder)
		return (0);
	while (reminder[i] != '\0' && reminder[i] != '\n')
		i++;
	if (reminder[i] == '\0')
	{
		free(reminder);
		return (0);
	}
	src = ft_malloc_gnl(ft_strlen_gnl(reminder) - i + 1);
	i++;
	while (reminder[i] != '\0')
		src[j++] = reminder[i++];
	src[j] = '\0';
	free(reminder);
	return (src);
}

char	*text_edit(char *str)
{
	int				i;
	char			*src;
	int				max_len;

	i = 0;
	max_len = 0;
	if (!str)
		return (0);
	while (str[max_len] && str[max_len] != '\n')
		max_len++;
	src = ft_malloc_gnl(max_len + 1);
	while (str[i] != '\0' && str[i] != '\n')
	{
		src[i] = str[i];
		i++;
	}
	src[i] = '\0';
	return (src);
}

int	get_next_line(int fd, char **line)
{
	char			*buff;
	static char		*reminder;
	ssize_t			counter;

	counter = 1;
	if (!line || fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > 1000000)
		ft_crash_gnl("File error", NULL);
	buff = ft_malloc_gnl(BUFFER_SIZE + 1);
	while (!ft_strchr_gnl(reminder, '\n') && counter != 0)
	{
		counter = read(fd, buff, BUFFER_SIZE);
		if (counter < 0)
			ft_crash_gnl("File error", buff);
		buff[counter] = '\0';
		reminder = ft_strjoin_gnl(reminder, buff);
	}
	free(buff);
	*line = text_edit(reminder);
	reminder = ft_find_reminder(reminder);
	if (counter == 0)
		return (0);
	return (1);
}
