#include "../includes/miniRT.h"

t_viewport	viewport(t_program *prog)
{
	t_viewport	view;
	t_vector	horizontal;
	t_vector	vertical;

	view.asp_ratio = (double) WIDTH / HEIGHT;
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

t_ray	generate_ray(t_viewport *view, int x, int y)
{
	double		new_x;
	double		new_y;
	t_ray		ray;


	new_x = (2.0 * ((x + 0.5) / WIDTH) - 0.5) * view->width;
	new_y = (1.0 - 2.0 * ((y + 0.5) / HEIGHT)) * tan(view->fov / 2.0);
	ray.direction = normalize_vector(add_vector(add_vector(view->forward, mul_vector(view->right, new_x)), mul_vector(view->up, new_y)));
	ray.origin = view->origin;
	return (ray);
}

void	render(t_program *prog)
{
	int			x;
	int			y;
	t_ray		ray;
	t_viewport	view;

	prog->img = mlx_new_image(prog->mlx, WIDTH, HEIGHT);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			generate_ray(&view, &ray, x, y);
			//ft_coeur du programme
			x++;
		}
		y++;
	}
}
