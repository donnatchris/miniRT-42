
#ifndef MINIRT_H
# define MINIRT_H

// libraries
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <limits.h>

// headers
# include "../libft/includes/libft.h"
# include "../dclst/dclst.h"
# include "../minilibx-linux/mlx.h"

// macros
# define WIDTH 800
# define HEIGHT 600
# define NAME_WINDOWS "miniRT by chdonnat / olthorel"
# define DEG_TO_RAD(x) (x * PI / 180)
# define RAD_TO_DEG(x) (x * 180 / PI)
# define WHITESPACE " \t\n\r\v\f"

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

typedef struct s_plane
{
	t_vector	position;
	t_vector	normal;
	int			color;
}	t_plane;

typedef struct s_sphere
{
	t_vector	position;
	double		diameter;
	int			color;
}	t_sphere;

typedef struct s_cylinder
{
	t_vector	position;
	t_vector	normal;
	double		diameter;
	double		height;
	int			color;
}	t_cylinder;

typedef struct s_file
{
	t_ambient_light	ambient_light;
	t_camera		camera;
	t_light			light;
	t_dclst			**obj_list;
}	t_file;

typedef struct s_program
{
	void	*mlx;
	void	*win;
	t_file	*file;
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
void    ft_free(void *ptr);
int		ft_iscolor(char *str);
int		ft_atoc(char *str);
double 	ft_atod(char *str);
int		ft_isdouble(char *str);
int		ft_isint(char *str);
void	delete_str_array(char **array);
size_t	str_array_size(char **array);

/* ************************************************************************** */
/* 							PARSING                                           */
/* ************************************************************************** */

t_file	*parse_input(char *input);
int 	store_scene(t_file *file, char *line);
int		store_sphere(t_file *file, char *line);
int		store_plane(t_file *file, char *line);
int		store_cylinder(t_file *file, char *line);
// parsing_utils.c
char	*next_arg(char *line, size_t start);
int		ft_isorientation(char *str);
int		ft_isratio(char *str);
int		ft_isangle(char *str);

/* ************************************************************************** */
/* 							VECTOR                                            */
/* ************************************************************************** */

int			is_inter_sphere(t_camera ray, t_sphere sphere, double *t);
int			is_inter_cylinder(t_camera ray, t_cylinder cylinder, double *t);
int			is_inter_plane(t_camera ray, t_plane plane, double *t);
int			ft_isvector(char *str);
int			store_vector(t_vector *vector, char *arg);
t_vector	reflect_vector(t_vector vector, t_vector nb);
t_vector	refract_vector(t_vector a, t_vector b, double c);
t_vector	vector(double x, double y, double z);
double		len_vector(t_vector v);
t_vector	sub_vector(t_vector a, t_vector b);
t_vector	add_vector(t_vector a, t_vector b);
t_vector	scale_vector(t_vector a, double scale);
double		dot_vector(t_vector a, t_vector b);
t_vector	cross_vector(t_vector a, t_vector b);
double		distance_vector(t_vector a, t_vector b);
t_vector	inv_vector(t_vector vector);
void		normalize_vector(t_vector *vector);

/* ************************************************************************** */
/* 							TEST                                              */
/* ************************************************************************** */
void	print_file(t_file *file);

#endif