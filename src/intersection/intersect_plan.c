#include "../includes/miniRT.h"

t_hit inter_plane(t_ray *ray, t_dclst *node)
{
	t_hit		hit;
	t_plane		*plane;
	t_vector	vector;
	t_vector	scaled_direction;
	double		denom;

	plane = (t_plane *) node->data;
	init_hit(&hit, node);
	denom = dot_vector(plane->normal, ray->direction);
	if (fabs(denom) > 1e-6)
	{
		vector = sub_vector(plane->position, ray->origin);
		hit.distance = dot_vector(vector, plane->normal) / denom;
		if (hit.distance >= 1e-6)
		{
			scaled_direction = mul_vector(ray->direction, hit.distance);
			hit.point = add_vector(ray->origin, scaled_direction);
			hit.normal = plane->normal;
			hit.color = plane->color;
			hit.hit = 1;
			return (hit);
		}
	}
	return (hit);
}

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
	t_hit	hit;

	(void)node;
	(void)ray;
	init_hit(&hit, node);
	return (hit);
}
