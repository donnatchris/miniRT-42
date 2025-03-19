#ifndef MINIRT_H
# define MINIRT_H

// libraries
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>

// headers
# include "../libft/includes/libft.h"
# include "../minilibx-linux/mlx.h"

// macros
# define DEG_TO_RAD(x) (x * PI / 180)
# define RAD_TO_DEG(x) (x * 180 / PI)

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
	double		fov;
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

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_ambient_light	ambient_light;
	t_camera		camera;
	t_light			light;
}	t_data;

#endif