#include "../includes/minirt.h"

static t_object	ft_check_pos_and_orient(char **args, t_rt *rt)
{
	char			**split;
	t_object		triangle;

	split = ft_split(args[1], ',');
	if (ft_split_length(args) != 5)
		ft_crash("Triangle is have to be with eight arguments", rt, 2);
	triangle.pos_f_point.x = ft_atod(split[0], rt);
	triangle.pos_f_point.y = ft_atod(split[1], rt);
	triangle.pos_f_point.z = ft_atod(split[2], rt);
	ft_free_split(split);
	split = ft_split(args[2], ',');
	if (ft_split_length(args) != 5)
		ft_crash("Triangle is have to be with eight arguments", rt, 2);
	triangle.pos_s_point.x = ft_atod(split[0], rt);
	triangle.pos_s_point.y = ft_atod(split[1], rt);
	triangle.pos_s_point.z = ft_atod(split[2], rt);
	ft_free_split(split);
	return (triangle);
}

void	ft_parse_triangle(char **args, t_rt *rt)
{
	char			**split;
	t_object		*ret;
	t_object		triangle;

	triangle = ft_check_pos_and_orient(args, rt);
	split = ft_split(args[3], ',');
	triangle.pos_th_point.x = ft_atod(split[0], rt);
	triangle.pos_th_point.y = ft_atod(split[1], rt);
	triangle.pos_th_point.z = ft_atod(split[2], rt);
	ft_free_split(split);
	split = ft_split(args[4], ',');
	triangle.argb.t_parts.a = 0;
	triangle.argb.t_parts.r = ft_check_color(ft_atoi(split[0], rt), rt, 255,
			"Triangle red color error");
	triangle.argb.t_parts.g = ft_check_color(ft_atoi(split[1], rt), rt, 255,
			"Triangle red color error");
	triangle.argb.t_parts.b = ft_check_color(ft_atoi(split[2], rt), rt, 255,
			"Triangle red color error");
	ft_free_split(split);
	ret = ft_malloc(sizeof(t_object), rt);
	*ret = triangle;
	ft_lstadd_back_for_obj(&rt->type_obj, ft_lstnew_for_obj(ret, 5));
}
