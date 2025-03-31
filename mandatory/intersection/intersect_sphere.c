/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 23:37:11 by christophed       #+#    #+#             */
/*   Updated: 2025/03/29 10:20:13 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static int	sp_hit_distance(t_ray *ray, t_sphere *sphere,
		t_vector oc, double *hit_distance)
{
	double		a;
	double		b;
	double		c;
	double		discriminant;

	a = dot_vector(ray->direction, ray->direction);
	b = 2.0 * dot_vector(oc, ray->direction);
	c = dot_vector(oc, oc) - (sphere->diameter / 2.0)
		* (sphere->diameter / 2.0);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1);
	*hit_distance = (-b - sqrt(discriminant)) / (2.0 * a);
	if (*hit_distance < EPS)
		*hit_distance = (-b + sqrt(discriminant)) / (2.0 * a);
	if (*hit_distance < EPS)
		return (-1);
	return (0);
}

t_hit	inter_sphere(t_ray *ray, t_dclst *node)
{
	t_hit		hit;
	t_sphere	*sphere;
	t_vector	oc;
	t_vector	scaled_direction;

	sphere = (t_sphere *) node->data;
	init_hit(&hit, node);
	oc = sub_vector(ray->origin, sphere->position);
	if (sp_hit_distance(ray, sphere, oc, &hit.distance) == -1)
		return (hit);
	scaled_direction = mul_vector(ray->direction, hit.distance);
	hit.point = add_vector(ray->origin, scaled_direction);
	hit.normal = sub_vector(hit.point, sphere->position);
	normalize_vector(&hit.normal);
	hit.color = sphere->color;
	hit.hit = 1;
	return (hit);
}
