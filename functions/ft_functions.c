#include "../includes/minirt.h"

size_t	ft_strlen(const char *str)
{
	int		i;

	i = 0;
	while (*str)
	{
		i++;
		str++;
	}
	return (i);
}

void	*ft_malloc(size_t size, t_rt *rt)
{
	size_t	i;
	char	*ret;

	ret = malloc(size);
	if (!ret)
	{
		ft_crash("malloc error", rt, 2);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < size)
	{
		ret[i] = '\0';
		i++;
	}
	return ((void *)ret);
}

int	ft_str_is_empty(const char *str)
{
	size_t	i;
	char	c;

	if (!str)
		return (0);
	i = -1;
	while (str[++i])
	{
		c = str[i];
		if (!(c >= 9 && c <= 13) || c == ' ')
			return (0);
	}
	return (1);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*memory;

	i = 0;
	memory = s;
	while (i < n)
	{
		memory[i] = 0;
		i++;
	}
}

size_t	ft_split_length(char **split)
{
	size_t	i;

	if (!split)
		return (0);
	i = -1;
	while (split[++i])
		;
	return (i);
}
