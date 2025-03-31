/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 10:57:38 by christophed       #+#    #+#             */
/*   Updated: 2025/03/31 11:31:57 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

static int	cy_hit_distance(t_ray *ray, t_cylinder *cyl, t_hit *hit)
{
	t_chd	chd;

	chd.rayon2 = (cyl->diameter / 2) * (cyl->diameter / 2);
	chd.oc = sub_vector(ray->origin, cyl->position);
	chd.a = dot_vector(ray->direction, ray->direction)
		- pow(dot_vector(ray->direction, cyl->orientation), 2);
	chd.b = 2 * (dot_vector(chd.oc, ray->direction)
			- dot_vector(chd.oc, cyl->orientation)
			* dot_vector(ray->direction, cyl->orientation));
	chd.c = dot_vector(chd.oc, chd.oc)
		- pow(dot_vector(chd.oc, cyl->orientation), 2) - chd.rayon2;
	chd.delta = chd.b * chd.b - 4 * chd.a * chd.c;
	if (chd.delta < 0)
		return (-1);
	chd.t1 = (-chd.b - sqrt(chd.delta)) / (2 * chd.a);
	chd.t2 = (-chd.b + sqrt(chd.delta)) / (2 * chd.a);
	if (chd.t1 > EPS)
		chd.parametric_distance = fmin(chd.t1, chd.t2);
	else
		chd.parametric_distance = chd.t2;
	if (chd.parametric_distance < EPS)
		return (-1);
	hit->distance = chd.parametric_distance;
	return (0);
}

t_hit	inter_cylinder(t_ray *ray, t_dclst *node)
{
	t_hit		hit;
	t_cylinder	*cyl;
	t_vector	cp;
	double		m;

	cyl = (t_cylinder *)node->data;
	init_hit(&hit, node);
	if (cy_hit_distance(ray, cyl, &hit) == -1)
		return (hit);
	hit.point = add_vector(ray->origin,
			mul_vector(ray->direction, hit.distance));
	cp = sub_vector(hit.point, cyl->position);
	m = dot_vector(cp, cyl->orientation);
	hit.normal = sub_vector(cp, mul_vector(cyl->orientation, m));
	normalize_vector(&hit.normal);
	hit.hit = 1;
	hit.color = cyl->color;
	hit.hit = 1;
	return (hit);
}
