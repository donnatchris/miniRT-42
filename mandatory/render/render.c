/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 22:32:59 by christophed       #+#    #+#             */
/*   Updated: 2025/04/08 14:26:12 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static int	ambient_lighting(t_hit hit, t_ambient_light ambient)
{
	t_rgb	ambient_rgb;
	t_rgb	obj;
	t_rgb	result;

	ambient_rgb.r = ((ambient.color >> 16) & 0xFF) * ambient.ratio;
	ambient_rgb.g = ((ambient.color >> 8) & 0xFF) * ambient.ratio;
	ambient_rgb.b = (ambient.color & 0xFF) * ambient.ratio;
	obj.r = (hit.color >> 16) & 0xFF;
	obj.g = (hit.color >> 8) & 0xFF;
	obj.b = hit.color & 0xFF;
	result.r = (obj.r * ambient_rgb.r) / 255;
	result.g = (obj.g * ambient_rgb.g) / 255;
	result.b = (obj.b * ambient_rgb.b) / 255;
	result.r = fmin(result.r, 255);
	result.g = fmin(result.g, 255);
	result.b = fmin(result.b, 255);
	return ((result.r << 16) | (result.g << 8) | result.b);
}

static int	init_img(t_program *prog)
{
	t_image	*img;

	img = malloc(sizeof(t_image));
	if (!img)
		return (perror("Error\nMalloc img failed"), 1);
	img->img_ptr = mlx_new_image(prog->mlx, WIDTH, HEIGHT);
	if (!img->img_ptr)
		return (perror("mlx_new_image failed"), free(img), 1);
	img->addr = mlx_get_data_addr(img->img_ptr,
			&img->bpp, &img->size_line, &img->endian);
	if (!img->addr)
		return (perror("Error\nMlx_get_data_addr failed"), free(img), 1);
	prog->img = img;
	return (0);
}

static int	choose_color(t_program *prog, int x, int y)
{
	t_ray		ray;
	t_hit		hit;
	t_ray		light_ray;
	t_hit		shadow;

	ray = generate_ray(prog->view, x, y);
	hit = inter_scene(&ray, prog->file);
	if (hit.hit == 0)
		return (0);
	else
	{
		light_ray = generate_light_ray(hit, prog->file->light);
		shadow = inter_scene(&light_ray, prog->file);
		if (shadow.hit && shadow.distance < light_ray.distance)
			return (ambient_lighting(hit, prog->file->ambient_light));
		else
			return (lighting(hit, prog->file->light, prog));
	}
}

void	render(t_program *prog)
{
	t_viewport	view;
	int			x;
	int			y;
	int			color;

	view = viewport(prog);
	prog->view = &view;
	if (init_img(prog))
		return ;
	y = -1;
	while (y++ < HEIGHT)
	{
		x = -1;
		while (x++ < WIDTH)
		{
			color = choose_color(prog, x, y);
			*(int *)(prog->img->addr + ((x + (y * WIDTH))
						* (prog->img->bpp / 8))) = color;
		}
	}
	mlx_put_image_to_window(prog->mlx, prog->win, prog->img->img_ptr, 0, 0);
	printf("IMAGE HAS BEEN GENERATED\n");
}
