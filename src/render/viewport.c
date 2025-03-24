#include "../includes/miniRT.h"

t_viewport	viewport(t_program *prog)
{
	t_viewport	view;
	t_vector	horizontal;
	t_vector	vertical;

	view.fov = DEG_TO_RAD(prog->file->camera.fov);
	view.height = 2.0 * tan(view.fov / 2.0);
	view.width = view.height * ((double) WIDTH / HEIGHT);
	view.world_up = vector(0, 1, 0);
	view.forward = normalize_vector(prog->file->camera.direction);
	view.right = normalize_vector(cross_vector(view.forward, view.world_up));
	view.up = normalize_vector(cross_vector(view.right, view.forward));
	horizontal = mul_vector(view.right, view.width);
	vertical = mul_vector(view.up, view.height);
	view.origin = sub_vector(add_vector(prog->file->camera.origin, view.forward), sub_vector(mul_vector(horizontal, 0.5), mul_vector(vertical, 0.5)));
	return (view);
}
