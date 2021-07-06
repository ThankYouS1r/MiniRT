/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_functions5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmellos <lmellos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 13:13:54 by lmellos           #+#    #+#             */
/*   Updated: 2021/04/07 16:26:22 by lmellos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	free_list_lights(t_rt *rt)
{
	t_list	*list_light1;

	if (rt->list_light)
	{
		while (rt->list_light)
		{
			list_light1 = rt->list_light->next;
			ft_lstdelone(rt->list_light, free);
			rt->list_light = list_light1;
		}
	}
}

void	free_list_cameras(t_rt *rt)
{
	t_list	*cameras1;

	if (rt->list_camera)
	{
		while (rt->list_camera)
		{
			cameras1 = rt->list_camera->next;
			ft_lstdelone(rt->list_camera, free);
			rt->list_camera = cameras1;
		}
	}
}

void	free_list_object(t_rt *rt)
{
	t_type	*list_obj;

	if (rt->type_obj)
	{
		while (rt->type_obj)
		{
			list_obj = rt->type_obj->next;
			free(rt->type_obj);
			rt->type_obj = list_obj;
		}
	}
}

void	ft_exit_program(t_rt *rt, int i)
{
	if (rt && rt->mlx)
	{
		if (rt->image)
			mlx_destroy_image(rt->mlx, rt->image);
	}
	if (!rt)
		exit(EXIT_FAILURE);
	free_list_lights(rt);
	free_list_cameras(rt);
	free_list_object(rt);
	if (i == 1)
		exit(EXIT_SUCCESS);
	if (i == 2 || i == 0)
		exit(EXIT_FAILURE);
}
