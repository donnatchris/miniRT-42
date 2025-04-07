/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 09:03:11 by chdonnat          #+#    #+#             */
/*   Updated: 2025/04/07 16:38:41 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include "../minilibx-linux/mlx.h"
# include "../dclst/dclst.h"
# include "miniRT_struct.h"

// macros
# define WIDTH 1200
# define HEIGHT 800
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

/* ************************************************************************** */
/* 							PARSING                                           */
/* ************************************************************************** */
// parsing_.c
t_file		*parse_input(char *input);
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
// store_cylinder.c
int			store_cylinder(t_file *file, char *line);
// store_plane.c
int			store_plane(t_file *file, char *line);
// store_scene.c
int			store_camera(t_file *file, char *line);
int			store_ambient(t_file *file, char *line);
int			store_light(t_file *file, char *line);
// store_sphere.c
int			store_sphere(t_file *file, char *line);
// store_utils1.c
int			store_angle(int *storage, char *arg, char *line);
int			store_double(double *storage, char *arg, char *line);
int			store_ratio(double *storage, char *arg, char *line);
int			store_color(int *storage, char *arg, char *line);
// store_utils2.c
int			store_vector(t_vector *vector, char *arg, char *line);
int			store_orientation(t_vector *vector, char *arg, char *line);

/* ************************************************************************** */
/* 							VECTOR                                            */
/* ************************************************************************** */

int			solve_quadratic(t_quadratic *q);
int			is_zero_vector(t_vector v);
t_vector	*ray_mul(t_vector *dst, t_ray *r, double t);
// t_vector	reflect_vector(t_vector vector, t_vector nb);
int			phong_lighting(t_hit hit, t_light light, t_program *prog);
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
// color.c
int			scale_color(int color, double factor);
int			mix_colors(int color1, int color2);
int			multiply_colors(int color1, int color2);
int			add_colors(int color1, int color2);
// phong.c
int			phong_lighting(t_hit hit, t_light light, t_program *prog);
// rays.c
t_ray		generate_ray(t_viewport *view, int x, int y);
t_ray		generate_light_ray(t_hit hit, t_light light);
// render.c
void		render(t_program *prog);
// viewport.c
t_viewport	viewport(t_program *prog);
/* ************************************************************************** */
/* 								INTERSECTION                                  */
/* ************************************************************************** */
t_hit		inter_scene(t_ray *ray, t_file *file);
t_hit		inter_plane(t_ray *ray, t_dclst *node);
t_hit		inter_sphere(t_ray *ray, t_dclst *node);
t_hit		inter_cylinder(t_ray *ray, t_dclst *node);
void		init_hit(t_hit *hit, t_dclst *node);
/* ************************************************************************** */
/* 							TEST                                              */
/* ************************************************************************** */
void		print_file(t_file *file);

#endif