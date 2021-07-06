#include "includes/minirt.h"

int	pick_best(t_raytrace *raytrace)
{
	double		closest_t;
	int			i;
	int			ret;

	closest_t = DBL_MAX;
	i = -1;
	while (++i < 5)
	{
		if (raytrace[i].c_t < closest_t)
		{
			closest_t = raytrace[i].c_t;
			ret = i;
		}
	}
	if (closest_t == DBL_MAX)
		return (-1);
	return (ret);
}

u_int32_t	ft_check_intersect_objects(t_rt *rt, t_ray *d)
{
	t_raytrace	raytrace[5];
	int			pick;
	t_raytrace	raytrace1;
	t_type		*obj;

	rt->t_min = 0.0001;
	rt->t_max = RAY_MAX;
	obj = rt->type_obj;
	raytrace1.c_t = DBL_MAX;
	raytrace[0] = ft_sp_r(rt, d, obj, raytrace1);
	raytrace[1] = ft_plane_raytrace(rt, d);
	raytrace[2] = ft_square_raytrace(rt, d);
	raytrace[3] = ft_triangle_raytrace(rt, d);
	raytrace[4] = ft_cylinder_raytrace(rt, d);
	pick = pick_best(raytrace);
	if (pick == -1)
		return (BACKGROUND);
	return (raytrace[pick].argb.color);
}

void	ft_raytrace(uint32_t *pixels, t_rt *rt)
{
	int			x;
	int			y;
	t_ray		dir;
	u_int32_t	color;

	x = 0;
	while (x < rt->res->s_w)
	{
		y = 0;
		while (y < rt->res->s_h)
		{
			dir = ft_vector_normalized(ft_setup_camera(x, y, rt));
			color = ft_check_intersect_objects(rt, &dir);
			pixels[rt->res->s_w * y + x] = color;
			y++;
		}
		x++;
	}
}
