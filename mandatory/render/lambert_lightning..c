/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lambert_lightning..c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 22:48:42 by christophed       #+#    #+#             */
/*   Updated: 2025/04/08 14:32:10 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static double	get_diffuse(t_hit hit, t_light light)
{
	t_vector	light_dir;

	light_dir = sub_vector(light.position, hit.point);
	normalize_vector(&light_dir);
	return (light.ratio * fmax(dot_vector(hit.normal, light_dir), 0.0));
}

static double	get_lambert_lighting(t_hit hit, t_light light, t_program *prog)
{
	double	ambient;
	double	diffuse;
	double	intensity;

	ambient = prog->file->ambient_light.ratio;
	diffuse = get_diffuse(hit, light);
	intensity = ambient + diffuse;
	return (fmin(intensity, 1.0));
}

int	lighting(t_hit hit, t_light light, t_program *prog)
{
	double	intensity;
	t_rgb	rgb;

	intensity = get_lambert_lighting(hit, light, prog);
	return (apply_intensity_to_color(hit.color, light.color, intensity));
}
