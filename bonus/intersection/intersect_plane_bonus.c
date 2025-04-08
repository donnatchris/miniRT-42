/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 23:54:13 by christophed       #+#    #+#             */
/*   Updated: 2025/04/08 15:57:15 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

static void	get_plane_uv(t_hit *hit, t_plane *plane)
{
	t_vector	local;

	local = sub_vector(hit->point, plane->position);
	hit->u = dot_vector(local, plane->u) * plane->scale;
	hit->v = dot_vector(local, plane->v) * plane->scale;
}

static void	apply_plane_bump(t_hit *hit, t_plane *plane)
{
	double	tex_u;
	double	tex_v;
	int		px;
	int		py;

	if (!plane->xpm)
		return ;
	tex_u = fmod(fabs(hit->u), 1.0);
	tex_v = fmod(fabs(hit->v), 1.0);
	px = (int)(tex_u * plane->xpm->width);
	py = (int)(tex_v * plane->xpm->height);
	if (px >= plane->xpm->width)
		px = plane->xpm->width - 1;
	if (py >= plane->xpm->height)
		py = plane->xpm->height - 1;
	hit->normal = perturbed_normal(plane->xpm, px, py, hit->normal);
}

static int	get_plane_xpm_color(t_plane *plane, double u, double v)
{
	int		px;
	int		py;

	u = fmod(fabs(u), 1.0);
	v = fmod(fabs(v), 1.0);
	px = (int)(u * plane->xpm->width);
	py = (int)(v * plane->xpm->height);
	if (px >= plane->xpm->width)
		px = plane->xpm->width - 1;
	if (py >= plane->xpm->height)
		py = plane->xpm->height - 1;
	return (get_pixel_color(plane->xpm, px, py));
}

static int	get_plane_chess_color(t_plane *plane, double u, double v)
{
	int	x;
	int	y;

	x = (int)(floor(u));
	y = (int)(floor(v));
	if ((x + y) % 2 == 0)
		return (plane->color);
	else
		return (plane->color2);
}

int	choose_pl_color(t_plane *plane, t_hit *hit)
{
	get_plane_uv(hit, plane);
	apply_plane_bump(hit, plane);
	if (plane->xpm)
		return (get_plane_xpm_color(plane, hit->u, hit->v));
	else if (plane->chessboard)
		return (get_plane_chess_color(plane, hit->u, hit->v));
	else
		return (plane->color);
}
