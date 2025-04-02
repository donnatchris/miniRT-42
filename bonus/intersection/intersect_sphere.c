/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 23:37:11 by christophed       #+#    #+#             */
/*   Updated: 2025/04/01 16:54:50 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

static int choose_sp_color(t_sphere *sphere, t_hit hit)
{
	t_vector	normal;
	double		u;
	double		v;
	int			x;
	int			y;

	if (!sphere->chessboard)
		return (sphere->color);
	normal = sub_vector(hit.point, sphere->position);
	normalize_vector(&normal);
	u = 0.5 + atan2(normal.z, normal.x) / (2 * M_PI);
	v = 0.5 - asin(normal.y) / M_PI;
	x = (int)(floor(u * sphere->scale));
	y = (int)(floor(v * sphere->scale));
	if ((x + y) % 2 == 0)
		return (sphere->color);
	else
		return (sphere->color2);
}


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
	hit.hit = 1;
	hit.color = choose_sp_color(sphere, hit);
	hit.shininess = sphere->shininess;
	hit.reflectivity = sphere->reflectivity;
	return (hit);
}
