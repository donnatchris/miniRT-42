#include "../includes/miniRT.h"

t_vector	reflect_vector(t_vector vector, t_vector nb)
{
	t_vector	new_vector;

	new_vector = scale_vector(nb, 2 * dot_vector(vector, nb));
	new_vector = sub_vector(new_vector, vector);
	return (new_vector);
}

t_vector	refract_vector(t_vector a, t_vector b, double c)
{
	double		c1;
	double		c2;
	t_vector	new_vector;

	c1 = dot_vector(a, b);
	c2 = sqrt(1 - c * c * (1 - c1 * c1));
	new_vector = scale_vector(b, c * c1 - c2);
	new_vector = add_vector(new_vector, scale_vector(a, c));
	normalize_vector(&new_vector);
	return (new_vector);
}
