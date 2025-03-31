/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plan.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 23:54:13 by christophed       #+#    #+#             */
/*   Updated: 2025/03/31 11:32:01 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

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
			hit.color = plane->color;
			hit.hit = 1;
		}
	}
	return (hit);
}
