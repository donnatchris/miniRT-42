/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_triangle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:08:54 by christophed       #+#    #+#             */
/*   Updated: 2025/04/08 13:09:09 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

static int	tr_hit_distance(t_hit *hit, t_ray *ray, t_triangle *tr,
		t_vector edge[2])
{
	t_vector	h;
	t_vector	q;
	t_vector	s;
	double		afuv[4];

	h = cross_vector(ray->direction, edge[1]);
	afuv[0] = dot_vector(edge[0], h);
	if (fabs(afuv[0]) < EPS)
		return (0);
	afuv[1] = 1.0 / afuv[0];
	s = sub_vector(ray->origin, tr->vertex[0]);
	afuv[2] = afuv[1] * dot_vector(s, h);
	if (afuv[2] < 0.0 || afuv[2] > 1.0)
		return (0);
	q = cross_vector(s, edge[0]);
	afuv[3] = afuv[1] * dot_vector(ray->direction, q);
	if (afuv[3] < 0.0 || (afuv[2] + afuv[3]) > 1.0)
		return (0);
	hit->distance = afuv[1] * dot_vector(edge[1], q);
	return (1);
}

t_hit	inter_triangle(t_ray *ray, t_dclst *node)
{
	t_hit		hit;
	t_triangle	*tr;
	t_vector	edge[2];

	init_hit(&hit, node);
	tr = (t_triangle *)node->data;
	edge[0] = sub_vector(tr->vertex[1], tr->vertex[0]);
	edge[1] = sub_vector(tr->vertex[2], tr->vertex[0]);
	if (!tr_hit_distance(&hit, ray, tr, edge))
		return (hit);
	if (hit.distance >= EPS)
	{
		hit.point = add_vector(ray->origin,
				mul_vector(ray->direction, hit.distance));
		hit.normal = cross_vector(edge[0], edge[1]);
		normalize_vector(&hit.normal);
		hit.color = tr->color;
		hit.hit = 1;
	}
	return (hit);
}
