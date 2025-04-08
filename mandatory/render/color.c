/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 21:11:25 by christophed       #+#    #+#             */
/*   Updated: 2025/04/08 14:30:11 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	mix_colors(int color1, int color2)
{
	t_rgb	rgb1;
	t_rgb	rgb2;
	t_rgb	mix;

	rgb1.r = (color1 >> 16) & 0xFF;
	rgb1.g = (color1 >> 8) & 0xFF;
	rgb1.b = color1 & 0xFF;
	rgb2.r = (color2 >> 16) & 0xFF;
	rgb2.g = (color2 >> 8) & 0xFF;
	rgb2.b = color2 & 0xFF;
	mix.r = (rgb1.r + rgb2.r) / 2;
	mix.g = (rgb1.g + rgb2.g) / 2;
	mix.b = (rgb1.b + rgb2.b) / 2;
	return ((mix.r << 16) | (mix.g << 8) | mix.b);
}

int	add_colors(int color1, int color2)
{
	t_rgb	rgb;

	rgb.r = fmin(0xFF, ((color1 >> 16) & 0xFF) + ((color2 >> 16) & 0xFF));
	rgb.g = fmin(0xFF, ((color1 >> 8) & 0xFF) + ((color2 >> 8) & 0xFF));
	rgb.b = fmin(0xFF, (color1 & 0xFF) + (color2 & 0xFF));
	return ((rgb.r << 16) | (rgb.g << 8) | rgb.b);
}

int	apply_intensity_to_color(int base_color, int light_color, double intensity)
{
	t_rgb	rgb;

	rgb.r = ((base_color >> 16) & 0xFF) * intensity
		* ((light_color >> 16) & 0xFF) / 255;
	rgb.g = ((base_color >> 8) & 0xFF) * intensity
		* ((light_color >> 8) & 0xFF) / 255;
	rgb.b = (base_color & 0xFF) * intensity
		* (light_color & 0xFF) / 255;
	if (rgb.r > 255)
		rgb.r = 255;
	if (rgb.g > 255)
		rgb.g = 255;
	if (rgb.b > 255)
		rgb.b = 255;
	return ((rgb.r << 16) | (rgb.g << 8) | rgb.b);
}
