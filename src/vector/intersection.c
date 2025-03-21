#include "../includes/miniRT.h"

int	is_inter_sphere(t_camera ray, t_sphere sphere, double *t)
{
	t_vector	vector;
	double		radius;
	double		discriminant;
	double		a;
	double		b;
	double		c;
	double		t1;
	double		t2;

	vector = subtrat_vector(ray.origin, sphere.position);
	radius = sphere.diameter / 2.0;
	a = dot_vector(ray.direction, ray.direction);
	b = 2.0 * dot_vector(vector, ray.direction);
	c = dot_vector(vector, vector) - (radius * radius);
	discriminant = (b * b) - 4 * (a * c);
	if (discriminant < 0)
		return (0);
	if (fabs(a) < 1e-6)
        return (0);
	t1 = (-b - sqrt(discriminant)) / (2.0 * a);
	t2 = (-b + sqrt(discriminant)) / (2.0 * a);
	if (t1 > 0)
		*t = t1;
	else if (t2 > 0)
		*t = t2;
	else
		return (0);
	return (1);
}
