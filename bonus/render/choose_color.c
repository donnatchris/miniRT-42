/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 09:44:42 by olthorel          #+#    #+#             */
/*   Updated: 2025/04/08 10:43:48 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

int	add_lights(t_program *prog, t_hit hit, int color)
{
	t_list	*light_node;
	t_light	*light;
	t_ray	light_ray;
	t_hit	shadow;

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
	return (color);
}

int	choose_color_with_depth(t_program *prog, t_ray ray, int depth)
{
	t_hit				hit;
	t_reflection		ref;
	int					color;

	hit = inter_scene(&ray, prog->file);
	if (hit.hit == 0)
		return (0);
	color = ambient_lighting(hit, prog->file->ambient_light);
	color = add_lights(prog, hit, color);
	ref.ray = ray;
	ref.hit = hit;
	ref.local_color = color;
	ref.depth = depth;
	return (apply_reflection(prog, ref));
}

int	choose_color(t_program *prog, int x, int y)
{
	t_ray	ray;

	ray = generate_ray(prog->view, x, y);
	return (choose_color_with_depth(prog, ray, 5));
}

int	get_pixel_color(t_xpm *xpm, int x, int y)
{
	int				pixel_offset;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	if (x < 0 || x >= xpm->width || y < 0 || y >= xpm->height)
		return (0);
	pixel_offset = (y * xpm->size_line) + (x * (xpm->bpp / 8));
	b = (unsigned char)xpm->img_addr[pixel_offset];
	g = (unsigned char)xpm->img_addr[pixel_offset + 1];
	r = (unsigned char)xpm->img_addr[pixel_offset + 2];
	return ((r << 16) | (g << 8) | b);
}
