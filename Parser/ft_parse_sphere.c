#include "../includes/minirt.h"

static void	ft_check_split(char **split, size_t count, t_rt *rt)
{
	if (ft_split_length(split) != count)
		ft_crash("Sphere is have to be with eight arguments", rt, 2);
}

static void	ft_check_diameter(t_object sphere, t_rt *rt)
{
	if (sphere.diameter < 0)
		ft_crash("invalid sphere diameter size", rt, 2);
}

static t_object	ft_check_pos_and_orient1(char **args, t_rt *rt)
{
	char			**split;
	t_object		sphere;

	if (ft_split_length(args) != 4)
		ft_crash("Sphere is have to be with five arguments", rt, 2);
	split = ft_split(args[1], ',');
	ft_check_split(split, 3, rt);
	sphere.center.x = ft_atod(split[0], rt);
	sphere.center.y = ft_atod(split[1], rt);
	sphere.center.z = ft_atod(split[2], rt);
	ft_free_split(split);
	split = ft_split(args[2], ',');
	ft_free_split(split);
	return (sphere);
}

void	ft_parse_sphere(char **args, t_rt *rt)
{
	char			**split;
	t_object		*ret;
	t_object		sp_o;

	sp_o = ft_check_pos_and_orient1(args, rt);
	split = ft_split(args[2], ' ');
	ft_check_split(split, 1, rt);
	sp_o.diameter = ft_atod(split[0], rt);
	ft_check_diameter(sp_o, rt);
	ft_free_split(split);
	split = ft_split(args[3], ',');
	ft_check_split(split, 3, rt);
	sp_o.radius = sp_o.diameter / 2;
	sp_o.argb.t_parts.a = 0;
	sp_o.argb.t_parts.r = ft_check_color(ft_atoi(split[0], rt), rt, 255,
			"Sphere red color error");
	sp_o.argb.t_parts.g = ft_check_color(ft_atoi(split[1], rt), rt, 255,
			"Sphere green color error");
	sp_o.argb.t_parts.b = ft_check_color(ft_atoi(split[2], rt), rt, 255,
			"Sphere blue color error");
	ft_free_split(split);
	ret = ft_malloc(sizeof(t_object), rt);
	*ret = sp_o;
	ft_lstadd_back_for_obj(&rt->type_obj, ft_lstnew_for_obj(ret, 1));
}
