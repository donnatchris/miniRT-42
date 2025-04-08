/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 23:37:11 by christophed       #+#    #+#             */
/*   Updated: 2025/04/08 11:19:56 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

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
	hit.hit = 1;
	hit.color = choose_sp_color(sphere, &hit);
	hit.shininess = sphere->shininess;
	hit.reflectivity = sphere->reflectivity;
	return (hit);
}
