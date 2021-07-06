/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmellos <lmellos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 12:02:07 by lmellos           #+#    #+#             */
/*   Updated: 2021/04/10 15:23:39 by lmellos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"

static double	pick_best(t_raytrace *raytrace)
{
	double		closest_t;
	int			i;

	closest_t = 1000000;
	i = -1;
	while (++i < 5)
	{
		if (raytrace[i].c_t < closest_t)
			closest_t = raytrace[i].c_t;
	}
	return (closest_t);
}

static int	ft_check_sh_obj(t_rt *rt, t_vector p_inter, t_vector l)
{
	t_raytrace	raytrace[5];
	double		pick;
	t_ray		check_shadow;

	check_shadow.origin = p_inter;
	check_shadow.dir = l;
	rt->t_max = 1;
	rt->t_min = 0.0025;
	raytrace[0] = sp_shadow_ray(rt, &check_shadow);
	raytrace[1] = plane_shadow_raytrace(rt, &check_shadow);
	raytrace[2] = square_shadow_raytrace(rt, &check_shadow);
	raytrace[3] = triangle_shadow_raytrace(rt, &check_shadow);
	raytrace[4] = cylinder_shadow_raytrace(rt, &check_shadow);
	pick = pick_best(raytrace);
	rt->t_max = RAY_MAX;
	if (pick > 0.0000001 && pick < rt->t_max)
		return (1);
	return (0);
}

t_vector	ft_light_calc(t_argb argb, t_vector light_calc)
{
	if (argb.t_parts.r != 0 && light_calc.x != 0)
		light_calc.x *= (double)argb.t_parts.r / 255;
	else
		light_calc.x = 0;
	if (argb.t_parts.g != 0 && light_calc.y != 0)
		light_calc.y *= (double)argb.t_parts.g / 255;
	else
		light_calc.y = 0;
	if (argb.t_parts.b != 0 && light_calc.z != 0)
		light_calc.z *= (double)argb.t_parts.b / 255;
	else
		light_calc.z = 0;
	return (light_calc);
}

t_vector	ft_l(t_light *l1, double n_dot_l, double l_i, t_vector l_c)
{
	l_i += l1->brightness_ratio * n_dot_l;
	l_c.x += (double)l1->argb.t_parts.r * l_i;
	l_c.y += (double)l1->argb.t_parts.g * l_i;
	l_c.z += (double)l1->argb.t_parts.b * l_i;
	return (l_c);
}

t_vector	ft_add_l(t_argb argb, t_rt *rt, t_vector p_i, t_ray *dir)
{
	t_vector	l;
	double		n_dot_l[2];
	t_list		*light;
	t_light		*light1;
	t_vector	light_calc;

	light = rt->list_light;
	n_dot_l[0] = 0.0;
	light_calc = ft_ambient_calc(rt->ambient->argb, rt->ambient->ratio);
	while (light)
	{
		light1 = light->content;
		if (ft_check_sh_obj(rt, p_i, v_sub(light1->position, p_i)) == 1)
		{
			light = light->next;
			continue ;
		}
		l = v_sub(p_i, light1->position);
		n_dot_l[1] = v_dot(dir->norm, v_norm(l));
		if (n_dot_l[1] < 0)
			n_dot_l[1] = 0;
		light_calc = ft_l(light1, n_dot_l[1], n_dot_l[0], light_calc);
		light = light->next;
	}
	return (ft_light_calc(argb, light_calc));
}
