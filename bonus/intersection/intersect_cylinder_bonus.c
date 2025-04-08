/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 10:57:38 by christophed       #+#    #+#             */
/*   Updated: 2025/04/08 10:58:49 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

static void	get_cylinder_uv(t_hit *hit, t_cylinder *cyl)
{
	t_vector	local;
	t_vector	height_proj;
	t_vector	radial;
	double		height;
	double		theta;

	local = sub_vector(hit->point, cyl->position);
	height = dot_vector(local, cyl->orientation);
	hit->v = height / cyl->height;
	height_proj = mul_vector(cyl->orientation, height);
	radial = sub_vector(local, height_proj);
	normalize_vector(&radial);
	theta = atan2(dot_vector(radial, cyl->v), dot_vector(radial, cyl->u));
	hit->u = 0.5 + theta / (2.0 * M_PI);
}

static void	apply_cylinder_bump(t_hit *hit, t_cylinder *cyl)
{
	double		tex_u;
	double		tex_v;
	int			px;
	int			py;

	if (!cyl->xpm)
		return ;
	tex_u = fmod(fabs(hit->u), 1.0);
	tex_v = fmod(fabs(hit->v), 1.0);
	px = (int)(tex_u * cyl->xpm->width);
	py = (int)(tex_v * cyl->xpm->height);
	if (px >= cyl->xpm->width)
		px = cyl->xpm->width - 1;
	if (py >= cyl->xpm->height)
		py = cyl->xpm->height - 1;
	hit->normal = perturbed_normal(cyl->xpm, px, py, hit->normal);
}

static int	get_cylinder_xpm_color(t_cylinder *cyl, double u, double v)
{
	int		x;
	int		y;
	double	tex_u;
	double	tex_v;

	tex_u = fmod(fabs(u), 1.0);
	tex_v = fmod(fabs(v), 1.0);
	x = (int)(tex_u * cyl->xpm->width);
	y = (int)(tex_v * cyl->xpm->height);
	if (x >= cyl->xpm->width)
		x = cyl->xpm->width - 1;
	if (y >= cyl->xpm->height)
		y = cyl->xpm->height - 1;
	return (get_pixel_color(cyl->xpm, x, y));
}

static int	get_cylinder_chess_color(t_cylinder *cyl, double u, double v)
{
	int	x;
	int	y;

	x = (int)(floor(u * cyl->scale));
	y = (int)(floor(v * cyl->scale));
	if ((x + y) % 2 == 0)
		return (cyl->color);
	else
		return (cyl->color2);
}

int	choose_cy_color(t_cylinder *cyl, t_hit *hit)
{
	get_cylinder_uv(hit, cyl);
	apply_cylinder_bump(hit, cyl);
	if (cyl->xpm)
		return (get_cylinder_xpm_color(cyl, hit->u, hit->v));
	else if (cyl->chessboard)
		return (get_cylinder_chess_color(cyl, hit->u, hit->v));
	else
		return (cyl->color);
}
