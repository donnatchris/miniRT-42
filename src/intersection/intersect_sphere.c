#include "../includes/miniRT.h"

t_hit	inter_sphere(t_ray *ray, t_dclst *node)
{
	t_hit		hit;
	t_sphere	*sphere;
	t_vector	oc;
	t_vector	scaled_direction;
	double		a, b, c;
	double		discriminant;
	double		t;

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
	if (t < EPS)
		t = (-b + sqrt(discriminant)) / (2.0 * a);
	if (t < EPS)
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
