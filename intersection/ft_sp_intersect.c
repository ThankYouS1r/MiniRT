/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sp_intersect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmellos <lmellos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 18:56:37 by lmellos           #+#    #+#             */
/*   Updated: 2021/03/24 18:59:38 by lmellos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	ft_check_discr(double k1, double k2, double k3, double *res)
{
	double		discr;

	discr = k2 * k2 - 4 * k1 * k3;
	if (discr < 0)
	{
		res[0] = DBL_MAX;
		res[1] = DBL_MAX;
	}
	else if (discr * 1000 < 1 && discr * 1000 > -1)
	{
		res[0] = (-k2) / (2 * k1);
		res[1] = DBL_MAX;
	}
	else
	{
		res[0] = (-k2 + sqrt(discr)) / (2 * k1);
		res[1] = (-k2 - sqrt(discr)) / (2 * k1);
	}
}

void	ft_sp_intersect(double *res, t_ray *d, t_object *sp)
{
	t_vector	center;
	t_vector	oc;
	double		k[3];

	center = sp->center;
	oc = v_sub(d->origin, center);
	k[0] = v_dot(d->dir, d->dir);
	k[1] = 2 * v_dot(oc, d->dir);
	k[2] = v_dot(oc, oc) - sp->radius * sp->radius;
	ft_check_discr(k[0], k[1], k[2], res);
}
