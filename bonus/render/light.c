/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 22:48:42 by christophed       #+#    #+#             */
/*   Updated: 2025/04/07 16:40:56 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

static t_vector	reflect(t_vector incident, t_vector normal)
{
	double		dot;
	t_vector	reflected;

	dot = dot_vector(normal, incident);
	reflected = sub_vector(incident, mul_vector(normal, 2.0 * dot));
	return (reflected);
}

int	phong_lighting(t_hit hit, t_light light, t_program *prog)
{
	t_phong	p;

	p.light_dir = sub_vector(light.position, hit.point);
	normalize_vector(&p.light_dir);
	p.view_dir = sub_vector(prog->view->origin, hit.point);
	normalize_vector(&p.view_dir);
	p.diffuse = fmax(dot_vector(hit.normal, p.light_dir), 0.0);
	p.reflect_dir = reflect(mul_vector(p.light_dir, -1.0), hit.normal);
	p.specular_coef = pow(fmax(dot_vector(p.reflect_dir,
			p.view_dir), 0.0), hit.shininess);
	p.intensity = (light.ratio * p.diffuse)
		+ (0.5 * p.specular_coef);
	p.intensity = fmin(p.intensity, 1.0);
	p.rgb.r = ((hit.color >> 16) & 0xFF) * p.intensity
		* ((light.color >> 16) & 0xFF) / 255;
	p.rgb.g = ((hit.color >> 8) & 0xFF) * p.intensity
		* ((light.color >> 8) & 0xFF) / 255;
	p.rgb.b = (hit.color & 0xFF) * p.intensity * (light.color & 0xFF) / 255;
	return ((p.rgb.r << 16) | (p.rgb.g << 8) | p.rgb.b);
}

int	apply_reflection(t_program *prog, t_hit hit, t_ray ray,
	int local_color, int depth)
{
	t_ray	ref_ray;
	int		ref_color;

	if (hit.reflectivity <= 0 || depth <= 0)
		return (local_color);
	ref_ray.origin = add_vector(hit.point, mul_vector(hit.normal, EPS));
	ref_ray.direction = reflectivity(ray.direction, hit.normal);
	ref_color = choose_color_with_depth(prog, ref_ray, depth - 1);
	return (mix_colors(local_color, ref_color, hit.reflectivity));
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
