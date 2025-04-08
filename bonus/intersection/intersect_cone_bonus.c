/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cone_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 09:21:48 by christophed       #+#    #+#             */
/*   Updated: 2025/04/08 10:44:51 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

void	get_cone_uv(t_hit *hit, t_cone *cone)
{
	t_vector	local;
	t_vector	radial;
	t_vector	height_proj;
	double		height;
	double		theta;

	local = sub_vector(hit->point, cone->apex);
	height = dot_vector(local, cone->axis);
	hit->v = height / cone->height;
	height_proj = mul_vector(cone->axis, height);
	radial = sub_vector(local, height_proj);
	normalize_vector(&radial);
	theta = atan2(dot_vector(radial, cone->v), dot_vector(radial, cone->u));
	hit->u = 0.5 + theta / (2.0 * M_PI);
}

void	apply_cone_bump(t_hit *hit, t_cone *cone)
{
	double		tex_u;
	double		tex_v;
	int			px;
	int			py;

	if (!cone->xpm)
		return ;
	tex_u = fmod(fabs(hit->u), 1.0);
	tex_v = fmod(fabs(hit->v), 1.0);
	px = (int)(tex_u * cone->xpm->width);
	py = (int)(tex_v * cone->xpm->height);
	if (px >= cone->xpm->width)
		px = cone->xpm->width - 1;
	if (py >= cone->xpm->height)
		py = cone->xpm->height - 1;
	hit->normal = perturbed_normal(cone->xpm, px, py, hit->normal);
}

static int	get_cone_xpm_color(t_cone *cone, double u, double v)
{
	int		x;
	int		y;
	double	tex_u;
	double	tex_v;

	tex_u = fmod(fabs(u), 1.0);
	tex_v = fmod(fabs(v), 1.0);
	x = (int)(tex_u * cone->xpm->width);
	y = (int)(tex_v * cone->xpm->height);
	if (x >= cone->xpm->width)
		x = cone->xpm->width - 1;
	if (y >= cone->xpm->height)
		y = cone->xpm->height - 1;
	return (get_pixel_color(cone->xpm, x, y));
}

static int	get_cone_chess_color(t_cone *cone, double u, double v)
{
	int	x;
	int	y;

	x = (int)(floor(u * cone->scale));
	y = (int)(floor(v * cone->scale));
	if ((x + y) % 2 == 0)
		return (cone->color);
	else
		return (cone->color2);
}

int	choose_co_color(t_cone *cone, t_hit *hit)
{
	get_cone_uv(hit, cone);
	apply_cone_bump(hit, cone);
	if (cone->xpm)
		return (get_cone_xpm_color(cone, hit->u, hit->v));
	else if (cone->chessboard)
		return (get_cone_chess_color(cone, hit->u, hit->v));
	else
		return (cone->color);
}
