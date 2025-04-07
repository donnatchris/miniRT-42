/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plan.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 23:54:13 by christophed       #+#    #+#             */
/*   Updated: 2025/04/07 14:51:59 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

// static int	choose_pl_color(t_plane *plane, t_hit hit)
// {
// 	t_vector	local;
// 	double		x;
// 	double		y;

// 	if (!plane->chessboard)
// 		return (plane->color);
// 	local = sub_vector(hit.point, plane->position);
// 	x = dot_vector(local, plane->u) * plane->scale;
// 	y = dot_vector(local, plane->v) * plane->scale;
// 	if ((int) (floor(x) + floor(y)) % 2 == 0)
// 		return (plane->color);
// 	else
// 		return (plane->color2);
// }

// t_hit	inter_plane(t_ray *ray, t_dclst *node)
// {
// 	t_hit		hit;
// 	t_plane		*plane;
// 	t_vector	vec_to_plane;
// 	double		denom;

// 	init_hit(&hit, node);
// 	plane = (t_plane *)node->data;
// 	denom = dot_vector(plane->normal, ray->direction);
// 	if (fabs(denom) > EPS)
// 	{
// 		vec_to_plane = sub_vector(plane->position, ray->origin);
// 		hit.distance = dot_vector(vec_to_plane, plane->normal) / denom;
// 		if (hit.distance >= EPS)
// 		{
// 			hit.point = add_vector(ray->origin,
// 					mul_vector(ray->direction, hit.distance));
// 			if (denom < 0)
// 				hit.normal = plane->normal;
// 			else
// 				hit.normal = mul_vector(plane->normal, -1);
// 			hit.hit = 1;
// 			hit.color = choose_pl_color(plane, hit);
// 			hit.shininess = plane->shininess;
// 			hit.reflectivity = plane->reflectivity;
// 		}
// 	}
// 	return (hit);
// }

void	get_plane_uv(t_hit *hit, t_plane *plane)
{
	t_vector	local;

	local = sub_vector(hit->point, plane->position);
	hit->u = dot_vector(local, plane->u) * 1; // 1 a modif si on veut appliquer un scale
	hit->v = dot_vector(local, plane->v) * 1; // 1 a modif si on veut appliquer un scale
}

// static int	choose_pl_color(t_plane *plane, t_hit hit)
// {
// 	double	x;
// 	double	y;

// 	if (!plane->chessboard)
// 	x = hit.u * plane->scale;
// 	y = hit.v * plane->scale;
// 		return (plane->color);
// 	if (((int) floor(x) + (int) floor(y)) % 2 == 0)
// 		return (plane->color);
// 	else
// 		return (plane->color2);
// }

static int	choose_pl_color(t_plane *plane, t_hit hit)
{
	double	x;
	double	y;

	// ✅ Si une texture XPM est présente, on l'utilise
	if (plane->xpm)
	{
		double tex_u = fmod(fabs(hit.u), 1.0);
		double tex_v = fmod(fabs(hit.v), 1.0);
		int px = (int)(tex_u * plane->xpm->width);
		int py = (int)(tex_v * plane->xpm->height);

		if (px >= plane->xpm->width)
			px = plane->xpm->width - 1;
		if (py >= plane->xpm->height)
			py = plane->xpm->height - 1;

		return get_pixel_color(plane->xpm, px, py);
	}

	// ✅ Sinon : damier ?
	if (!plane->chessboard)
		return (plane->color);

	// ✅ Checkerboard : applique scale à u/v
	x = hit.u * plane->scale;
	y = hit.v * plane->scale;
	if (((int)floor(x) + (int)floor(y)) % 2 == 0)
		return (plane->color);
	else
		return (plane->color2);
}


void	apply_plane_bump(t_hit *hit, t_plane *plane)
{
	double		tex_u;
	double		tex_v;
	int			px;
	int			py;

	if (!plane->xpm)
		return ;
	tex_u = fmod(fabs(hit->u), 1.0);
	tex_v = fmod(fabs(hit->v), 1.0);
	px = (int)(tex_u * plane->xpm->width);
	py = (int)(tex_v * plane->xpm->height);
	hit->normal = perturbed_normal(plane->xpm, px, py, hit->normal);
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
			get_plane_uv(&hit, plane);
			apply_plane_bump(&hit, plane);
			hit.color = choose_pl_color(plane, hit);
			hit.shininess = plane->shininess;
			hit.reflectivity = plane->reflectivity;
		}
	}
	return (hit);
}
