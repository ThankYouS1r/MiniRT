/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_rt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmellos <lmellos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 14:32:07 by lmellos           #+#    #+#             */
/*   Updated: 2021/04/06 15:32:54 by lmellos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"

static void	check_args(char **args, t_rt *rt)
{
	if (args[0][0] == 'R' && !args[0][1] && !rt->res)
		rt->res = ft_parse_resolution(args, rt);
	else if (args[0][0] == 'A' && !args[0][1] && !rt->ambient)
		rt->ambient = ft_parse_ambient(args, rt);
	else if (args[0][0] == 'c' && !args[0][1])
		ft_parse_camera(args, rt);
	else if (args[0][0] == 'l' && !args[0][1])
		ft_parse_light(args, rt);
	else if (args[0][0] == 's' && args[0][1] == 'p' && !args[0][2])
		ft_parse_sphere(args, rt);
	else if (args[0][0] == 'p' && args[0][1] == 'l' && !args[0][2])
		ft_parse_plane(args, rt);
	else if (args[0][0] == 's' && args[0][1] == 'q' && !args[0][2])
		ft_parse_square(args, rt);
	else if (args[0][0] == 'c' && args[0][1] == 'y' && !args[0][2])
		ft_parse_cylinder(args, rt);
	else if (args[0][0] == 't' && args[0][1] == 'r' && !args[0][2])
		ft_parse_triangle(args, rt);
	else
		ft_crash("Invalid config", rt, 2);
}

static void	check_rt(t_rt *rt)
{
	if (rt->res == NULL)
		ft_crash("Resolution is not provided", rt, 2);
	if (rt->ambient == NULL)
		ft_crash("Ambient is not provided", rt, 2);
	if (rt->list_camera == NULL)
		ft_crash("Camera is not provided", rt, 2);
}

void	init_rt(char **config, t_rt *rt)
{
	size_t		i;
	char		**split;

	i = -1;
	while (config[++i])
	{
		split = ft_split(config[i], ' ');
		if (ft_split_length(split) < 3)
			ft_crash("Parse error", rt, 2);
		check_args(split, rt);
		ft_free_split(split);
	}
	check_rt(rt);
}
