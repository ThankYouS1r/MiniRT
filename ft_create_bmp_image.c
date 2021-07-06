#include "includes/minirt.h"

static void	ft_create_bmp_type_data(t_rt *rt, int size, int fd)
{
	unsigned char	*str;
	int				file_size;

	str = ft_malloc(14, rt);
	file_size = 54 + (rt->p_pix / 8 * rt->res->s_w + size) * rt->res->s_h;
	str[0] = (unsigned char)('B');
	str[1] = (unsigned char)('M');
	str[2] = (unsigned char)(file_size);
	str[3] = (unsigned char)(file_size >> 8);
	str[4] = (unsigned char)(file_size >> 16);
	str[5] = (unsigned char)(file_size >> 24);
	str[10] = (unsigned char)(54);
	write(fd, str, 14);
	free(str);
}

static void	ft_create_bmp_info_data(t_rt *rt, int fd)
{
	unsigned char	*str;

	str = ft_malloc(40, rt);
	str[0] = (unsigned char)(40);
	str[4] = (unsigned char)(rt->res->s_w);
	str[5] = (unsigned char)(rt->res->s_w >> 8);
	str[6] = (unsigned char)(rt->res->s_w >> 16);
	str[7] = (unsigned char)(rt->res->s_w >> 24);
	str[8] = (unsigned char)(rt->res->s_h);
	str[9] = (unsigned char)(rt->res->s_h >> 8);
	str[10] = (unsigned char)(rt->res->s_h >> 16);
	str[11] = (unsigned char)(rt->res->s_h >> 24);
	str[12] = (unsigned char)(1);
	str[14] = (unsigned char)(rt->p_pix);
	write(fd, str, 40);
	free(str);
}

void	ft_create_bmp_image(t_rt *rt, uint32_t *p)
{
	int				fd;
	int				size;
	int				i;
	unsigned char	*data;

	fd = open("image.bmp", O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (!fd)
		ft_crash("bmp save error", NULL, 0);
	data = ft_malloc(4, NULL);
	i = rt->res->s_h - 1;
	size = (4 - (rt->res->s_w * rt->p_pix / 8) % 4) % 4;
	ft_create_bmp_type_data(rt, size, fd);
	ft_create_bmp_info_data(rt, fd);
	while (i >= 0)
	{
		write(fd, (char *)p + (i * rt->res->s_w * rt->p_pix / 8), rt->l_length);
		write(fd, data, size);
		i--;
	}
	free(data);
	close(fd);
}
