#include "../includes/minirt.h"

static void	ft_check_split(char **split, size_t count, t_rt *rt)
{
	if (ft_split_length(split) != count)
		ft_crash("Plane is have to be with eight arguments", rt, 2);
}

static void	ft_check_orient(t_object plane, t_rt *rt)
{
	if ((plane.norm.x < -1 || plane.norm.x > 1)
		|| (plane.norm.y < -1 || plane.norm.y > 1)
		|| (plane.norm.z < -1 || plane.norm.z > 1))
		ft_crash("invalid plane orientation", rt, 2);
}

t_object	ft_check_pos_and_orient(char **args, t_rt *rt)
{
	char		**split;
	t_object	plane;

	split = ft_split(args[1], ',');
	if (ft_split_length(args) != 4)
		ft_crash("Plane is have to be with eight arguments", rt, 2);
	ft_check_split(split, 3, rt);
	plane.position.x = ft_atod(split[0], rt);
	plane.position.y = ft_atod(split[1], rt);
	plane.position.z = ft_atod(split[2], rt);
	ft_free_split(split);
	split = ft_split(args[2], ',');
	ft_check_split(split, 3, rt);
	plane.norm.x = ft_atod(split[0], rt);
	plane.norm.y = ft_atod(split[1], rt);
	plane.norm.z = ft_atod(split[2], rt);
	ft_free_split(split);
	return (plane);
}

void	ft_parse_plane(char **args, t_rt *rt)
{
	char		**split;
	t_object	*ret;
	t_object	plane;

	plane = ft_check_pos_and_orient(args, rt);
	ft_check_orient(plane, rt);
	split = ft_split(args[3], ',');
	ft_check_split(split, 3, rt);
	plane.argb.t_parts.a = 0;
	plane.argb.t_parts.r = ft_check_color(ft_atoi(split[0], rt), rt, 255,
			"Plane red color error");
	plane.argb.t_parts.g = ft_check_color(ft_atoi(split[1], rt), rt, 255,
			"Plane green color error");
	plane.argb.t_parts.b = ft_check_color(ft_atoi(split[2], rt), rt, 255,
			"Plane blue color error");
	ft_free_split(split);
	ret = ft_malloc(sizeof(t_object), rt);
	*ret = plane;
	ft_lstadd_back_for_obj(&rt->type_obj, ft_lstnew_for_obj(ret, 2));
}
