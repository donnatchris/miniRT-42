#include "../../includes/miniRT_bonus.h"

t_hit	inter_triangle(t_ray *ray, t_dclst *node)
{
	t_hit		hit;
	t_triangle	*tr;
	t_vector	edge1;
	t_vector	edge2;
	t_vector	h;
	t_vector	q;
	t_vector	s;
	double		a;
	double		f;
	double		u;
	double		v;

	init_hit(&hit, node);
	tr = (t_triangle *)node->data;
	edge1 = sub_vector(tr->vertex[1], tr->vertex[0]);
	edge2 = sub_vector(tr->vertex[2], tr->vertex[0]);

	h = cross_vector(ray->direction, edge2);
	a = dot_vector(edge1, h);
	if (fabs(a) < EPS)
		return (hit);
	f = 1.0 / a;
	s = sub_vector(ray->origin, tr->vertex[0]);
	u = f * dot_vector(s, h);
	if (u < 0.0 || u > 1.0)
		return (hit);
	q = cross_vector(s, edge1);
	v = f * dot_vector(ray->direction, q);
	if (v < 0.0 || (u + v) > 1.0)
		return (hit);
	hit.distance = f * dot_vector(edge2, q);
	if (hit.distance >= EPS)
	{
		hit.point = add_vector(ray->origin, mul_vector(ray->direction, hit.distance));
		hit.normal = cross_vector(edge1, edge2);
		normalize_vector(&hit.normal);
		hit.color = tr->color;
		hit.hit = 1;
	}
	return (hit);
}
