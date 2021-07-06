#include "includes/minirt.h"

t_raytrace	sp_shadow_ray(t_rt *rt, t_ray *d)
{
	t_type		*objects;
	t_object	*sphere;
	double		r[2];
	t_raytrace	raytrace;

	objects = rt->type_obj;
	raytrace.c_t = DBL_MAX;
	while (objects)
	{
		if (objects->id == 1)
		{
			sphere = objects->content;
			ft_sp_intersect(r, d, sphere);
			if (r[0] > rt->t_min && r[0] < rt->t_max && (r[0] < raytrace.c_t))
				raytrace.c_t = r[0];
			if (r[1] > rt->t_min & r[1] < rt->t_max && (r[1] < raytrace.c_t))
				raytrace.c_t = r[1];
		}
		objects = objects->next;
	}
	return (raytrace);
}

static t_vector	l_i_range(t_vector l_intense)
{
	if (l_intense.x > 255)
		l_intense.x = 255;
	if (l_intense.y > 255)
		l_intense.y = 255;
	if (l_intense.z > 255)
		l_intense.z = 255;
	return (l_intense);
}

static t_raytrace	ft_sp(t_rt *rt, t_object *sp, t_raytrace ray, t_ray *d)
{
	t_vector	p_intersect;
	t_vector	light_intensity;

	if (ray.c_t != DBL_MAX)
	{
		sp = ray.object;
		ray.argb.color = sp->argb.color;
		p_intersect = vector_add(d->origin, vec_mu(d->dir, ray.c_t));
		p_intersect = vector_add(p_intersect, vec_mu(d->norm, 0.02));
		d->norm = v_norm(
				v_sub(p_intersect, sp->center));
		if (v_dot(d->norm, v_sub(p_intersect, d->origin)) < 0)
			d->norm = vec_mu(d->norm, -1);
		light_intensity = ft_add_l(ray.argb, rt, p_intersect, d);
		light_intensity = l_i_range(light_intensity);
		ray.argb.t_parts.r = (uint8_t)light_intensity.x;
		ray.argb.t_parts.g = (uint8_t)light_intensity.y;
		ray.argb.t_parts.b = (uint8_t)light_intensity.z;
	}
	return (ray);
}

double	ft_ch_sp(t_raytrace r, t_rt *rt, double res, t_ray *d)
{
	if (res > rt->t_min && res < rt->t_max
		&& (res < r.c_t)
		&& (res > v_len(d->dir)))
		return (1);
	return (0);
}

t_raytrace	ft_sp_r(t_rt *rt, t_ray *d, t_type *o, t_raytrace r)
{
	t_object	*sphere;
	double		result[2];

	while (o)
	{
		if (o->id == 1)
		{
			sphere = o->content;
			ft_sp_intersect(result, d, sphere);
			result[0] -= 0.0003;
			result[1] -= 0.0003;
			if (ft_ch_sp(r, rt, result[0], d))
			{
				r.c_t = result[0];
				r.object = sphere;
			}
			if (ft_ch_sp(r, rt, result[1], d))
			{
				r.c_t = result[1];
				r.object = sphere;
			}
		}
		o = o->next;
	}
	return (ft_sp(rt, sphere, r, d));
}
