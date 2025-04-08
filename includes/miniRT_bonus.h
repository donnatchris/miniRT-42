/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 09:03:11 by chdonnat          #+#    #+#             */
/*   Updated: 2025/04/08 10:42:19 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H

// libraries
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <limits.h>

// headers
# include "../libft/includes/libft.h"
# include "../minilibx-linux/mlx.h"
# include "../dclst/dclst.h"
# include "miniRT_struct_bonus.h"

// macros
# define WIDTH 2120
# define HEIGHT 1080
# define PI 3.141592
# define EPS 1e-6
# define NAME_WINDOWS "miniRT by chdonnat / olthorel"
# define WHITESPACE " \t\r\v\f"

/* ************************************************************************** */
/* 							UTILS                                             */
/* ************************************************************************** */

int			ft_close_windows(t_program *program);
int			ft_key_hook(int keycode, t_program *program);
void		ft_print_error(int exit_code);
int			ft_iscolor(char *str);
int			ft_atoc(char *str);
double		ft_atod(char *str);
int			ft_isdouble(char *str);
int			ft_isint(char *str);
int			ft_isvector(char *str);
size_t		str_array_size(char **array);
// utils_free.c
void		ft_free(void **ptr);
void		delete_str_array(char **array);
void		delete_file(t_file *file);
void		delete_program(t_program *program);
void		delete_xpm(t_xpm *xpm);

/* ************************************************************************** */
/* 								INTERSECTION                                  */
/* ************************************************************************** */

// intersection.c
t_hit		inter_scene(t_ray *ray, t_file *file);
// intersect_cone_bonus.c
void		get_cone_uv(t_hit *hit, t_cone *cone);
void		apply_cone_bump(t_hit *hit, t_cone *cone);
int			choose_co_color(t_cone *cone, t_hit *hit);
// intersect_cone.c
t_hit       inter_cone(t_ray *ray, t_dclst *node);
t_hit		inter_plane(t_ray *ray, t_dclst *node);
t_hit		inter_sphere(t_ray *ray, t_dclst *node);
t_hit		inter_cylinder(t_ray *ray, t_dclst *node);
t_hit		inter_triangle(t_ray *ray, t_dclst *node);
void		init_hit(t_hit *hit, t_dclst *node);

/* ************************************************************************** */
/* 							PARSING                                           */
/* ************************************************************************** */
// parsing_.c
t_file		*parse_input(char *input, void *mlx_ptr);
// parsing_utils1.c
int			is_scene(char *str);
int			is_object(char *str);
int			ft_isvector(char *str);
int			ft_isratio(char *str);
int			ft_isangle(char *str);
// parsing_utils2.c
int			check_input_file(char *input);
char		*next_arg(char *line, size_t *start);
char		*next_and_advance(char *line, size_t *start, char *old_arg);
int			pars_err_msg(char *msg, char *line);
// store_.c
int			store_scene(t_file *file, char *line);
int			store_object(t_file *file, char *line);
// store_cone.c
int	        store_cone(t_file *file, char *line);
// store_cone_bonus.c
int			store_co_bonus(t_cone *cone, char *line, char *arg,
				size_t *start);
// store_cylinder.c
int			store_cylinder(t_file *file, char *line);
// store_cylinder_bonus.c
int			store_cy_bonus(t_cylinder *cylinder, char *line, char *arg,
				size_t *start);
// store_plane.c
int			store_plane(t_file *file, char *line);
// store_plane_bonus.c
int			store_pl_bonus(t_plane *plane, char *line, char *arg,
				size_t *start);
// store_scene.c
int			store_camera(t_file *file, char *line);
int			store_ambient(t_file *file, char *line);
int			store_light(t_file *file, char *line);
// store.sphere
int			store_sphere(t_file *file, char *line);
// store_sphere_bonus.c
int			store_sp_bonus(t_sphere *sphere, char *line, char *arg,
				size_t *start);
// store.triangle
int			store_triangle(t_file *file, char *line);
// store_utils1.c
int			store_angle(int *storage, char *arg, char *line);
int			store_double(double *storage, char *arg, char *line);
int			store_ratio(double *storage, char *arg, char *line);
int			store_color(int *storage, char *arg, char *line);
int			store_scale(int *storage, char *arg, char *line);
// store_utils2.c
int			store_vector(t_vector *vector, char *arg, char *line);
int			store_orientation(t_vector *vector, char *arg, char *line);
void		create_ortho_basis(t_vector normal, t_vector *u, t_vector *v);
// store_xpm.c
void		*xpm_error(char *file);
t_xpm		*store_xpm(char *file, void *mlx_ptr);

/* ************************************************************************** */
/* 								RENDER                                        */
/* ************************************************************************** */

// bump_map.c
int			get_pixel_color(t_xpm *xpm, int x, int y);
t_vector	perturbed_normal(t_xpm *xpm, int u, int v, t_vector normal);
// choose_color.c
int			choose_color_with_depth(t_program *prog, t_ray ray, int depth);
int			choose_color(t_program *prog, int x, int y);
// color_utils.c
int			scale_color(int color, double factor);
int			mix_colors(int color1, int color2, double reflectivity);
int			multiply_colors_scalar(int color1, int color2, double intensity);
int			multiply_colors(int color1, int color2);
int			add_colors(int color1, int color2);
// light.c
int			phong_lighting(t_hit hit, t_light light, t_program *prog);
int			apply_reflection(t_program *prog, t_hit hit, t_ray ray, int local_color, int depth);
int			ambient_lighting(t_hit hit, t_ambient_light ambient);
// rays.c
t_ray		generate_ray(t_viewport *view, int x, int y);
t_ray		generate_light_ray(t_hit hit, t_light light);
// render.c
void		render(t_program *prog);
// viewport.c
t_viewport	viewport(t_program *prog);

/* ************************************************************************** */
/* 							VECTOR                                            */
/* ************************************************************************** */

int			solve_quadratic(t_quadratic *q);
int			is_zero_vector(t_vector v);
t_vector	reflectivity(t_vector incident, t_vector normal);
t_vector	*ray_mul(t_vector *dst, t_ray *r, double t);
int			phong_lighting(t_hit hit, t_light light, t_program *prog);
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
/* 							TEST                                              */
/* ************************************************************************** */
void		print_file(t_file *file);

#endif