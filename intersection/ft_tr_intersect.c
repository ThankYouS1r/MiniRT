/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tr_intersect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmellos <lmellos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 11:31:02 by lmellos           #+#    #+#             */
/*   Updated: 2021/03/29 14:42:11 by lmellos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

double	ft_check_2(t_vector e1, t_vector e2, t_ray *d, t_object *t)
{
	t_vector	tvec;
	double		determ;
	double		inv_determ;
	double		u;
	double		v;

	determ = v_dot(e1, vector_cross(d->dir, e2));
	if (determ < 1e-8 && determ > -1e-8)
		return (DBL_MAX);
	inv_determ = 1 / determ;
	tvec = v_sub(d->origin, t->pos_f_point);
	u = v_dot(tvec, vector_cross(d->dir, e2)) * inv_determ;
	if (u < 0 || u > 1)
		return (DBL_MAX);
	v = v_dot(d->dir, vector_cross(tvec, e1)) * inv_determ;
	if (v < 0 || u + v > 1)
		return (DBL_MAX);
	return (v_dot(e2, vector_cross(tvec, e1)) * inv_determ);
}

double	ft_tr_intersect(t_ray *d, t_object *triangle)
{
	t_vector	e1;
	t_vector	e2;

	e1 = v_sub(triangle->pos_s_point, triangle->pos_f_point);
	e2 = v_sub(triangle->pos_th_point, triangle->pos_f_point);
	return (ft_check_2(e1, e2, d, triangle));
}
