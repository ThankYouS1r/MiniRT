#include "../includes/minirt.h"

double	v_dot(t_vector a, t_vector b)
{
	double	result;

	result = a.x * b.x + a.y * b.y + a.z * b.z;
	return (result);
}

t_vector	vec_mu(t_vector vec, double n)
{
	t_vector	result;

	result.x = vec.x * n;
	result.y = vec.y * n;
	result.z = vec.z * n;
	return (result);
}

double	v_len(t_vector v)
{
	return (sqrt(v.x * v.x + v.y
			* v.y + v.z * v.z));
}

t_vector	v_sub(t_vector a, t_vector b)
{
	a.x -= b.x;
	a.y -= b.y;
	a.z -= b.z;
	return (a);
}

t_ray	ft_vector_normalized(t_ray v)
{
	double	len;

	len = sqrt(pow(v.dir.x, 2) + pow(v.dir.y, 2) + pow(v.dir.z, 2));
	v.dir.x = v.dir.x / len;
	v.dir.y = v.dir.y / len;
	v.dir.z = v.dir.z / len;
	return (v);
}
