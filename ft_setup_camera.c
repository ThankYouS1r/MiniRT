/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setup_camera.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmellos <lmellos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 09:03:05 by lmellos           #+#    #+#             */
/*   Updated: 2021/04/12 16:27:08 by lmellos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"

static void	rot_x(t_vector *d, const double nb)
{
	double		y;
	double		z;

	y = d->y;
	z = d->z;
	d->y = y * cos(nb) - z * sin(nb);
	d->z = y * sin(nb) + z * cos(nb);
}

static void	rot_y(t_vector *d, const double nb)
{
	double		x;
	double		z;

	x = d->x;
	z = d->z;
	d->x = x * cos(nb) + z * sin(nb);
	d->z = x * -sin(nb) + z * cos(nb);
}

static void	rot_z(t_vector *d, const double nb)
{
	double		x;
	double		y;

	x = d->x;
	y = d->y;
	d->x = x * cos(nb) - y * sin(nb);
	d->y = x * sin(nb) + y * cos(nb);
}

static void	rotation(t_vector *vec, t_vector *rot)
{
	rot->z = 0;
	rot_x(vec, rot->x);
	rot_y(vec, rot->y);
	rot_z(vec, rot->z);
}

t_ray	ft_setup_camera(int x, int y, t_rt *rt)
{
	t_ray		ray;
	t_list		*cum;
	t_camera	*camera;
	t_vector	rot;

	cum = rt->list_camera;
	camera = cum->content;
	ray.origin = camera->position;
	camera->pixel_width = 2 * tan(camera->fov / 2 * M_PI / 180)
		/ rt->res->s_w;
	ray.dir.x = (x - (double)rt->res->s_w / 2)
		* camera->pixel_width;
	ray.dir.y = -(y - (double)rt->res->s_h / 2)
		* camera->pixel_width;
	ray.dir.z = -1;
	rot.x = atan(camera->orientation.y / camera->orientation.z);
	rot.y = atan(camera->orientation.x / camera->orientation.z);
	if (camera->orientation.z == 0 && camera->orientation.x == 0)
		rot.y = atan(camera->orientation.x / 0.00000001);
	if (camera->orientation.z == 0 && camera->orientation.y == 0)
		rot.x = atan(camera->orientation.y / 0.00000001);
	if (camera->orientation.z > 0)
		rot.y += M_PI;
	rotation(&ray.dir, &rot);
	return (ray);
}
