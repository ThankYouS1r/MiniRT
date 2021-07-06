/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_plane_raytrace.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmellos <lmellos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 11:16:19 by lmellos           #+#    #+#             */
/*   Updated: 2021/04/10 15:26:50 by lmellos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"

t_raytrace	plane_shadow_raytrace(t_rt *rt, t_ray *d)
{
	t_type		*objects;
	t_object	*plane;
	double		r;
	t_raytrace	raytrace;

	objects = rt->type_obj;
	raytrace.c_t = DBL_MAX;
	while (objects)
	{
		if (objects->id == 2)
		{
			plane = objects->content;
			r = ft_pl_intersect(d, plane);
			if ((r < raytrace.c_t) && r > rt->t_min && r < rt->t_max)
				raytrace.c_t = r;
		}
		objects = objects->next;
	}
	return (raytrace);
}

t_raytrace	ft_pl_trace(t_rt *rt, t_object *pl, t_raytrace ray, t_ray *d)
{
	t_vector	p_inter;
	t_vector	l_intense;

	if (ray.c_t != DBL_MAX)
	{
		pl = ray.object;
		ray.argb.color = pl->argb.color;
		p_inter = vector_add(d->origin, vec_mu(d->dir, ray.c_t));
		p_inter = vector_add(p_inter, vec_mu(d->norm, 0.002));
		d->norm = v_norm(pl->norm);
		if (v_dot(d->norm, v_sub(p_inter, d->origin)) < 0)
			d->norm = vec_mu(d->norm, -1);
		l_intense = ft_add_l(ray.argb, rt, p_inter, d);
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

t_raytrace	ft_plane_raytrace(t_rt *rt, t_ray *d)
{
	t_type		*objects;
	t_object	*plane;
	double		r;
	t_raytrace	raytrace;

	objects = rt->type_obj;
	raytrace.c_t = DBL_MAX;
	while (objects)
	{
		if (objects->id == 2)
		{
			plane = objects->content;
			r = ft_pl_intersect(d, plane);
			if ((r < raytrace.c_t) && r > rt->t_min && r < rt->t_max)
			{
				raytrace.c_t = r;
				raytrace.object = plane;
			}
		}
		objects = objects->next;
	}
	return (ft_pl_trace(rt, plane, raytrace, d));
}
