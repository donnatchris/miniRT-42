/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 23:37:11 by christophed       #+#    #+#             */
/*   Updated: 2025/04/07 14:29:46 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

void	get_sphere_uv(t_hit *hit, t_sphere *sphere)
{
	t_vector	local;

	local = sub_vector(hit->point, sphere->position);
	normalize_vector(&local); // Converti en coordonnées sphériques unitaires
	hit->u = 0.5 + atan2(local.z, local.x) / (2 * M_PI); // longitude
	hit->v = 0.5 - asin(local.y) / M_PI;                 // latitude
}

void	apply_sphere_bump(t_hit *hit, t_sphere *sphere)
{
	double		tex_u;
	double		tex_v;
	int			px;
	int			py;
	double		scale;

	if (!sphere->xpm)
		return ;
	scale = 1;
	tex_u = fmod(fabs(hit->u), scale);
	tex_v = fmod(fabs(hit->v), scale);
	px = (int)(tex_u * sphere->xpm->width);
	py = (int)(tex_v * sphere->xpm->height);
	hit->normal = perturbed_normal(sphere->xpm, px, py, hit->normal);
}

static int choose_sp_color(t_sphere *sphere, t_hit hit)
{
	if (sphere->xpm)
	{
		double tex_u = fmod(fabs(hit.u), 1.0);
		double tex_v = fmod(fabs(hit.v), 1.0);
		int x = (int)(tex_u * sphere->xpm->width);
		int y = (int)(tex_v * sphere->xpm->height);
		if (x >= sphere->xpm->width)
			x = sphere->xpm->width - 1;
		if (y >= sphere->xpm->height)
			y = sphere->xpm->height - 1;
		return get_pixel_color(sphere->xpm, x, y);
	}
	if (!sphere->chessboard)
		return (sphere->color);
	int x = (int)(floor(hit.u * sphere->scale));
	int y = (int)(floor(hit.v * sphere->scale));
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
	get_sphere_uv(&hit, sphere);
	apply_sphere_bump(&hit, sphere);
	hit.color = choose_sp_color(sphere, hit);
	hit.shininess = sphere->shininess;
	hit.reflectivity = sphere->reflectivity;
	return (hit);
}
