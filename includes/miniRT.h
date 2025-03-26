
#ifndef MINIRT_H
# define MINIRT_H

// libraries
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <limits.h>
# include <float.h>

// headers
# include "../libft/includes/libft.h"
# include "../dclst/dclst.h"
# include "../minilibx-linux/mlx.h"

// macros
# define WIDTH 3200
# define HEIGHT 1600
# define PI 3.141592
# define NAME_WINDOWS "miniRT by chdonnat / olthorel"
# define DEG_TO_RAD(x) (x * PI / 180)
# define RAD_TO_DEG(x) (x * 180 / PI)
# define WHITESPACE " \t\r\v\f"

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

typedef struct ambient_light
{
	double	ratio;
	int		color;
}	t_ambient_light;

typedef struct s_camera
{
	t_vector	origin;
	t_vector	direction;
	int			fov;
}	t_camera;

typedef struct s_light
{
	t_vector	position;
	double		ratio;
	int			color;
}	t_light;

typedef struct s_hit
{
	int			hit;
	int			color;
	double		distance;
	t_dclst		*object;
	t_vector	point;
	t_vector	normal;
}	t_hit;

// typedef t_hit (*t_intersect_fn)(t_ray *ray, t_dclst *node);
	// t_intersect_fn	intersect;

typedef struct s_quadratic
{
	double	a;
	double	b;
	double	c;
	double	t1;
	double	t2;
	double	delta;
}	t_quadratic;

typedef struct s_plane
{
	t_vector		position;
	t_vector		normal;
	int				color;
}	t_plane;

typedef struct s_sphere
{
	t_vector	position;
	double		diameter;
	double		rayon2;
	int			color;
}	t_sphere;

typedef struct s_cylinder
{
	t_vector	position;
	t_vector	orientation;
	t_vector	p1;
	t_vector	p2;
	t_vector	delta_p;
	double		diameter;
	double		height;
	double		rayon2;
	int			color;
}	t_cylinder;

typedef struct s_file
{
	t_ambient_light	ambient_light;
	t_camera		camera;
	t_light			light;
	t_dclst			**obj_list;
}	t_file;

typedef struct s_viewport
{
	double		fov;
	double		asp_ratio;
	double		height;
	double		width;
	t_vector	world_up;
	t_vector	forward;
	t_vector	right;
	t_vector	up;
	t_vector	origin;
}	t_viewport;

typedef struct s_ray
{
	t_vector	origin;
	t_vector	direction;
}	t_ray;


typedef struct s_image
{
	void	*img_ptr;
	int		bpp;
	int		size_line;
	int		endian;
	char	*addr;
}	t_image;

typedef struct s_program
{
	void		*mlx;
	void		*win;
	t_image		*img;
	t_file		*file;
	t_viewport	*view;
}	t_program;

typedef enum e_object
{
	PL,
	SP,
	CY
}	t_object;

/* ************************************************************************** */
/* 							UTILS                                             */
/* ************************************************************************** */

int		ft_close_windows(t_program *program);
int		ft_key_hook(int keycode, t_program *program);
void	ft_print_error(int exit_code);
int		ft_iscolor(char *str);
int		ft_atoc(char *str);
double 	ft_atod(char *str);
int		ft_isdouble(char *str);
int		ft_isint(char *str);
int		ft_isvector(char *str);
size_t	str_array_size(char **array);
// utils_free.c
void    ft_free(void **ptr);
void	delete_str_array(char **array);
void	delete_file(t_file *file);
void	delete_program(t_program *program);

/* ************************************************************************** */
/* 							PARSING                                           */
/* ************************************************************************** */
// parsing_.c
t_file	*parse_input(char *input);
// parsing_utils1.c
int		is_scene(char *str);
int		is_object(char *str);
int		ft_isvector(char *str);
int		ft_isorientation(char *str);
int		ft_isratio(char *str);
// parsing_utils2.c
int		ft_isangle(char *str);
int		check_input_file(char *input);
char	*next_arg(char *line, size_t start);
char	*next_and_advance(char *line, size_t *start, char *old_arg);
int		pars_err_msg(char *msg, char *line);
// store_.c
int		store_scene(t_file *file, char *line);
int		store_object(t_file *file, char *line);
// store_cylinder.c
int		store_cylinder(t_file *file, char *line);
// store_plane.c
int		store_plane(t_file *file, char *line);
// store_scene.c
int		store_camera(t_file *file, char *line);
int		store_ambient(t_file *file, char *line);
int		store_light(t_file *file, char *line);
// store_sphere.c
int		store_sphere(t_file *file, char *line);
// store_utils1.c
int		store_angle(int *storage, char *arg, char *line);
int		store_double(double *storage, char *arg, char *line);
int		store_ratio(double *storage, char *arg, char *line);
int		store_color(int *storage, char *arg, char *line);
// store_utils2.c
int		store_vector(t_vector *vector, char *arg, char *line);
int		store_orientation(t_vector *vector, char *arg, char *line);

/* ************************************************************************** */
/* 							VECTOR                                            */
/* ************************************************************************** */

// int			is_inter_scene(t_ray *ray, t_file *file, t_hit *hit);
// int			is_inter_plane(t_ray *ray, t_plane *plane, t_hit *hit);
// int 		is_inter_sphere(t_ray ray, t_sphere sphere, t_hit *hit);
// int			is_infinite_cylinder(t_ray *ray, t_cylinder *cylinder, t_hit *hit);
// int 		is_inter_cylinder(t_ray *ray, t_cylinder *cylinder, t_hit *hit);
int			ft_isvector(char *str);
int			is_quadratic(t_quadratic *q);
int 		is_zero_vector(t_vector v);
t_vector	*ray_mul(t_vector *dst, t_camera *r, double t);
// t_vector	reflect_vector(t_vector vector, t_vector nb);
int	phong_lighting(t_hit hit, t_light light, t_program *prog);
t_vector	refract_vector(t_vector a, t_vector b, double c);
t_vector	vector(double x, double y, double z);
double		len_vector(t_vector v);
t_vector	sub_vector(t_vector a, t_vector b);
t_vector	add_vector(t_vector a, t_vector b);
t_vector	mul_vector(t_vector v, double f);
double		dot_vector(t_vector a, t_vector b);
t_vector	cross_vector(t_vector a, t_vector b);
double		distance_vector(t_vector a, t_vector b);
t_vector	inv_vector(t_vector vector);
void		normalize_vector(t_vector *vector);
/* ************************************************************************** */
/* 								RENDER                                        */
/* ************************************************************************** */
t_viewport	viewport(t_program *prog);
t_ray		generate_ray(t_viewport *view, int x, int y);
t_ray		generate_light_ray(t_hit hit, t_light light);
int			init_img(t_program *prog);
int			scale_color(int color, double factor);
int			lambert_color(t_hit hit, t_light light);
void		render(t_program *prog);
/* ************************************************************************** */
/* 								INTERSECTION                                  */
/* ************************************************************************** */
t_hit		inter_scene(t_ray *ray, t_file *file);
t_hit 		inter_plane(t_ray *ray, t_dclst *node);
t_hit 		inter_sphere(t_ray *ray, t_dclst *node);
t_hit		inter_cylinder(t_ray *ray, t_dclst *node);
void		init_hit(t_hit *hit, t_dclst *node);
/* ************************************************************************** */
/* 							TEST                                              */
/* ************************************************************************** */
void	print_file(t_file *file);

#endif