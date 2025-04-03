/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 22:48:42 by christophed       #+#    #+#             */
/*   Updated: 2025/04/03 12:04:17 by chdonnat         ###   ########.fr       */
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
	p.specular_coef = pow(fmax(dot_vector(p.reflect_dir, p.view_dir), 0.0), hit.shininess);
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

