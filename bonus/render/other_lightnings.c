/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_lightnings.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 22:48:42 by christophed       #+#    #+#             */
/*   Updated: 2025/04/08 14:49:13 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

int	apply_reflection(t_program *prog, t_reflection data)
{
	t_ray	ref_ray;
	int		ref_color;

	if (data.hit.reflectivity <= 0 || data.depth <= 0)
		return (data.local_color);
	ref_ray.origin = add_vector(data.hit.point,
			mul_vector(data.hit.normal, EPS));
	ref_ray.direction = reflectivity(data.ray.direction, data.hit.normal);
	ref_color = choose_color_with_depth(prog, ref_ray, data.depth - 1);
	return (mix_colors(data.local_color, ref_color, data.hit.reflectivity));
}

int	ambient_lighting(t_hit hit, t_ambient_light ambient)
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
