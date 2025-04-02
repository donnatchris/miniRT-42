/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_copy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 21:11:25 by christophed       #+#    #+#             */
/*   Updated: 2025/04/02 09:39:38 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

int	scale_color(int color, double factor)
{
	t_rgb	rgb;

	rgb.r = ((color >> 16) & 0xFF) * factor;
	rgb.g = ((color >> 8) & 0xFF) * factor;
	rgb.b = (color & 0xFF) * factor;
	if (rgb.r > 255)
		rgb.r = 255;
	if (rgb.g > 255)
		rgb.g = 255;
	if (rgb.b > 255)
		rgb.b = 255;
	if (rgb.r < 0)
		rgb.r = 0;
	if (rgb.g < 0)
		rgb.g = 0;
	if (rgb.b < 0)
		rgb.b = 0;
	return ((rgb.r << 16) | (rgb.g << 8) | rgb.b);
}

int	mix_colors(int color1, int color2, double reflectivity)
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
	// mix.r = (rgb1.r + rgb2.r) / 2;
	// mix.g = (rgb1.g + rgb2.g) / 2;
	// mix.b = (rgb1.b + rgb2.b) / 2;
	mix.r = fmin((1 - reflectivity) * rgb1.r + reflectivity * rgb2.r, 255);
	mix.g = fmin((1 - reflectivity) * rgb1.g + reflectivity * rgb2.g, 255);
	mix.b = fmin((1 - reflectivity) * rgb1.b + reflectivity * rgb2.b, 255);
	return ((mix.r << 16) | (mix.g << 8) | mix.b);
}

int	multiply_colors(int color1, int color2)
{
	t_rgb	rgb;

	rgb.r = ((color1 >> 16) & 0xFF) * ((color2 >> 16) & 0xFF) / 255;
	rgb.g = ((color1 >> 8) & 0xFF) * ((color2 >> 8) & 0xFF) / 255;
	rgb.b = (color1 & 0xFF) * (color2 & 0xFF) / 255;
	return ((rgb.r << 16) | (rgb.g << 8) | rgb.b);
}

int	add_colors(int color1, int color2)
{
	t_rgb	rgb;

	rgb.r = fmin(0xFF, ((color1 >> 16) & 0xFF) + ((color2 >> 16) & 0xFF));
	rgb.g = fmin(0xFF, ((color1 >> 8) & 0xFF) + ((color2 >> 8) & 0xFF));
	rgb.b = fmin(0xFF, (color1 & 0xFF) + (color2 & 0xFF));
	return ((rgb.r << 16) | (rgb.g << 8) | rgb.b);
}
