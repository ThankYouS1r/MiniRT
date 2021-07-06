#include "../includes/minirt.h"

static void	ft_check_split_length(char **args, t_rt *rt)
{
	if (ft_split_length(args) != 4)
		ft_crash("Light is have to be with eight arguments", rt, 2);
}

static void	ft_check_split(char **split, size_t count, t_rt *rt)
{
	if (ft_split_length(split) != count)
		ft_crash("Light is have to be with eight arguments", rt, 2);
}

t_argb	ft_light_argb(char **split, t_rt *rt)
{
	t_object	light;

	light.argb.t_parts.a = 0;
	light.argb.t_parts.r = ft_check_color(ft_atoi(split[0], rt), rt, 255,
			"Light red color error");
	light.argb.t_parts.g = ft_check_color(ft_atoi(split[1], rt), rt, 255,
			"Light green color error");
	light.argb.t_parts.b = ft_check_color(ft_atoi(split[2], rt), rt, 255,
			"Light blue color error");
	return (light.argb);
}

void	ft_parse_light(char **args, t_rt *rt)
{
	char		**split;
	t_light		*ret;
	t_light		light;

	split = ft_split(args[1], ',');
	ft_check_split(split, 3, rt);
	ft_check_split_length(args, rt);
	light.position.x = ft_atod(split[0], rt);
	light.position.y = ft_atod(split[1], rt);
	light.position.z = ft_atod(split[2], rt);
	ft_free_split(split);
	split = ft_split(args[2], ' ');
	ft_check_split(split, 1, rt);
	light.brightness_ratio = ft_atod(split[0], rt);
	if (light.brightness_ratio < 0 || light.brightness_ratio > 1)
		ft_crash("light ratio is not valid", rt, 2);
	ft_free_split(split);
	split = ft_split(args[3], ',');
	ft_check_split(split, 3, rt);
	light.argb = ft_light_argb(split, rt);
	ft_free_split(split);
	ret = ft_malloc(sizeof(t_light), rt);
	*ret = light;
	ft_lstadd_back(&rt->list_light, ft_lstnew(ret));
}
