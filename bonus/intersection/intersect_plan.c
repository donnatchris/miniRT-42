/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plan.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 23:54:13 by christophed       #+#    #+#             */
/*   Updated: 2025/04/04 15:27:09 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

static int	choose_pl_color(t_plane *plane, t_hit hit)
{
	t_vector	local;
	double		x;
	double		y;

	if (!plane->chessboard)
		return (plane->color);
	local = sub_vector(hit.point, plane->position);
	x = dot_vector(local, plane->u) * plane->scale;
	y = dot_vector(local, plane->v) * plane->scale;
	if ((int) (floor(x) + floor(y)) % 2 == 0)
		return (plane->color);
	else
		return (plane->color2);
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
			hit.reflectivity = plane->reflectivity;
			if (plane->xpm) // on a une texture bump
			{
				t_vector	local;
				double		u;
				double		v;
				int			tex_u;
				int			tex_v;

				// Calcule les coords locales (comme pour ton checkerboard)
				local = sub_vector(hit.point, plane->position);
				u = dot_vector(local, plane->u) * plane->scale;
				v = dot_vector(local, plane->v) * plane->scale;

				// Applique modulo pour rester dans la texture
				u = fmod(fabs(u), 1.0);
				v = fmod(fabs(v), 1.0);

				// Convertis ça en pixels
				tex_u = (int)(u * plane->xpm->width);
				tex_v = (int)(v * plane->xpm->height);

				// Applique le bump
				printf("Vecteur avant perturbation: ");
				printf("x: %f, y: %f, z: %f\n", hit.normal.x, hit.normal.y, hit.normal.z);
				hit.normal = perturbed_normal(plane->xpm, tex_u, tex_v, hit.normal);
				printf("Vecteur apres perturbation: ");
				printf("x: %f, y: %f, z: %f\n", hit.normal.x, hit.normal.y, hit.normal.z);

			}

		}
	}
	return (hit);
}
