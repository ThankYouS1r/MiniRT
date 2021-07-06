#include "includes/minirt.h"

t_raytrace	square_shadow_raytrace(t_rt *rt, t_ray *d)
{
	t_type		*objects;
	t_object	*square;
	double		res;
	t_raytrace	raytrace;

	objects = rt->type_obj;
	raytrace.c_t = DBL_MAX;
	while (objects)
	{
		if (objects->id == 3)
		{
			square = objects->content;
			res = ft_sq_intersect(d, square);
			if ((res < raytrace.c_t) && res > rt->t_min && res < rt->t_max)
				raytrace.c_t = res;
		}
		objects = objects->next;
	}
	return (raytrace);
}

t_raytrace	ft_sq(t_rt *rt, t_object *sq, t_raytrace ray, t_ray *d)
{
	t_vector	p_intersect;
	t_vector	light_intensity;

	if (ray.c_t != DBL_MAX)
	{
		sq = ray.object;
		ray.argb.color = sq->argb.color;
		p_intersect = vector_add(d->origin, vec_mu(d->dir, ray.c_t));
		p_intersect = vector_add(p_intersect, vec_mu(d->norm, 0.002));
		d->norm = v_norm(sq->norm);
		if (v_dot(d->norm, v_sub(p_intersect, d->origin)) < 0)
			d->norm = vec_mu(d->norm, -1);
		light_intensity = ft_add_l(ray.argb, rt, p_intersect, d);
		if (light_intensity.x > 255)
			light_intensity.x = 255;
		if (light_intensity.y > 255)
			light_intensity.y = 255;
		if (light_intensity.z > 255)
			light_intensity.z = 255;
		ray.argb.t_parts.r = (uint8_t)light_intensity.x;
		ray.argb.t_parts.g = (uint8_t)light_intensity.y;
		ray.argb.t_parts.b = (uint8_t)light_intensity.z;
	}
	return (ray);
}

t_raytrace	ft_square_raytrace(t_rt *rt, t_ray *d)
{
	t_type		*objects;
	t_object	*square;
	double		result;
	t_raytrace	raytrace;

	objects = rt->type_obj;
	raytrace.c_t = DBL_MAX;
	while (objects)
	{
		if (objects->id == 3)
		{
			square = objects->content;
			result = ft_sq_intersect(d, square) - 0.0003;
			if ((result < raytrace.c_t) && (result > v_len(d->dir))
				&& (result > rt->t_min) && (result < rt->t_max)
				&& (result < raytrace.c_t))
			{
				raytrace.c_t = result;
				raytrace.object = square;
			}
		}
		objects = objects->next;
	}
	return (ft_sq(rt, square, raytrace, d));
}
