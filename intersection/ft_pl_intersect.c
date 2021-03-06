#include "../includes/minirt.h"

double	ft_pl_intersect(t_ray *d, t_object *plane)
{
	double		denominator;
	double		t;
	t_vector	positions;

	denominator = v_dot(d->dir, plane->norm);
	if (fabs(denominator) < 0.00001)
		return (DBL_MAX);
	positions = v_sub(plane->position, d->origin);
	t = v_dot(positions, plane->norm) / denominator;
	if (t < 0)
		return (DBL_MAX);
	return (t);
}
