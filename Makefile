NAME		=		miniRT

FUNCTIONS_DIR	=	functions/

DIRS			=	./

LIST		= 	ft_add_light.c						\
				ft_check_color.c					\
				ft_create_bmp_image.c				\
				ft_cylinder_raytrace.c				\
				ft_escape_press.c					\
				ft_init_rt.c						\
				ft_plane_raytrace.c					\
				ft_raytrace.c						\
				main.c								\
				ft_setup_camera.c					\
				ft_sphere_raytrace.c				\
				ft_square_raytrace.c				\
				ft_triangle_raytrace.c				\
				Parser/ft_parse_ambient.c			\
				Parser/ft_parse_camera.c			\
				Parser/ft_parse_cylinder.c			\
				Parser/ft_parse_light.c				\
				Parser/ft_parse_resolution.c		\
				Parser/ft_parse_plane.c				\
				Parser/ft_parse_sphere.c			\
				Parser/ft_parse_square.c			\
				Parser/ft_parse_triangle.c			\
				Parser/ft_read_config.c				\
				Parser/get_next_line.c				\
				intersection/ft_cy_intersect.c		\
				intersection/ft_pl_intersect.c		\
				intersection/ft_sp_intersect.c		\
				intersection/ft_sq_intersect.c		\
				intersection/ft_tr_intersect.c		\
				functions/ft_functions.c			\
				functions/ft_functions2.c			\
				functions/ft_functions3.c			\
				functions/ft_functions4.c			\
				functions/ft_functions5.c			\
				functions/ft_functions_list.c		\
				functions/ft_vec_function.c			\
				functions/ft_vec_function2.c		\
				functions/get_next_line_utils.c		\

SOURCE		=	$(addprefix $(DIRS), $(LIST))

OBJ			=	$(patsubst %.c,%.o,$(SOURCE))
D_FILE		=	$(patsubst %.c,%.d,$(SOURCE))

override D_ALL	?=	$(D_FILE)

override OBJ_ALL	?=	$(OBJ)

INCLUDES  = includes/

MLX = minilibx

MLXFLAGS = -I includes -I $(MLX)

OPENGL	=	-framework OpenGL -framework AppKit

FLAGS	= -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ_ALL)
		@make -C $(MLX)
		gcc $(FLAGS) $(OBJ) $(MLXFLAGS) $(OPENGL) $(MLX)/libmlx.a -o $(NAME) -MMD

clean:
		@rm -f $(OBJ) $(D_FILE)
		@make clean -C $(MLX)

fclean: clean
	@rm -rf $(NAME) libmlx.a image.bmp

re: fclean all

%.o: %.c
	gcc $(FLAGS) -c -I $(INCLUDES) -c $< -o $@ -MMD

include $(wildcard $(D_ALL))

.PHONY: all clean fclean re
