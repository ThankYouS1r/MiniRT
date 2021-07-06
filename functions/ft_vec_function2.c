#include "../includes/minirt.h"

t_vector	v_norm(t_vector v)
{
	t_vector	norm;
	double		len;

	len = sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
	norm.x = v.x / len;
	norm.y = v.y / len;
	norm.z = v.z / len;
	return (norm);
}

t_vector	vector_add(t_vector v1, t_vector v2)
{
	t_vector	result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return (result);
}

t_vector	vector_cross(t_vector v1, t_vector v2)
{
	t_vector	v;

	v.x = v1.y * v2.z - v1.z * v2.y;
	v.y = v1.z * v2.x - v1.x * v2.z;
	v.z = v1.x * v2.y - v1.y * v2.x;
	return (v);
}

t_vector	ft_ambient_calc(t_argb amb_argb, double amb_ratio)
{
	t_vector	light_calc;

	light_calc.x = (double)amb_argb.t_parts.r * amb_ratio;
	light_calc.y = (double)amb_argb.t_parts.g * amb_ratio;
	light_calc.z = (double)amb_argb.t_parts.b * amb_ratio;
	return (light_calc);
}

t_vector	ft_vec_normalized(t_vector v)
{
	double	len;

	len = sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
	v.x = v.x / len;
	v.y = v.y / len;
	v.z = v.z / len;
	return (v);
}
