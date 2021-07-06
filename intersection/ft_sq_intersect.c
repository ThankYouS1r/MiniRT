/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sq_intersect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmellos <lmellos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 11:30:05 by lmellos           #+#    #+#             */
/*   Updated: 2021/03/25 11:30:05 by lmellos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

double	ft_sq_intersect(t_ray *d, t_object *square)
{
	double		denominator;
	t_vector	p_intersect;
	t_vector	positions;
	double		t;

	denominator = v_dot(d->dir, square->norm);
	if (fabs(denominator) <= 0.000001)
		return (DBL_MAX);
	positions = v_sub(square->position, d->origin);
	t = v_dot(positions, square->norm) / denominator;
	p_intersect = vector_add(d->origin, vec_mu(d->dir, t));
	if (fabs(p_intersect.x - square->position.x) > (square->side_size / 2))
		return (DBL_MAX);
	if (fabs(p_intersect.y - square->position.y) > (square->side_size / 2))
		return (DBL_MAX);
	if (fabs(p_intersect.z - square->position.z) > (square->side_size / 2))
		return (DBL_MAX);
	return (t);
}
