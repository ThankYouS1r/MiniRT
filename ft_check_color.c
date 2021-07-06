/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmellos <lmellos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 15:17:38 by lmellos           #+#    #+#             */
/*   Updated: 2021/04/07 15:17:38 by lmellos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"

u_int8_t	ft_check_color(int c, t_rt *rt, int max, const char *error)
{
	if (c < rt->col_min || c > max)
		ft_crash(error, rt, 2);
	return (c);
}
