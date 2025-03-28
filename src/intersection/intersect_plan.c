#include "../includes/miniRT.h"

t_hit inter_plane(t_ray *ray, t_dclst *node) {
    t_hit      hit;
    t_plane    *plane = (t_plane *)node->data;
    t_vector   unit_normal = plane->normal;
	normalize_vector(&unit_normal);
    double     denom = dot_vector(unit_normal, ray->direction);
    double     tolerance = 1e-3; // Ajustable

    init_hit(&hit, node);
    
    if (fabs(denom) > tolerance)
	{
        t_vector vec_to_plane = sub_vector(plane->position, ray->origin);
        hit.distance = dot_vector(vec_to_plane, unit_normal) / denom;
        
        if (hit.distance >= tolerance)
		{
            hit.point = add_vector(ray->origin, mul_vector(ray->direction, hit.distance));
            hit.normal = (denom < 0) ? unit_normal : mul_vector(unit_normal, -1);
            hit.color = plane->color;
            hit.hit = 1;
        }
    }
    return hit;
}

// t_hit inter_plane(t_ray *ray, t_dclst *node)
// {
// 	t_hit		hit;
// 	t_plane		*plane;
// 	t_vector	vector;
// 	t_vector	scaled_direction;
// 	double		denom;

// 	plane = (t_plane *) node->data;
// 	init_hit(&hit, node);
// 	denom = dot_vector(plane->normal, ray->direction);
// 	if (fabs(denom) > 1e-6)
// 	{
// 		vector = sub_vector(plane->position, ray->origin);
// 		hit.distance = dot_vector(vector, plane->normal) / denom;
// 		if (hit.distance >= 1e-6)
// 		{
// 			scaled_direction = mul_vector(ray->direction, hit.distance);
// 			hit.point = add_vector(ray->origin, scaled_direction);
// 			hit.normal = plane->normal;
// 			hit.color = plane->color;
// 			hit.hit = 1;
// 			return (hit);
// 		}
// 	}
// 	return (hit);
// }

// t_hit	inter_sphere(t_ray *ray, t_dclst *node)
// {
// 	t_hit		hit;
// 	t_sphere	*sphere;
// 	t_vector	oc;
// 	double		a, b, c;
// 	double		discriminant, t;

// 	sphere = (t_sphere *) node->data;
// 	init_hit(&hit, node);

// 	oc = sub_vector(ray->origin, sphere->position);
// 	a = dot_vector(ray->direction, ray->direction);
// 	b = 2.0 * dot_vector(oc, ray->direction);
// 	c = dot_vector(oc, oc) - sphere->rayon2;

// 	discriminant = b * b - 4 * a * c;
// 	if (discriminant < 0)
// 		return (hit);

// 	t = (-b - sqrt(discriminant)) / (2.0 * a);
// 	if (t < 1e-6)
// 		t = (-b + sqrt(discriminant)) / (2.0 * a);
// 	if (t < 1e-6)
// 		return (hit);

// 	hit.distance = t;
// 	hit.point = add_vector(ray->origin, mul_vector(ray->direction, t));
// 	hit.normal = sub_vector(hit.point, sphere->position);
// 	normalize_vector(&hit.normal);
// 	hit.color = sphere->color;
// 	hit.hit = 1;
// 	return (hit);
// }

// version gpt
t_hit	inter_sphere(t_ray *ray, t_dclst *node)
{
	t_hit		hit;
	t_sphere	*sphere;
	t_vector	oc;
	double		a, b, c;
	double		discriminant;
	double		t;
	t_vector	scaled_direction;

	sphere = (t_sphere *) node->data;
	init_hit(&hit, node);
	oc = sub_vector(ray->origin, sphere->position);
	a = dot_vector(ray->direction, ray->direction);
	b = 2.0 * dot_vector(oc, ray->direction);
	c = dot_vector(oc, oc) - (sphere->diameter / 2.0) * (sphere->diameter / 2.0);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (hit); // pas d'intersection
	t = (-b - sqrt(discriminant)) / (2.0 * a);
	if (t < 1e-6)
		t = (-b + sqrt(discriminant)) / (2.0 * a);
	if (t < 1e-6)
		return (hit); // intersection derrière la caméra
	hit.distance = t;
	scaled_direction = mul_vector(ray->direction, t);
	hit.point = add_vector(ray->origin, scaled_direction);
	hit.normal = sub_vector(hit.point, sphere->position);
	normalize_vector(&hit.normal);
	hit.color = sphere->color;
	hit.hit = 1;
	return (hit);
}

t_hit inter_cylinder(t_ray *ray, t_dclst *node)
{
	t_hit hit;
	t_cylinder *cylinder;
	t_vector oc;
	double a, b, c, discriminant, t1, t2;
	t_vector scaled_direction;
	t_vector tmp_normal;

	cylinder = (t_cylinder *) node->data;
	init_hit(&hit, node);
	oc = sub_vector(ray->origin, cylinder->position);

	// Calcul des coefficients pour l'équation quadratique
	// Utilisation de 'orientation' pour obtenir l'axe du cylindre
	t_vector axis = sub_vector(cylinder->p2, cylinder->p1);
	normalize_vector(&axis);

	a = dot_vector(ray->direction, ray->direction) - pow(dot_vector(ray->direction, axis), 2);
	b = 2.0 * (dot_vector(ray->direction, oc) - dot_vector(ray->direction, axis) * dot_vector(oc, axis));
	c = dot_vector(oc, oc) - pow(dot_vector(oc, axis), 2) - cylinder->rayon2 * cylinder->rayon2;

	// Calcul du discriminant pour déterminer s'il y a des intersections
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (hit); // Pas d'intersection

	// Calcul des points d'intersection
	t1 = (-b - sqrt(discriminant)) / (2.0 * a);
	t2 = (-b + sqrt(discriminant)) / (2.0 * a);

	if (t1 < 1e-6 && t2 < 1e-6)
		return (hit); // Pas d'intersection devant la caméra

	// Choisir la valeur la plus proche (t1 ou t2)
	if (t1 > t2)
		hit.distance = t2;
	else
		hit.distance = t1;

	// Calcul du point d'intersection
	scaled_direction = mul_vector(ray->direction, hit.distance);
	hit.point = add_vector(ray->origin, scaled_direction);

	// Calcul de la normale au cylindre (calculée à partir de l'axe du cylindre)
	tmp_normal = sub_vector(hit.point, cylinder->position);
	double projection = dot_vector(tmp_normal, axis);
	tmp_normal = sub_vector(tmp_normal, mul_vector(axis, projection)); // projection sur l'axe
	normalize_vector(&tmp_normal);
	hit.normal = tmp_normal;

	// Vérifier si le point d'intersection est dans les limites de la hauteur du cylindre
	double height_check = dot_vector(hit.point, axis) - dot_vector(cylinder->position, axis);
	if (height_check < 0 || height_check > cylinder->height)
	{
		hit.hit = 0; // Pas d'intersection valide à l'intérieur du cylindre
	}
	else
	{
		hit.color = cylinder->color;
		hit.hit = 1; // Intersection valide
	}

	return (hit);
}
