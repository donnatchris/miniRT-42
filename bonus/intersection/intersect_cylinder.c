/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 10:57:38 by christophed       #+#    #+#             */
/*   Updated: 2025/04/07 14:39:45 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

void	get_cylinder_uv(t_hit *hit, t_cylinder *cyl)
{
	t_vector	local;
	t_vector	axis = cyl->orientation;
	t_vector	height_proj;
	t_vector	around;
	double		theta;

	local = sub_vector(hit->point, cyl->position);
	double height = dot_vector(local, axis);
	hit->v = height;
	height_proj = mul_vector(axis, height);
	around = sub_vector(local, height_proj);
	normalize_vector(&around);
	theta = atan2(dot_vector(around, cyl->v), dot_vector(around, cyl->u));
	hit->u = 0.5 + theta / (2.0 * M_PI);
}

void	apply_cylinder_bump(t_hit *hit, t_cylinder *cyl)
{
	double		tex_u;
	double		tex_v;
	int			px;
	int			py;

	if (!cyl->xpm)
		return ;

	// Wrapping UV dans [0, 1]
	tex_u = fmod(fabs(hit->u), 1.0);
	tex_v = fmod(fabs(hit->v), 1.0);

	// Conversion en pixels
	px = (int)(tex_u * cyl->xpm->width);
	py = (int)(tex_v * cyl->xpm->height);

	// Sécurité : clamp pour ne jamais dépasser la texture
	if (px >= cyl->xpm->width)
		px = cyl->xpm->width - 1;
	if (py >= cyl->xpm->height)
		py = cyl->xpm->height - 1;

	hit->normal = perturbed_normal(cyl->xpm, px, py, hit->normal);
}


static int choose_cy_color(t_cylinder *cyl, t_hit hit)
{
	double		tex_u;
	double		tex_v;
	int			x;
	int			y;

	// ✅ Si on a une texture XPM
	if (cyl->xpm)
	{
		// UV wrapping
		tex_u = fmod(fabs(hit.u), 1.0);
		tex_v = fmod(fabs(hit.v), 1.0);

		// Passage en pixels
		x = (int)(tex_u * cyl->xpm->width);
		y = (int)(tex_v * cyl->xpm->height);

		// Clamp (sécurité)
		if (x >= cyl->xpm->width)
			x = cyl->xpm->width - 1;
		if (y >= cyl->xpm->height)
			y = cyl->xpm->height - 1;

		return get_pixel_color(cyl->xpm, x, y);
	}

	// ✅ Sinon, checkerboard (damier)
	if (!cyl->chessboard)
		return (cyl->color);

	x = (int)(floor(hit.u * cyl->scale));
	y = (int)(floor(hit.v * cyl->scale));
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
	get_cylinder_uv(&hit, cyl);
	apply_cylinder_bump(&hit, cyl);
	hit.shininess = cyl->shininess;
	hit.reflectivity = cyl->reflectivity;
	hit.color = choose_cy_color(cyl, hit);
	return (hit);
}
