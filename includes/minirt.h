/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmellos <lmellos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 14:42:05 by lmellos           #+#    #+#             */
/*   Updated: 2021/04/10 17:00:05 by lmellos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>
# include <fcntl.h>
# include "../minilibx/mlx.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <float.h>

# define K_ESCAPE	53
# define K_TAB		48
# define RAY_MAX	100000
# define BACKGROUND	0x0

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_res
{
	int				s_w;
	int				s_h;
}					t_res;

typedef union u_argb
{
	struct	s_parts
	{
		uint8_t		b;
		uint8_t		g;
		uint8_t		r;
		uint8_t		a;
	}				t_parts;
	uint32_t		color;
}					t_argb;

typedef struct s_vector
{
	double			x;
	double			y;
	double			z;
}					t_vector;

typedef struct s_ray
{
	t_vector		origin;
	t_vector		dir;
	t_vector		norm;
}					t_ray;

typedef struct s_camera
{
	t_vector		position;
	t_vector		orientation;
	double			fov;
	double			pixel_width;
}					t_camera;

typedef struct s_ambient
{
	double			ratio;
	t_argb			argb;
}					t_ambient;

typedef struct s_light
{
	t_vector		position;
	t_argb			argb;
	double			brightness_ratio;
}					t_light;

typedef struct s_type
{
	void			*content;
	int				id;
	struct s_type	*next;
}					t_type;

typedef struct s_object
{
	t_vector		center;
	t_vector		position;
	t_vector		norm;
	double			side_size;
	double			cy_h;
	t_vector		pos_f_point;
	t_vector		pos_s_point;
	t_vector		pos_th_point;
	t_vector		cc;
	t_argb			argb;
	double			diameter;
	double			radius;
	double			m;
}					t_object;

typedef struct s_math
{
	double			delta;
	double			m;
	double			a;
	double			t1;
	double			t2;
	int				dbl_max;
}					t_math;

typedef struct s_rt
{
	t_res			*res;
	t_ambient		*ambient;
	double			t_min;
	double			t_max;
	double			col_min;
	t_type			*type_obj;
	t_list			*list_camera;
	t_list			*list_light;
	uint32_t		*pixels;
	void			*image;
	void			*mlx;
	void			*window;
	int				p_pix;
	int				endian;
	int				l_length;
}					t_rt;

typedef struct s_raytrace
{
	double			c_t;
	t_argb			argb;
	void			*object;
}					t_raytrace;

/*
** Libft functions
*/

size_t				ft_strlen(const char *s);
char				*ft_sub(char const *s, unsigned int st, size_t n, t_rt *rt);
char				*ft_strdup(const char *s1);
int					ft_atoi(const char *str, t_rt *rt);
int					get_next_line(int fd, char **line);
int					ft_check_atoi(const char *str, t_rt *rt);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
t_vector			ft_vec_normalized(t_vector v);

/*
** Parser functions
*/

u_int8_t			ft_check_color(int c, t_rt *rt, int max, const char *error);
char				**ft_read_config(const char *path);
void				ft_crash(const char *str, t_rt *rt, int i);
void				*ft_malloc(size_t size, t_rt *rt);
size_t				ft_split_length(char **split);
char				*ft_free(char **arr, size_t i);
char				*ft_add_str(char **arr, size_t i, char const *s, char c);
size_t				ft_size(char const *s, char c);
char				**ft_split(const char *s, char c);
int					ft_str_is_empty(const char *str);
void				ft_free_split(char **split);
double				ft_atod(const char *str, t_rt *rt);
t_res				*ft_parse_resolution(char **args, t_rt *rt);
t_ambient			*ft_parse_ambient(char **args, t_rt *rt);
void				ft_parse_camera(char **args, t_rt *rt);
void				ft_parse_light(char **args, t_rt *rt);
double				ft_return_atod(const char *str, int d, double f);
void				ft_parse_sphere(char **args, t_rt *rt);
void				ft_parse_plane(char **args, t_rt *rt);
void				ft_parse_square(char **args, t_rt *rt);
void				ft_parse_cylinder(char **args, t_rt *rt);
void				ft_parse_triangle(char **args, t_rt *rt);

/*
** List functions
*/

t_list				*ft_lstnew(void *content);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_bzero(void *s, size_t n);
t_type				*ft_lstnew_for_obj(void *content, int id);
void				ft_lstadd_back_for_obj(t_type **lst, t_type *new);
void				ft_lstdelone(t_list *lst, void (*del)(void*));

/*
** Raytracing functions
*/

void				ft_exit_program(t_rt *rt, int i);
void				init_rt(char **config, t_rt *rt);
int					ft_button_press(int keycode, t_rt *rt);
void				ft_raytrace(uint32_t *pixels, t_rt *rt);
void				ft_create_bmp_image(t_rt *rt, uint32_t *p);
t_ray				ft_setup_camera(int x, int y, t_rt *rt);
t_raytrace			ft_plane_raytrace(t_rt *rt, t_ray *d);
double				ft_pl_intersect(t_ray *d, t_object *plane);
t_raytrace			ft_square_raytrace(t_rt *rt, t_ray *d);
double				ft_sq_intersect(t_ray *d, t_object *square);
double				ft_tr_intersect(t_ray *d, t_object *triangle);
t_raytrace			ft_triangle_raytrace(t_rt *rt, t_ray *d);
void				ft_sp_intersect(double *res, t_ray *d, t_object *sp);
double				ft_cy_intersect(t_ray *d, t_object *c);
t_raytrace			ft_cylinder_raytrace(t_rt *rt, t_ray *d);
t_raytrace			ft_sp_r(t_rt *rt, t_ray *d, t_type *o, t_raytrace r);
t_raytrace			sp_shadow_ray(t_rt *rt, t_ray *d);
t_raytrace			plane_shadow_raytrace(t_rt *rt, t_ray *d);
t_raytrace			triangle_shadow_raytrace(t_rt *rt, t_ray *d);
t_raytrace			square_shadow_raytrace(t_rt *rt, t_ray *d);
t_raytrace			cylinder_shadow_raytrace(t_rt *rt, t_ray *d);
t_vector			ft_add_l(t_argb argb, t_rt *rt, t_vector p_i, t_ray *dir);
t_vector			ft_ambient_calc(t_argb amb_argb, double amb_ratio);

/*
**Vector functions
*/

double				v_dot(t_vector a, t_vector b);
double				v_len(t_vector v);
t_vector			v_sub(t_vector a, t_vector b);
t_vector			vector_add(t_vector v1, t_vector v2);
t_vector			v_norm(t_vector v);
t_ray				ft_vector_normalized(t_ray v);
t_vector			vector_cross(t_vector v1, t_vector v2);
t_vector			vec_mu(t_vector vec, double n);

#endif
