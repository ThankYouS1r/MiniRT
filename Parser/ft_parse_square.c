/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_square.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmellos <lmellos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 17:19:13 by lmellos           #+#    #+#             */
/*   Updated: 2021/04/10 17:39:31 by lmellos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static void	ft_ch_orient(t_object square, t_rt *rt)
{
	if ((square.norm.x < -1 || square.norm.x > 1)
		|| (square.norm.y < -1 || square.norm.y > 1)
		|| (square.norm.z < -1 || square.norm.z > 1))
		ft_crash("invalid square orientation", rt, 2);
}

static void	ft_check_side_size(t_object square, t_rt *rt)
{
	if (square.side_size < 0)
		ft_crash("invalid square side size", rt, 2);
}

static t_object	ft_check_pos_and_orient(char **args, t_rt *rt)
{
	char			**split;
	t_object		square;

	split = ft_split(args[1], ',');
	if (ft_split_length(args) != 5)
		ft_crash("Square is have to be with eight arguments", rt, 2);
	if (ft_split_length(split) != 3)
		ft_crash("Square is have to be with eight arguments", rt, 2);
	square.position.x = ft_atod(split[0], rt);
	square.position.y = ft_atod(split[1], rt);
	square.position.z = ft_atod(split[2], rt);
	ft_free_split(split);
	split = ft_split(args[2], ',');
	if (ft_split_length(split) != 3)
		ft_crash("Square is have to be with eight arguments", rt, 2);
	square.norm.x = ft_atod(split[0], rt);
	square.norm.y = ft_atod(split[1], rt);
	square.norm.z = ft_atod(split[2], rt);
	ft_free_split(split);
	return (square);
}

void	ft_parse_square(char **args, t_rt *rt)
{
	char			**split;
	t_object		*ret;
	t_object		square;

	square = ft_check_pos_and_orient(args, rt);
	ft_ch_orient(square, rt);
	split = ft_split(args[3], ' ');
	square.side_size = ft_atod(split[0], rt);
	ft_check_side_size(square, rt);
	ft_free_split(split);
	split = ft_split(args[4], ',');
	if (ft_split_length(split) != 3)
		ft_crash("Square is have to be with eight arguments", rt, 2);
	square.argb.t_parts.a = 0;
	square.argb.t_parts.r = ft_check_color(ft_atoi(split[0], rt), rt, 255,
			"Square red color error");
	square.argb.t_parts.g = ft_check_color(ft_atoi(split[1], rt), rt, 255,
			"Square red color error");
	square.argb.t_parts.b = ft_check_color(ft_atoi(split[2], rt), rt, 255,
			"Square red color error");
	ft_free_split(split);
	ret = ft_malloc(sizeof(t_object), rt);
	*ret = square;
	ft_lstadd_back_for_obj(&rt->type_obj, ft_lstnew_for_obj(ret, 3));
}
