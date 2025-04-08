/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_struct_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 09:00:52 by chdonnat          #+#    #+#             */
/*   Updated: 2025/04/08 13:23:46 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_STRUCT_BONUS_H
# define MINIRT_STRUCT_BONUS_H

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_xpm
{
	void	*mlx_ptr;
	int		width;
	int		height;
	void	*img_ptr;
	char	*img_addr;
	int		bpp;
	int		size_line;
	int		endian;
}	t_xpm;

typedef struct s_chd
{
	double		rayon2;
	double		a;
	double		b;
	double		c;
	double		delta;
	double		parametric_distance;
	double		t1;
	double		t2;
	t_vector	oc;
}	t_chd;

typedef struct phong
{
	t_vector	light_dir;
	t_vector	view_dir;
	t_vector	reflect_dir;
	double		ambient;
	double		diffuse;
	double		specular_coef;
	double		intensity;
	t_rgb		rgb;
}	t_phong;

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
	double		reflectivity;
	int			shininess;
	double		u;
	double		v;
}	t_hit;

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
	t_vector		u;
	t_vector		v;
	int				shininess;
	double			reflectivity;
	int				chessboard;
	int				color2;
	int				scale;
	void			*mlx_ptr;
	t_xpm			*xpm;
}	t_plane;

typedef struct s_sphere
{
	t_vector	position;
	double		diameter;
	double		rayon2;
	int			color;
	int			shininess;
	double		reflectivity;
	int			chessboard;
	int			color2;
	int			scale;
	void		*mlx_ptr;
	t_xpm		*xpm;
	double		u;
	double		v;
}	t_sphere;

typedef struct s_cylinder
{
	t_vector	position;
	t_vector	orientation;
	double		diameter;
	double		height;
	int			color;
	int			shininess;
	double		reflectivity;
	int			chessboard;
	int			color2;
	int			scale;
	void		*mlx_ptr;
	t_xpm		*xpm;
	t_vector	u;
	t_vector	v;
}	t_cylinder;

typedef struct s_triangle
{
	t_vector	vertex[3];
	t_vector	face[3];
	int			color;
}	t_triangle;

typedef struct s_cone
{
	t_vector	apex;
	t_vector	axis;
	int			angle;
	double		angle_rad;
	double		height;
	int			color;
	int			shininess;
	double		reflectivity;
	int			chessboard;
	int			color2;
	int			scale;
	void		*mlx_ptr;
	t_xpm		*xpm;
	t_vector	u;
	t_vector	v;
}	t_cone;

typedef struct s_file
{
	t_ambient_light	ambient_light;
	t_camera		camera;
	t_list			**light_list;
	t_dclst			**obj_list;
	void			*mlx_ptr;
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
	t_vector	horizontal;
	t_vector	vertical;
}	t_viewport;

typedef struct s_ray
{
	t_vector	origin;
	t_vector	direction;
	double		distance;
}	t_ray;

typedef struct s_reflection
{
	t_ray		ray;
	t_hit		hit;
	int			local_color;
	int			depth;
}	t_reflection;

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
	CY,
	CO,
	TR
}	t_object;

#endif