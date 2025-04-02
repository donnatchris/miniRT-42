/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_vector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 16:24:20 by olthorel          #+#    #+#             */
/*   Updated: 2025/04/01 16:47:12 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

int	solve_quadratic(t_quadratic *q)
{
	q->delta = q->b * q->b - 4 * q->a * q->c;
	if (q->delta < 0)
		return (0);
	q->t1 = (-q->b - sqrt(q->delta)) / (q->a * 2);
	q->t2 = (-q->b + sqrt(q->delta)) / (q->a * 2);
	return (1);
}

int	is_zero_vector(t_vector v)
{
	return (v.x == 0.0 && v.y == 0.0 && v.z == 0.0);
}

t_vector	*ray_mul(t_vector *dst, t_ray *r, double t)
{
	dst->x = r->origin.x + t * r->direction.x;
	dst->y = r->origin.y + t * r->direction.y;
	dst->z = r->origin.z + t * r->direction.z;
	return (dst);
}

t_vector	reflectivity(t_vector incident, t_vector normal)
{
	return (sub_vector(incident, mul_vector(normal, 2 * dot_vector(incident, normal))));
}