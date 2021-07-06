/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_resolution.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmellos <lmellos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 18:44:23 by lmellos           #+#    #+#             */
/*   Updated: 2021/04/07 11:57:57 by lmellos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_res	*ft_parse_resolution(char **args, t_rt *rt)
{
	t_res	*ret;
	t_res	resolution;
	int		width;
	int		height;

	width = 0;
	height = 0;
	if (ft_split_length(args) != 3)
		ft_crash("Resolution is have to be with two arguments", rt, 2);
	resolution.s_w = ft_atoi(args[1], rt);
	if (resolution.s_w < 1)
		ft_crash("invalid resolution size", rt, 2);
	resolution.s_h = ft_atoi(args[2], rt);
	if (resolution.s_h < 1)
		ft_crash("invalid resolution size", rt, 2);
	mlx_get_screen_size(&width, &height);
	if (resolution.s_w > width)
		resolution.s_w = width;
	if (resolution.s_h > height)
		resolution.s_h = height;
	ret = ft_malloc(sizeof(t_res), rt);
	*ret = resolution;
	return (ret);
}
