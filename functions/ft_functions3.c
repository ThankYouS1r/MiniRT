#include "../includes/minirt.h"

void	ft_crash(const char *str, t_rt *rt, int i)
{
	write(2, "\033[31m", 5);
	write(2, str, ft_strlen(str));
	write(2, "\033[0m\n", 5);
	ft_exit_program(rt, i);
}

void	ft_free_split(char **split)
{
	size_t		i;

	if (!split)
		return ;
	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

char	*ft_free(char **arr, size_t i)
{
	while (i > 0)
	{
		free(arr[i]);
		i--;
	}
	free(arr);
	return (0);
}

char	**ft_split(const char *s, char c)
{
	char		**arr;
	size_t		i;

	if (s == NULL)
		return (NULL);
	i = ft_size(s, c);
	arr = ft_malloc((i + 1) * sizeof(char *), NULL);
	arr[i] = 0;
	if (i == 0)
		return (arr);
	i = 0;
	while ((s[0]) != '\0')
	{
		if (s[0] != c)
		{
			s = ft_add_str(arr, i, s, c);
			if (s == 0)
				return (0);
			i++;
		}
		else
			s++;
	}
	return (arr);
}

char	*ft_add_str(char **arr, size_t i,
char const *s, char c)
{
	size_t		j;
	size_t		size;
	char		*tmp;

	size = 0;
	while (s[size] != '\0' && s[size] != c)
		size++;
	tmp = ft_malloc(size + 1, NULL);
	if (tmp == NULL)
		return (ft_free(arr, i));
	arr[i] = tmp;
	j = 0;
	while (j < size)
	{
		tmp[j] = s[j];
		j++;
	}
	tmp[j] = '\0';
	return ((char *)s + size);
}
