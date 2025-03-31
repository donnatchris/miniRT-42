/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 21:27:02 by christophed       #+#    #+#             */
/*   Updated: 2025/03/31 10:11:58 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT_bonus.h"

t_ray	generate_ray(t_viewport *view, int x, int y)
{
	double	new_x;
	double	new_y;
	t_ray	ray;

	new_x = ((x + 0.5) / WIDTH - 0.5) * view->width;
	new_y = (0.5 - (y + 0.5) / HEIGHT) * view->height;
	ray.direction = add_vector
		(add_vector(view->forward, mul_vector(view->right, new_x)),
			mul_vector(view->up, new_y));
	normalize_vector(&ray.direction);
	ray.origin = view->origin;
	return (ray);
}

t_ray	generate_light_ray(t_hit hit, t_light light)
{
	t_ray		ray;
	t_vector	to_light;

	to_light = sub_vector(light.position, hit.point);
	ray.origin = add_vector(hit.point, mul_vector(hit.normal, EPS));
	ray.direction = to_light;
	normalize_vector(&ray.direction);
	ray.distance = distance_vector(hit.point, light.position);
	return (ray);
}
