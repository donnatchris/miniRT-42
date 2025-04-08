/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_lightning.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 22:48:42 by christophed       #+#    #+#             */
/*   Updated: 2025/04/08 14:50:40 by christophed      ###   ########.fr       */
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

static double	get_diffuse(t_hit hit, t_light light, t_vector *light_dir)
{
	*light_dir = sub_vector(light.position, hit.point);
	normalize_vector(light_dir);
	return (fmax(dot_vector(hit.normal, *light_dir), 0.0));
}

static double	get_specular(t_hit hit, t_vector light_dir, t_program *prog)
{
	t_vector	view_dir;
	t_vector	reflect_dir;
	double		spec;

	view_dir = sub_vector(prog->view->origin, hit.point);
	normalize_vector(&view_dir);
	reflect_dir = reflect(mul_vector(light_dir, -1.0), hit.normal);
	spec = pow(fmax(dot_vector(reflect_dir, view_dir), 0.0), hit.shininess);
	return (0.5 * spec);
}

static double	get_phong_lighting(t_hit hit, t_light light, t_program *prog)
{
	t_vector	light_dir;
	double		diffuse;
	double		specular;
	double		intensity;

	diffuse = get_diffuse(hit, light, &light_dir);
	specular = get_specular(hit, light_dir, prog);
	intensity = (light.ratio * diffuse) + specular;
	return (fmin(intensity, 1.0));
}

int	phong_lighting(t_hit hit, t_light light, t_program *prog)
{
	double	intensity;

	intensity = get_phong_lighting(hit, light, prog);
	return (apply_intensity_to_color(hit.color, light.color, intensity));
}
