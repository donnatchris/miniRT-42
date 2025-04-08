/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_cone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 10:13:57 by christophed       #+#    #+#             */
/*   Updated: 2025/04/01 09:27:06 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

// Function to fill the cone structure from the line
// Returns 0 if the cone was filled successfully
// Returns 1 if an error occured
static int	fill_cone_from_line(t_cone *cone, char *line)
{
	size_t	start;
	char	*arg;

	start = 2;
	arg = next_arg(line, &start);
	if (store_vector(&cone->apex, arg, line))
		return (ft_free((void **)&arg), 1);
	arg = next_and_advance(line, &start, arg);
	if (store_orientation(&cone->axis, arg, line))
		return (ft_free((void **)&arg), 1);
	arg = next_and_advance(line, &start, arg);
	if (store_angle(&cone->angle, arg, line))
		return (ft_free((void **)&arg), 1);
	cone->angle_rad = cone->angle * M_PI / 180;
	arg = next_and_advance(line, &start, arg);
	if (store_double(&cone->height, arg, line))
		return (ft_free((void **)&arg), 1);
	arg = next_and_advance(line, &start, arg);
	if (store_color(&cone->color, arg, line))
		return (ft_free((void **)&arg), 1);
	if (store_co_bonus(cone, line, arg, &start))
		return (1);
	return (0);
}

// Function to store the sphere in the file structure
// Returns 0 if the sphere was stored successfully
// Returns 1 if an error occured
int	store_cone(t_file *file, char *line)
{
	t_cone		*cone;
	t_dclst		*node;

	cone = malloc(sizeof(t_cone));
	if (!cone)
		return (perror("Error\nMalloc failed"), 1);
	ft_memset(cone, 0, sizeof(t_cone));
	cone->mlx_ptr = file->mlx_ptr;
	if (fill_cone_from_line(cone, line))
		return (ft_free((void **)&cone), 1);
	node = dclst_add_back(file->obj_list, cone);
	if (!node)
		return (ft_free((void **)&cone),
			perror("Error\nMalloc failed"), 1);
	cone->shininess = 32;
	node->type = CO;
	return (0);
}
