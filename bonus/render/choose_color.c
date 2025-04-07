#include "../../includes/miniRT_bonus.h"

int	choose_color_with_depth(t_program *prog, t_ray ray, int depth)
{
	t_hit	hit;
	t_ray	light_ray;
	t_hit	shadow;
	t_list	*light_node;
	t_light	*light;
	int		color;

	hit = inter_scene(&ray, prog->file);
	if (hit.hit == 0)
		return (0);
	color = ambient_lighting(hit, prog->file->ambient_light);
	light_node = *prog->file->light_list;
	while (light_node)
	{
		light = (t_light *) light_node->content;
		light_ray = generate_light_ray(hit, *light);
		shadow = inter_scene(&light_ray, prog->file);
		if (!(shadow.hit && shadow.distance < light_ray.distance))
			color = add_colors(color, phong_lighting(hit, *light, prog));
		light_node = light_node->next;
	}
	return (apply_reflection(prog, hit, ray, color, depth));
}

int	choose_color(t_program *prog, int x, int y)
{
	t_ray	ray;

	ray = generate_ray(prog->view, x, y);
	return (choose_color_with_depth(prog, ray, 5));
}
