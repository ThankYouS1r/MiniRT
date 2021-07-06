/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_functions4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmellos <lmellos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 15:03:03 by lmellos           #+#    #+#             */
/*   Updated: 2021/04/10 16:27:46 by lmellos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	ft_check_atoi(const char *str, t_rt *rt)
{
	int	minus;

	minus = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
		{
			++str;
			if (*str == '+')
				ft_crash("invalid config(sign error)", rt, 2);
			minus = -1;
		}
		if (*str == '+')
			++str;
		if (*str == '-' || *str == '+')
			ft_crash("invalid config(sign error)", rt, 2);
	}
	return (minus);
}

const char	*ft_check_sign(const char *str, t_rt *rt)
{
	char	*temp_cut;

	if (*str == '-' || *str == '+')
	{
		while (*str == '-' || *str == '+')
			str++;
	}
	if (ft_strlen(str) > 5)
	{
		temp_cut = ft_sub(str, 0, 5, rt);
		str = ft_strdup(temp_cut);
		free(temp_cut);
		return (str);
	}
	return (ft_strdup(str));
}

int	free_and_ret(void *to_free, int to_ret)
{
	free(to_free);
	return (to_ret);
}

int	ft_atoi(const char *str, t_rt *rt)
{
	long long	n;
	int			minus;
	const char	*temp_str;
	void		*to_free;

	n = 0;
	minus = ft_check_atoi(str, rt);
	temp_str = ft_check_sign(str, rt);
	to_free = (void *)temp_str;
	while (*temp_str)
	{
		if (!(*temp_str >= '0' && *temp_str <= '9'))
			ft_crash("atoi error", rt, 2);
		if (*temp_str >= '0' && *temp_str <= '9')
		{
			if (minus == -1 && (n != ((n * 10 + (*temp_str - '0')) / 10)))
				return (free_and_ret(to_free, 0));
			else if (n != ((n * 10 + (*temp_str - '0')) / 10))
				return (free_and_ret(to_free, -1));
			n = n * 10 + *temp_str - '0';
			temp_str++;
		}
	}
	return (free_and_ret(to_free, (int)n * minus));
}

char	*ft_sub(char const *s, unsigned int st, size_t n, t_rt *rt)
{
	char	*substr;
	size_t	i;

	substr = ft_malloc(n + 1, rt);
	if (s == NULL)
		return (NULL);
	if (ft_strlen(s) < st)
	{
		substr[0] = '\0';
		return (substr);
	}
	i = 0;
	while (s[st] != '\0' && i < n)
	{
		substr[i] = s[st];
		i++;
		s++;
	}
	substr[i] = '\0';
	return (substr);
}
