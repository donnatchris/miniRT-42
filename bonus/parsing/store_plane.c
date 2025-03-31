/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 10:13:48 by christophed       #+#    #+#             */
/*   Updated: 2025/03/31 10:11:27 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT_bonus.h"

// Function to fill the plane structure from the line
// Returns 0 if the plane was filled successfully
// Returns 1 if an error occured
static int	fill_plane_from_line(t_plane *plane, char *line)
{
	size_t	start;
	char	*arg;

	start = 2;
	arg = next_arg(line, &start);
	if (store_vector(&plane->position, arg, line))
		return (ft_free((void **)&arg), 1);
	arg = next_and_advance(line, &start, arg);
	if (store_orientation(&plane->normal, arg, line))
		return (ft_free((void **)&arg), 1);
	arg = next_and_advance(line, &start, arg);
	if (store_color(&plane->color, arg, line))
		return (ft_free((void **)&arg), 1);
	return (ft_free((void **)&arg), 0);
}

// Function to store the plane in the file structure
// Returns 0 if the plane was stored successfully
// Returns 1 if an error occured
int	store_plane(t_file *file, char *line)
{
	t_plane	*plane;
	t_dclst	*node;

	plane = malloc(sizeof(t_plane));
	if (!plane)
		return (perror("malloc failed"), 1);
	if (fill_plane_from_line(plane, line))
		return (ft_free((void **)&plane), 1);
	node = dclst_add_back(file->obj_list, plane);
	if (!node)
		return (ft_free((void **)&plane), perror("malloc failed"), 1);
	node->type = PL;
	return (0);
}
