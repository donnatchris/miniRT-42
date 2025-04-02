#include "../../includes/miniRT_bonus.h"

void create_ortho_basis(t_vector normal, t_vector *u, t_vector *v)
{
	t_vector up;

	if (fabs(normal.y) < 0.999)
		up = (t_vector){0, 1, 0};
	else
		up = (t_vector){1, 0, 0};
	*u = cross_vector(up, normal);
	normalize_vector(u);
	*v = cross_vector(normal, *u);
	normalize_vector(v);
}

