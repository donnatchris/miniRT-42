/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_triangle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 08:47:35 by christophed       #+#    #+#             */
/*   Updated: 2025/04/08 08:47:47 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

// Function to fill the plane structure from the line
// Returns 0 if the plane was filled successfully
// Returns 1 if an error occured
static int	fill_triangle_from_line(t_triangle *triangle, char *line)
{
	size_t	start;
	char	*arg;

	start = 2;
	arg = next_arg(line, &start);
	if (store_vector(&triangle->vertex[0], arg, line))
		return (ft_free((void **)&arg), 1);
	arg = next_and_advance(line, &start, arg);
	if (store_vector(&triangle->vertex[1], arg, line))
		return (ft_free((void **)&arg), 1);
	arg = next_and_advance(line, &start, arg);
	if (store_vector(&triangle->vertex[2], arg, line))
		return (ft_free((void **)&arg), 1);
	arg = next_and_advance(line, &start, arg);
	if (store_color(&triangle->color, arg, line))
		return (ft_free((void **)&arg), 1);
	return (ft_free((void **)&arg), 0);
}

// Function to store the plane in the file structure
// Returns 0 if the plane was stored successfully
// Returns 1 if an error occured
int	store_triangle(t_file *file, char *line)
{
	t_triangle	*triangle;
	t_dclst		*node;

	triangle = malloc(sizeof(t_triangle));
	if (!triangle)
		return (perror("Error\nMalloc failed"), 1);
	if (fill_triangle_from_line(triangle, line))
		return (ft_free((void **)&triangle), 1);
	node = dclst_add_back(file->obj_list, triangle);
	if (!node)
		return (ft_free((void **)&triangle), perror("Error\nMalloc failed"), 1);
	node->type = TR;
	return (0);
}
