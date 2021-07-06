/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_ambient.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmellos <lmellos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 18:45:21 by lmellos           #+#    #+#             */
/*   Updated: 2021/04/10 17:23:40 by lmellos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static void	ft_check_range_argb(t_ambient *ambient, t_rt *rt)
{
	if ((ambient->argb.t_parts.r < 0 || ambient->argb.t_parts.r > 255)
		|| (ambient->argb.t_parts.g < 0 || ambient->argb.t_parts.g > 255)
		|| (ambient->argb.t_parts.b < 0 || ambient->argb.t_parts.b > 255))
		ft_crash("Wrong ambient color", rt, 2);
}

t_ambient	*ft_parse_ambient(char **args, t_rt *rt)
{
	char		**split;
	t_ambient	*ret;
	t_ambient	ambient;

	if (ft_split_length(args) != 3)
		ft_crash("Ambient is have to be with five arguments", rt, 2);
	ambient.ratio = ft_atod(args[1], rt);
	if (ambient.ratio < 0 || ambient.ratio > 1)
		ft_crash("invalid ambient ratio", rt, 2);
	split = ft_split(args[2], ',');
	if (ft_split_length(split) != 3)
		ft_crash("Ambient is have to be with five arguments", rt, 2);
	ambient.argb.t_parts.a = 0;
	ambient.argb.t_parts.r = ft_check_color(ft_atoi(split[0], rt), rt, 255,
			"Ambient red color error");
	ambient.argb.t_parts.g = ft_check_color(ft_atoi(split[1], rt), rt, 255,
			"Ambient green color error");
	ambient.argb.t_parts.b = ft_check_color(ft_atoi(split[2], rt), rt, 255,
			"Ambient blue color error");
	ft_free_split(split);
	ft_check_range_argb(&ambient, rt);
	ret = ft_malloc(sizeof(t_ambient), rt);
	*ret = ambient;
	return (ret);
}
