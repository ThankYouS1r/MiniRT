/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cy_intersect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmellos <lmellos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 18:45:02 by lmellos           #+#    #+#             */
/*   Updated: 2021/04/10 17:10:19 by lmellos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static double	ft_cy(t_ray *d, t_object *cy, t_math math, t_vector oc)
{
	math.m = v_dot(d->dir, cy->norm) * math.t1 + v_dot(oc, cy->norm);
	if (math.m >= 0 && math.m <= cy->cy_h && math.t1 >= 0)
	{
		cy->m = math.m;
		return (math.t1);
	}
	math.m = v_dot(d->dir, cy->norm) * math.t2 + v_dot(oc, cy->norm);
	if (math.m >= 0 && math.m <= cy->cy_h && math.t2 >= 0
		&& (cy->m == 0 || math.t2 < math.t1))
	{
		cy->m = math.m;
		return (math.t2);
	}
	return (DBL_MAX);
}

double	ft_cy_intersect(t_ray *d, t_object *c)
{
	t_vector	oc;
	t_math		math;
	double		k[3];

	c->m = 0.0;
	c->norm = v_norm(c->norm);
	oc = v_sub(d->origin, c->cc);
	k[0] = v_dot(d->dir, d->dir) - (v_dot(d->dir,
				c->norm) * v_dot(d->dir, c->norm));
	k[1] = 2 * (v_dot(d->dir, oc) - (v_dot(d->dir,
					c->norm) * v_dot(oc, c->norm)));
	k[2] = v_dot(oc, oc) - v_dot(oc, c->norm)
		* v_dot(oc, c->norm) - (c->diameter / 2)
		* (c->diameter / 2);
	math.delta = k[1] * k[1] - 4 * k[0] * k[2];
	if (math.delta < 0)
		return (DBL_MAX);
	math.t1 = (-k[1] - sqrt(math.delta)) / (2 * k[0]);
	math.t2 = (-k[1] + sqrt(math.delta)) / (2 * k[0]);
	return (ft_cy(d, c, math, oc));
}
