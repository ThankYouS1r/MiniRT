#include "includes/minirt.h"

t_raytrace	triangle_shadow_raytrace(t_rt *rt, t_ray *d)
{
	t_type		*objects;
	t_object	*triangle;
	double		result;
	t_raytrace	raytrace;

	objects = rt->type_obj;
	raytrace.c_t = DBL_MAX;
	while (objects)
	{
		if (objects->id == 5)
		{
			triangle = objects->content;
			result = ft_tr_intersect(d, triangle);
			if ((result < raytrace.c_t)
				&& (result > rt->t_min) && result < rt->t_max)
				raytrace.c_t = result;
		}
		objects = objects->next;
	}
	return (raytrace);
}

t_vector	ft_ch_vector_range(t_vector light_intensity)
{
	if (light_intensity.x > 255)
		light_intensity.x = 255;
	if (light_intensity.y > 255)
		light_intensity.y = 255;
	if (light_intensity.z > 255)
		light_intensity.z = 255;
	return (light_intensity);
}

t_raytrace	ft_tr_ray(t_rt *rt, t_object *tr, t_raytrace ray, t_ray *d)
{
	t_vector	p_intersect;
	t_vector	a;
	t_vector	b;
	t_vector	light_intensity;

	if (ray.c_t != DBL_MAX)
	{
		tr = ray.object;
		ray.argb.color = tr->argb.color;
		p_intersect = vector_add(d->origin, vec_mu(d->dir, ray.c_t));
		p_intersect = vector_add(p_intersect, vec_mu(d->norm, 0.002));
		a = v_sub(tr->pos_s_point, tr->pos_f_point);
		b = v_sub(tr->pos_th_point, tr->pos_f_point);
		d->norm = v_norm(vector_cross(a, b));
		if (v_dot(d->norm, v_sub(p_intersect, d->origin)) < 0)
			d->norm = vec_mu(d->norm, -1);
		light_intensity = ft_add_l(ray.argb, rt, p_intersect, d);
		light_intensity = ft_ch_vector_range(light_intensity);
		ray.argb.t_parts.r = (uint8_t)light_intensity.x;
		ray.argb.t_parts.g = (uint8_t)light_intensity.y;
		ray.argb.t_parts.b = (uint8_t)light_intensity.z;
	}
	return (ray);
}

t_raytrace	ft_triangle_raytrace(t_rt *rt, t_ray *d)
{
	t_type		*objects;
	t_object	*triangle;
	double		result;
	t_raytrace	raytrace;

	objects = rt->type_obj;
	raytrace.c_t = DBL_MAX;
	while (objects)
	{
		if (objects->id == 5)
		{
			triangle = objects->content;
			result = ft_tr_intersect(d, triangle);
			result -= 0.0003;
			if ((result < raytrace.c_t)
				&& result > rt->t_min && result < rt->t_max)
			{
				raytrace.c_t = result;
				raytrace.object = triangle;
				return (ft_tr_ray(rt, triangle, raytrace, d));
			}
		}
		objects = objects->next;
	}
	return (ft_tr_ray(rt, triangle, raytrace, d));
}
