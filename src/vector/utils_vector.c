#include "../includes/miniRT.h"

int	solve_quadratic(t_quadratic *q)
{
	q->delta = q->b * q->b - 4 * q->a * q->c;
	if (q->delta < 0)
		return (0);
	q->t1 = (-q->b - sqrt(q->delta)) / (q->a * 2);
	q->t2 = (-q->b + sqrt(q->delta)) / (q->a * 2);
	return (1);
}

int is_zero_vector(t_vector v)
{
    return (v.x == 0.0 && v.y == 0.0 && v.z == 0.0);
}

t_vector	*ray_mul(t_vector *dst, t_camera *r, double t)
{
	dst->x = r->origin.x + t * r->direction.x;
	dst->y = r->origin.y + t * r->direction.y;
	dst->z = r->origin.z + t * r->direction.z;
	return (dst);
}

// t_vector	reflect_vector(t_vector vector, t_vector nb)
// {
// 	t_vector	new_vector;

// 	new_vector = scale_vector(nb, 2 * dot_vector(vector, nb));
// 	new_vector = sub_vector(new_vector, vector);
// 	return (new_vector);
// }

// t_vector	refract_vector(t_vector a, t_vector b, double c)
// {
// 	double		c1;
// 	double		c2;
// 	t_vector	new_vector;

// 	c1 = dot_vector(a, b);
// 	c2 = sqrt(1 - c * c * (1 - c1 * c1));
// 	new_vector = scale_vector(b, c * c1 - c2);
// 	new_vector = add_vector(new_vector, scale_vector(a, c));
// 	normalize_vector(&new_vector);
// 	return (new_vector);
// }
