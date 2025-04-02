/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plan.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 23:54:13 by christophed       #+#    #+#             */
/*   Updated: 2025/04/02 17:24:20 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

static int	chessboard_pl_color(t_plane *plane, t_hit hit)
{
	t_vector	local;
	double		x;
	double		y;

	local = sub_vector(hit.point, plane->position);
	x = dot_vector(local, plane->u) * plane->scale;
	y = dot_vector(local, plane->v) * plane->scale;
	if ((int) (floor(x) + floor(y)) % 2 == 0)
		return (plane->color);
	else
		return (plane->color2);
}

static int xpm_pl_color(t_plane *plane, t_hit hit)
{
	t_vector	local;
	double		u, v;
	int			x, y;	

	// Position locale du point par rapport au plan
	local = sub_vector(hit.point, plane->position);

	// Coordonnées UV (0..1)
	u = dot_vector(local, plane->u) / plane->xpm_scale;
	v = dot_vector(local, plane->v) / plane->xpm_scale;

	// Optionnel : faire un mod 1.0 pour répéter
	u = u - floor(u);
	v = v - floor(v);

	// Appliquer la rotation de texture
if (plane->xpm_rotation == 90)
{
	double tmp = u;
	u = v;
	v = 1.0 - tmp;
}
else if (plane->xpm_rotation == 180)
{
	u = 1.0 - u;
	v = 1.0 - v;
}
else if (plane->xpm_rotation == 270)
{
	double tmp = u;
	u = 1.0 - v;
	v = tmp;
}


	// Transformation en pixels
	x = (int)(u * plane->xpm->width);
	y = (int)(v * plane->xpm->height);

	return (get_xpm_color(plane->xpm, x, y));
}

static int	choose_pl_color(t_plane *plane, t_hit hit)
{
	if (plane->xpm)
		return (xpm_pl_color(plane, hit));
	else if (plane->chessboard)
		return (chessboard_pl_color(plane, hit));
	else
		return (plane->color);
}

t_hit	inter_plane(t_ray *ray, t_dclst *node)
{
	t_hit		hit;
	t_plane		*plane;
	t_vector	vec_to_plane;
	double		denom;

	init_hit(&hit, node);
	plane = (t_plane *)node->data;
	denom = dot_vector(plane->normal, ray->direction);
	if (fabs(denom) > EPS)
	{
		vec_to_plane = sub_vector(plane->position, ray->origin);
		hit.distance = dot_vector(vec_to_plane, plane->normal) / denom;
		if (hit.distance >= EPS)
		{
			hit.point = add_vector(ray->origin,
					mul_vector(ray->direction, hit.distance));
			if (denom < 0)
				hit.normal = plane->normal;
			else
				hit.normal = mul_vector(plane->normal, -1);
			hit.hit = 1;
			hit.color = choose_pl_color(plane, hit);
			hit.shininess = plane->shininess;
		}
	}
	return (hit);
}
