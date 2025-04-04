/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 10:57:38 by christophed       #+#    #+#             */
/*   Updated: 2025/04/04 07:42:27 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

static int choose_cy_color(t_cylinder *cyl, t_hit hit)
{
	t_vector	dir;
	t_vector	axis;
	double		u, v;
	int			x, y;

	if (!cyl->chessboard)
		return (cyl->color);
	axis = cyl->orientation;
	dir = sub_vector(hit.point, cyl->position);
	t_vector radial = sub_vector(dir, mul_vector(axis, dot_vector(dir, axis)));
	u = 0.5 + atan2(radial.z, radial.x) / (2 * M_PI);
	v = dot_vector(dir, axis) / cyl->height;
	x = (int)(floor(u * cyl->scale));
	y = (int)(floor(v * cyl->scale));
	if ((x + y) % 2 == 0)
		return (cyl->color);
	else
		return (cyl->color2);
}

static	int	is_valid_cy_distance(double t, t_ray *ray, t_cylinder *cyl)
{
	t_vector	p;
	t_vector	v;
	double		h;

	p = add_vector(ray->origin, mul_vector(ray->direction, t));
	v = sub_vector(p, cyl->position);
	h = dot_vector(v, cyl->orientation);
	if (t > EPS && h >= 0 && h <= cyl->height)
		return (1);
	return (0);
}

static int	choose_cy_distance(t_chd *chd, t_hit *hit, t_ray *ray, t_cylinder *cyl)
{
	int	valid1;
	int	valid2;

	valid1 = is_valid_cy_distance(chd->t1, ray, cyl);
	valid2 = is_valid_cy_distance(chd->t2, ray, cyl);
	if (!valid1 && !valid2)
		return (-1);
	if (valid1 && (!valid2 || chd->t1 < chd->t2))
		chd->parametric_distance = chd->t1;
	else
		chd->parametric_distance = chd->t2;
	hit->distance = chd->parametric_distance;
	return (0);
}

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
	return (choose_cy_distance(&chd, hit, ray, cyl));
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
	hit.shininess = cyl->shininess;
	hit.reflectivity = cyl->reflectivity;
	hit.color = choose_cy_color(cyl, hit);
	return (hit);
}
