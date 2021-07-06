#include "../includes/minirt.h"

static int	ft_check_fov_range(t_camera camera, t_rt *rt)
{
	if (camera.fov < 0 || camera.fov > 180)
		ft_crash("invalid fov size", rt, 2);
	return (0);
}

static t_vector	ft_check_range(char **split, t_camera camera, t_rt *rt)
{
	camera.orientation.x = ft_atod(split[0], rt);
	camera.orientation.y = ft_atod(split[1], rt);
	camera.orientation.z = ft_atod(split[2], rt);
	if (camera.orientation.x == 0 && camera.orientation.y == 0
		&& camera.orientation.z == 0)
		ft_crash("Orientation vector error", rt, 2);
	camera.orientation = ft_vec_normalized(camera.orientation);
	if ((camera.orientation.x < -1 || camera.orientation.x > 1)
		|| (camera.orientation.y < -1 || camera.orientation.y > 1)
		|| (camera.orientation.z < -1 || camera.orientation.z > 1))
		ft_crash("error normalized orientation vector range", rt, 2);
	return (camera.orientation);
}

void	ft_check_split(char **split, size_t count, t_rt *rt)
{
	if (ft_split_length(split) != count)
		ft_crash("Camera is have to be with eight arguments", rt, 2);
}

void	ft_parse_camera(char **args, t_rt *rt)
{
	char		**split;
	t_camera	*ret;
	t_camera	camera;

	split = ft_split(args[1], ',');
	if (ft_split_length(args) != 4)
		ft_crash("Camera is have to be with eight arguments", rt, 2);
	ft_check_split(split, 3, rt);
	camera.position.x = ft_atod(split[0], rt);
	camera.position.y = ft_atod(split[1], rt);
	camera.position.z = ft_atod(split[2], rt);
	ft_free_split(split);
	split = ft_split(args[2], ',');
	ft_check_split(split, 3, rt);
	camera.orientation = ft_check_range(split, camera, rt);
	ft_free_split(split);
	split = ft_split(args[3], ' ');
	ft_check_split(split, 1, rt);
	camera.fov = ft_atoi(split[0], rt);
	ft_check_fov_range(camera, rt);
	ft_free_split(split);
	ret = ft_malloc(sizeof(t_camera), rt);
	*ret = camera;
	ft_lstadd_back(&rt->list_camera, ft_lstnew(ret));
}
