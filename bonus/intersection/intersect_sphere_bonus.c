/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 23:37:11 by christophed       #+#    #+#             */
/*   Updated: 2025/04/08 16:19:03 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

static void	get_sphere_uv(t_hit *hit, t_sphere *sphere)
{
	t_vector	local;

	local = sub_vector(hit->point, sphere->position);
	normalize_vector(&local);
	hit->u = (0.5 + atan2(local.z, local.x) / (2.0 * M_PI)) * sphere->scale;
	hit->v = (0.5 - asin(local.y) / M_PI) * sphere->scale;
}

static void	apply_sphere_bump(t_hit *hit, t_sphere *sphere)
{
	double	tex_u;
	double	tex_v;
	int		px;
	int		py;

	if (!sphere->xpm)
		return ;
	tex_u = fmod(fabs(hit->u), 1.0);
	tex_v = fmod(fabs(hit->v), 1.0);
	px = (int)(tex_u * sphere->xpm->width);
	py = (int)(tex_v * sphere->xpm->height);
	if (px >= sphere->xpm->width)
		px = sphere->xpm->width - 1;
	if (py >= sphere->xpm->height)
		py = sphere->xpm->height - 1;
	hit->normal = perturbed_normal(sphere->xpm, px, py, hit->normal);
}

static int	get_sphere_xpm_color(t_sphere *sphere, double u, double v)
{
	int		x;
	int		y;

	u = fmod(fabs(u), 1.0);
	v = fmod(fabs(v), 1.0);
	x = (int)(u * sphere->xpm->width);
	y = (int)(v * sphere->xpm->height);
	if (x >= sphere->xpm->width)
		x = sphere->xpm->width - 1;
	if (y >= sphere->xpm->height)
		y = sphere->xpm->height - 1;
	return (get_pixel_color(sphere->xpm, x, y));
}

static int	get_sphere_chess_color(t_sphere *sphere, double u, double v)
{
	int	x;
	int	y;

	x = (int)(floor(u));
	y = (int)(floor(v));
	if ((x + y) % 2 == 0)
		return (sphere->color);
	else
		return (sphere->color2);
}

int	choose_sp_color(t_sphere *sphere, t_hit *hit)
{
	get_sphere_uv(hit, sphere);
	apply_sphere_bump(hit, sphere);
	if (sphere->xpm)
		return (get_sphere_xpm_color(sphere, hit->u, hit->v));
	else if (sphere->chessboard)
		return (get_sphere_chess_color(sphere, hit->u, hit->v));
	else
		return (sphere->color);
}
