/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 09:21:48 by christophed       #+#    #+#             */
/*   Updated: 2025/04/08 10:24:08 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

static double	find_closest_intersection(double t1, double t2)
{
	if (t1 > EPS && (t2 < EPS || t1 < t2))
		return (t1);
	if (t2 > EPS)
		return (t2);
	return (-1);
}

static int	is_valid_co_height(t_cone *cone, t_hit hit)
{
	double	m;

	m = dot_vector(sub_vector(hit.point, cone->apex), cone->axis);
	if (m < 0 || m > cone->height)
		return (0);
	if (cone->height > 0 && (m < -EPS || m > cone->height + EPS))
		return (0);
	return (1);
}

static void	init_co_quadratic(t_quadratic *q, t_cone *cone, t_ray *ray)
{
	t_vector	co;
	double		k;
	double		dv;
	double		coa;

	k = pow(tan(cone->angle_rad), 2);
	co = sub_vector(ray->origin, cone->apex);
	dv = dot_vector(ray->direction, cone->axis);
	coa = dot_vector(co, cone->axis);
	q->a = dot_vector(ray->direction, ray->direction) - (1 + k) * dv * dv;
	q->b = 2 * (dot_vector(ray->direction, co) - (1 + k) * dv * coa);
	q->c = dot_vector(co, co) - (1 + k) * coa * coa;
}

static void	calculate_co_normal(t_hit *hit, t_cone *cone, t_ray *ray)
{
	t_vector	apex_to_p;
	double		proj_len;
	t_vector	proj;
	double		k;

	k = pow(tan(cone->angle_rad), 2);
	apex_to_p = sub_vector(hit->point, cone->apex);
	proj_len = dot_vector(apex_to_p, cone->axis);
	proj = mul_vector(cone->axis, proj_len);
	hit->normal = sub_vector(apex_to_p, mul_vector(proj, 1 + k));
	normalize_vector(&hit->normal);
	if (dot_vector(hit->normal, ray->direction) > 0)
		hit->normal = mul_vector(hit->normal, -1);
}

// Function to check if the intersection is valid
// and calculate the intersection point, distance and normal
// Returns a complete hit structure if there is a valid intersection
// Returns a hit structure with hit.hit = 0 if the intersection is not valid
t_hit	inter_cone(t_ray *ray, t_dclst *node)
{
	t_hit		hit;
	t_cone		*cone;
	t_quadratic	q;
	double		t;

	cone = (t_cone *) node->data;
	init_hit(&hit, node);
	init_co_quadratic(&q, cone, ray);
	if (!solve_quadratic(&q))
		return (hit);
	t = find_closest_intersection(q.t1, q.t2);
	if (t < EPS)
		return (hit);
	hit.point = add_vector(ray->origin, mul_vector(ray->direction, t));
	if (!is_valid_co_height(cone, hit))
		return (hit);
	calculate_co_normal(&hit, cone, ray);
	hit.distance = t;
	hit.hit = 1;
	hit.color = choose_co_color(cone, &hit);
	hit.shininess = cone->shininess;
	hit.reflectivity = cone->reflectivity;
	return (hit);
}
