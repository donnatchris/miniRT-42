/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 21:11:25 by christophed       #+#    #+#             */
/*   Updated: 2025/04/08 13:49:42 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

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
	mix.r = fmin((1 - reflectivity) * rgb1.r + reflectivity * rgb2.r, 255);
	mix.g = fmin((1 - reflectivity) * rgb1.g + reflectivity * rgb2.g, 255);
	mix.b = fmin((1 - reflectivity) * rgb1.b + reflectivity * rgb2.b, 255);
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
