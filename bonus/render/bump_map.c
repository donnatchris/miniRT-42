/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 09:45:35 by olthorel          #+#    #+#             */
/*   Updated: 2025/04/08 10:43:42 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

static int	get_pixel_grayscale(t_xpm *xpm, int x, int y)
{
	int				pixel_offset;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	pixel_offset = (y * xpm->size_line) + (x * (xpm->bpp / 8));
	b = (unsigned char)xpm->img_addr[pixel_offset];
	g = (unsigned char)xpm->img_addr[pixel_offset + 1];
	r = (unsigned char)xpm->img_addr[pixel_offset + 2];
	return ((int)(0.299 * r + 0.587 * g + 0.114 * b));
}

static int	safe_coord(int coord, int max)
{
	if (coord + 1 >= max)
		return (coord);
	return (coord + 1);
}

static t_vector	get_bump_normal(t_xpm *xpm, int u, int v)
{
	double		h_center;
	double		dx;
	double		dy;
	t_vector	bump;

	h_center = get_pixel_grayscale(xpm, u, v);
	dx = get_pixel_grayscale(xpm, safe_coord(u, xpm->width), v) - h_center;
	dy = get_pixel_grayscale(xpm, u, safe_coord(v, xpm->height)) - h_center;
	bump = vector(-dx * 0.05, -dy * 0.05, 1);
	normalize_vector(&bump);
	return (bump);
}

static t_vector	perturb_normal(t_vector bump, t_vector normal)
{
	t_vector	tangent;
	t_vector	bitangent;
	t_vector	perturbed;

	if (fabs(normal.x) > 0.9)
		tangent = vector(0, 1, 0);
	else
		tangent = vector(1, 0, 0);
	bitangent = cross_vector(normal, tangent);
	tangent = cross_vector(bitangent, normal);
	perturbed = add_vector(
			add_vector(
				mul_vector(tangent, bump.x),
				mul_vector(bitangent, bump.y)),
			mul_vector(normal, bump.z));
	normalize_vector(&perturbed);
	return (perturbed);
}

t_vector	perturbed_normal(t_xpm *xpm, int u, int v, t_vector normal)
{
	t_vector	bump;
	t_vector	final_normal;

	bump = get_bump_normal(xpm, u, v);
	final_normal = perturb_normal(bump, normal);
	return (final_normal);
}
