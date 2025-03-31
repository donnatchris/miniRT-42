/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 23:15:31 by christophed       #+#    #+#             */
/*   Updated: 2025/03/31 09:13:13 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	init_hit(t_hit *hit, t_dclst *node)
{
	ft_memset(hit, 0, sizeof(*hit));
	hit->object = node;
}

t_hit	inter_scene(t_ray *ray, t_file *file)
{
	t_hit	hit;
	t_hit	temp;
	t_dclst	*current;

	hit.hit = 0;
	hit.distance = ((double)1.79769313486231570814527423731704357e+308L);
	current = *file->obj_list;
	while (current)
	{
		if (current->type == PL)
			temp = inter_plane(ray, current);
		else if (current->type == SP)
			temp = inter_sphere(ray, current);
		else if (current->type == CY)
			temp = inter_cylinder(ray, current);
		if (temp.hit && temp.distance < hit.distance)
			hit = temp;
		current = current->next;
		if (current == *file->obj_list)
			break ;
	}
	return (hit);
}
