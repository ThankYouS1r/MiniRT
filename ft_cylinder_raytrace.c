/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cylinder_raytrace.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmellos <lmellos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 15:55:49 by lmellos           #+#    #+#             */
/*   Updated: 2021/04/10 15:23:39 by lmellos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"

t_raytrace	cylinder_shadow_raytrace(t_rt *rt, t_ray *d)
{
	t_type		*objects;
	t_object	*cylinder;
	t_raytrace	trace;
	double		res;

	objects = rt->type_obj;
	trace.c_t = DBL_MAX;
	while (objects)
	{
		if (objects->id == 4)
		{
			cylinder = objects->content;
			res = ft_cy_intersect(d, cylinder);
			if ((res < trace.c_t) && res > rt->t_min && res < rt->t_max)
				trace.c_t = res;
		}
		objects = objects->next;
	}
	return (trace);
}

t_raytrace	ft_cy_trace(t_rt *rt, t_object *cy, t_raytrace ray, t_ray *dir)
{
	t_vector	p_i;
	t_vector	l_intense;

	if (ray.c_t != DBL_MAX)
	{
		cy = ray.object;
		ray.argb.color = cy->argb.color;
		p_i = vector_add(dir->origin, vec_mu(dir->dir, ray.c_t));
		dir->norm = v_norm(v_sub(v_sub(p_i, cy->cc), vec_mu(cy->norm, cy->m)));
		p_i = vector_add(p_i, vec_mu(dir->norm, 0.00002));
		if (v_dot(dir->norm, v_sub(p_i, dir->origin)) < 0)
			dir->norm = vec_mu(dir->norm, -1);
		l_intense = ft_add_l(ray.argb, rt, p_i, dir);
		if (l_intense.x > 255)
			l_intense.x = 255;
		if (l_intense.y > 255)
			l_intense.y = 255;
		if (l_intense.z > 255)
			l_intense.z = 255;
		ray.argb.t_parts.r = (uint8_t)l_intense.x;
		ray.argb.t_parts.g = (uint8_t)l_intense.y;
		ray.argb.t_parts.b = (uint8_t)l_intense.z;
	}
	return (ray);
}

t_raytrace	ft_cylinder_raytrace(t_rt *rt, t_ray *d)
{
	t_type		*objects;
	t_object	*cylinder;
	t_raytrace	ray;
	double		res;

	objects = rt->type_obj;
	ray.c_t = DBL_MAX;
	while (objects)
	{
		if (objects->id == 4)
		{
			cylinder = objects->content;
			res = ft_cy_intersect(d, cylinder);
			res -= 0.0003;
			if ((res < ray.c_t) && (res > rt->t_min) && res < rt->t_max)
			{
				ray.c_t = res;
				ray.object = cylinder;
			}
		}
		objects = objects->next;
	}
	return (ft_cy_trace(rt, cylinder, ray, d));
}
