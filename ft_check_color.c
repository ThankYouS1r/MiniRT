#include "includes/minirt.h"

u_int8_t	ft_check_color(int c, t_rt *rt, int max, const char *error)
{
	if (c < rt->col_min || c > max)
		ft_crash(error, rt, 2);
	return (c);
}
