#include "../includes/minirt.h"

void	*ft_malloc_gnl(size_t size)
{
	size_t		i;
	char		*ret;

	ret = malloc(size);
	if (!ret)
	{
		write(STDERR_FILENO, "Malloc error!", 13);
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

size_t	ft_strlen_gnl(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

void	*ft_memmove_gnl(void *dst, const void *src, size_t len)
{
	char		*a;
	const char	*b;
	size_t		i;

	a = dst;
	b = src;
	i = -1;
	if (dst == src)
		return (dst);
	if (b < a)
	{
		while (len != 0)
		{
			a[len - 1] = b[len - 1];
			len--;
		}
	}
	else
	{
		while (++i != len)
			a[i] = b[i];
	}
	return (a);
}

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	char		*str;
	size_t		max_len;

	if (!s1 && !s2)
		return (0);
	max_len = ft_strlen_gnl(s1) + ft_strlen_gnl(s2);
	str = ft_malloc_gnl(max_len + 1);
	ft_memmove_gnl(str, s1, ft_strlen_gnl(s1));
	ft_memmove_gnl(str + ft_strlen_gnl(s1), s2, ft_strlen_gnl(s2));
	str[max_len] = '\0';
	free((char *)s1);
	return (str);
}

char	*ft_strchr_gnl(const char *s, int c)
{
	size_t		i;
	char		src;

	i = 0;
	src = (char)c;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == src)
			return ((char *)(s + i));
		i++;
	}
	if (src == '\0')
		return ((char *)(s + i));
	return (NULL);
}
