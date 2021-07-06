#include "includes/minirt.h"

int	ft_button_press(int keycode, t_rt *rt)
{
	t_list	*list_cam;

	if (keycode == K_ESCAPE)
	{
		mlx_destroy_window(rt->mlx, rt->window);
		ft_exit_program(rt, 1);
	}
	if (keycode == K_TAB)
	{
		if (rt->list_camera->next != NULL)
		{
			list_cam = rt->list_camera->next;
			ft_lstdelone(rt->list_camera, free);
			rt->list_camera = list_cam;
			ft_raytrace(rt->pixels, rt);
			mlx_clear_window(rt->mlx, rt->window);
			mlx_put_image_to_window(rt->mlx, rt->window, rt->image, 0, 0);
		}
	}
	return (0);
}
