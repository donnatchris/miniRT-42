#include "../../includes/miniRT_bonus.h"

static int	get_pixel_grayscale(t_xpm *xpm, int x, int y)
{
	int				pixel_offset;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	pixel_offset = (y * xpm->size_line) + (x * (xpm->bpp / 8));
	b = (unsigned char)xpm->img_addr[pixel_offset];
	g = (unsigned char)xpm->img_addr[pixel_offset + 1];
	r = (unsigned char)xpm->img_addr[pixel_offset + 2];
	return ((int) (0.299 * r + 0.587 * g + 0.114 * b));
}

static t_vector	get_bump_normal(t_xpm *xpm, int u, int v)
{
	double		h_center;
	double		dx;
	double		dy;
	double strength = 1; // commence petit
	int			safe_u;
	int			safe_v;
	t_vector	bump;

	safe_u = u + 1;
	safe_v = v + 1;
	if (safe_u > xpm->width)
		safe_u = u;
	if (safe_v > xpm->height)
		safe_v = v;
	h_center = get_pixel_grayscale(xpm, u, v);
	dx = get_pixel_grayscale(xpm, safe_u, v) - h_center;
	dy = get_pixel_grayscale(xpm, u, safe_v) - h_center;
	printf("dx: %f, dy: %f\n", dx, dy);
	bump = vector(-dx * strength, -dy * strength, 1);
	normalize_vector(&bump);
	return (bump);
}

static t_vector	perturb_normal(t_vector bump, t_vector normal)
{
	t_vector tangent;
	t_vector bitangent;
	t_vector perturbed;

	if (fabs(normal.x) > 0.9)
		tangent = vector(0, 1, 0);
	else
		tangent = vector(1, 0, 0);
	bitangent = cross_vector(normal, tangent);
	tangent = cross_vector(bitangent, normal);
	perturbed = add_vector(
				mul_vector(tangent, bump.x),
				mul_vector(bitangent, bump.y)),
			mul_vector(normal, bump.z);
	normalize_vector(&perturbed);
	return (perturbed);
}

t_vector	perturbed_normal(t_xpm *xpm, int u, int v, t_vector normal)
{
	t_vector	bump;
	t_vector	final_normal;

	bump = get_bump_normal(xpm, u, v);
	final_normal = perturb_normal(bump, normal);
	return (final_normal);
}
