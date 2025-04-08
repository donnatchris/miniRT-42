/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 23:15:31 by christophed       #+#    #+#             */
/*   Updated: 2025/04/08 09:20:03 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

// Function to initialize the hit structure
// (The hit structure is used to store the intersection)
void	init_hit(t_hit *hit, t_dclst *node)
{
	ft_memset(hit, 0, sizeof(*hit));
	hit->object = node;
}

static void	init_intersection(t_hit *hit)
{
	hit->hit = 0;
	hit->distance = ((double) 1.79769313486231570814527423731704357e+308L);
}

// Function to test the intersection of the ray with all objects
// Returns the closest intersection
// Returns a hit structure with the distance and the object
t_hit	inter_scene(t_ray *ray, t_file *file)
{
	t_hit	hit;
	t_hit	temp;
	t_dclst	*current;

	init_intersection(&hit);
	current = *file->obj_list;
	while (current)
	{
		if (current->type == PL)
			temp = inter_plane(ray, current);
		else if (current->type == SP)
			temp = inter_sphere(ray, current);
		else if (current->type == CY)
			temp = inter_cylinder(ray, current);
		else if (current->type == TR)
			temp = inter_triangle(ray, current);
		else if (current->type == CO)
			temp = inter_cone(ray, current);
		if (temp.hit && temp.distance < hit.distance)
			hit = temp;
		current = current->next;
		if (current == *file->obj_list)
			break ;
	}
	return (hit);
}
