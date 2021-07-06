/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_functions2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmellos <lmellos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 15:01:55 by lmellos           #+#    #+#             */
/*   Updated: 2021/04/11 15:47:34 by lmellos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	i;
	size_t	max_len;

	i = 0;
	max_len = ft_strlen(s1);
	str = ft_malloc(max_len + 1, NULL);
	while (i < max_len)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

double	ft_return_atod(const char *str, int d, double f)
{
	if (str[0] == '-' && d == 0)
		return (d - f);
	if (d < 0)
		return (d - f);
	return (d + f);
}

double	ft_atod(const char *str, t_rt *rt)
{
	char	**split;
	int		decimal;
	double	fractional;
	int		len;

	split = ft_split(str, '.');
	if (ft_split_length(split) != 2)
	{
		ft_free_split(split);
		if (ft_strlen(str) > 5)
			return (ft_atoi(str, rt));
		return (ft_atoi(str, rt));
	}
	decimal = ft_atoi(split[0], rt);
	fractional = ft_atoi(split[1], rt);
	len = (int)ft_strlen(split[1]);
	if (len > 5)
		len = 5;
	fractional *= pow(10, -len);
	ft_free_split(split);
	return (ft_return_atod(str, decimal, fractional));
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t				nb;
	const unsigned char	*first = (const unsigned char*)s1;
	const unsigned char	*second = (const unsigned char*)s2;

	nb = 0;
	while (nb < n && first[nb] && second[nb])
	{
		if (first[nb] != second[nb])
			return (first[nb] - second[nb]);
		nb++;
	}
	if (nb == n)
		return (0);
	return (first[nb] - second[nb]);
}

size_t	ft_size(char const *s, char c)
{
	size_t	size;

	size = 0;
	while (s[0] != '\0')
	{
		if (s[0] != c)
		{
			while (s[0] != '\0' && s[0] != c)
			{
				if (s[0] == '.' || s[0] == ',')
				{
					++s;
					if (s[0] == '.' || s[0] == ',')
						ft_crash("config error(too many sign)", NULL, 0);
				}
				else
					s++;
			}
			size++;
		}
		else
			s++;
	}
	return (size);
}
