/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 10:13:48 by christophed       #+#    #+#             */
/*   Updated: 2025/03/31 16:00:13 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

static void	create_pl_ortho(t_plane *plane)
{
	t_vector	up;

	if (fabs(plane->normal.y) < 0.999)
		up = (t_vector){0, 1, 0};
	else
		up = (t_vector){1, 0, 0};
	plane->u = cross_vector(up, plane->normal);
	normalize_vector(&plane->u);
	plane->v = cross_vector(plane->normal, plane->u);
	normalize_vector(&plane->v);
}

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
	arg = next_and_advance(line, &start, arg);
	if (!arg)
	{
		plane->color2 = plane->color;
		plane->scale = 10;
	}
	else
	{
		if (store_color(&plane->color2, arg, line))
			return (ft_free((void **)&arg), 1);
		arg = next_and_advance(line, &start, arg);
		if (store_scale(&plane->scale, arg, line))
			plane->scale = 10;
	}
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
		return (perror("Error\nMalloc failed"), 1);
	if (fill_plane_from_line(plane, line))
		return (ft_free((void **)&plane), 1);
	node = dclst_add_back(file->obj_list, plane);
	if (!node)
		return (ft_free((void **)&plane), perror("Error\nMalloc failed"), 1);
	create_pl_ortho(plane);
	node->type = PL;
	return (0);
}
