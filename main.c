/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmellos <lmellos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 15:22:45 by lmellos           #+#    #+#             */
/*   Updated: 2021/04/10 15:40:08 by lmellos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"

static int	close_program(t_rt *rt)
{
	ft_exit_program(rt, 1);
	exit(0);
}

void	init_mlx(t_rt *rt)
{
	rt->mlx = mlx_init();
	if (!rt->mlx)
		ft_crash("init error", rt, 2);
	rt->window = mlx_new_window(rt->mlx, rt->res->s_w, rt->res->s_h, "miniRT");
	rt->image = mlx_new_image(rt->mlx, rt->res->s_w, rt->res->s_h);
	rt->pixels = (uint32_t *)mlx_get_data_addr(rt->image, &rt->p_pix,
			&rt->l_length, &rt->endian);
	mlx_hook(rt->window, 2, 0, ft_button_press, rt);
	mlx_hook(rt->window, 17, 1, close_program, rt);
}

int	main(int ac, char *av[])
{
	char	**config;
	t_rt	rt;

	ft_bzero(&rt, sizeof(t_rt));
	if (ac < 2 || ac > 3)
		ft_crash("arg error", NULL, 2);
	if (ac == 3 && ft_strncmp(av[2], "--save", 7))
		ft_crash("arg error", NULL, 2);
	config = ft_read_config(av[1]);
	init_rt(config, &rt);
	init_mlx(&rt);
	ft_raytrace(rt.pixels, &rt);
	if (ac == 3)
		ft_create_bmp_image(&rt, rt.pixels);
	else
	{
		mlx_clear_window(rt.mlx, rt.window);
		mlx_put_image_to_window(rt.mlx, rt.window, rt.image, 0, 0);
		mlx_loop(rt.mlx);
	}
	ft_exit_program(&rt, 1);
}
