/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_cylinder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmellos <lmellos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 18:06:22 by lmellos           #+#    #+#             */
/*   Updated: 2021/04/10 17:35:37 by lmellos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static void	ft_check_split(char **split, size_t count, t_rt *rt)
{
	if (ft_split_length(split) != count)
		ft_crash("Cylinder is have to be with eight arguments", rt, 2);
}

static void	ft_check(t_object cylinder, t_rt *rt)
{
	if (cylinder.cy_h < 0 || cylinder.diameter < 0)
		ft_crash("Invalid height/diameter cylinder", rt, 2);
	if ((cylinder.norm.x < -1 || cylinder.norm.x > 1)
		|| (cylinder.norm.y < -1 || cylinder.norm.y > 1)
		|| (cylinder.norm.z < -1 || cylinder.norm.z > 1))
		ft_crash("invalid cylinder orientation", rt, 2);
}

t_object	ft_fill_pos_orient(char **args, t_rt *rt)
{
	char		**split;
	t_object	cy;

	split = ft_split(args[1], ',');
	if (ft_split_length(args) != 6)
		ft_crash("Cylinder is have to be with eight arguments", rt, 2);
	ft_check_split(split, 3, rt);
	cy.position.x = ft_atod(split[0], rt);
	cy.position.y = ft_atod(split[1], rt);
	cy.position.z = ft_atod(split[2], rt);
	ft_free_split(split);
	split = ft_split(args[2], ',');
	ft_check_split(split, 3, rt);
	cy.norm.x = ft_atod(split[0], rt);
	cy.norm.y = ft_atod(split[1], rt);
	cy.norm.z = ft_atod(split[2], rt);
	ft_free_split(split);
	return (cy);
}

t_argb	ft_cy_argb(char **split, t_rt *rt)
{
	t_object		cy;

	cy.argb.t_parts.a = 0;
	rt->col_min = 0;
	cy.argb.t_parts.r = ft_check_color(ft_atoi(split[0], rt), rt, 255,
			"Cylinder red color error");
	cy.argb.t_parts.g = ft_check_color(ft_atoi(split[1], rt), rt, 255,
			"Cylinder green color error");
	cy.argb.t_parts.b = ft_check_color(ft_atoi(split[2], rt), rt, 255,
			"Cylinder blue color error");
	return (cy.argb);
}

void	ft_parse_cylinder(char **args, t_rt *rt)
{
	char			**split;
	t_object		*ret;
	t_object		cy;

	cy = ft_fill_pos_orient(args, rt);
	split = ft_split(args[3], ' ');
	ft_check_split(split, 1, rt);
	cy.diameter = ft_atod(split[0], rt);
	ft_free_split(split);
	split = ft_split(args[4], ' ');
	ft_check_split(split, 1, rt);
	cy.cy_h = ft_atod(split[0], rt);
	ft_free_split(split);
	split = ft_split(args[5], ',');
	ft_check_split(split, 3, rt);
	cy.argb = ft_cy_argb(split, rt);
	cy.cc = v_sub(cy.position, vec_mu(cy.norm, cy.cy_h / 2));
	ft_check(cy, rt);
	ft_free_split(split);
	ret = ft_malloc(sizeof(t_object), rt);
	*ret = cy;
	ft_lstadd_back_for_obj(&rt->type_obj, ft_lstnew_for_obj(ret, 4));
}
