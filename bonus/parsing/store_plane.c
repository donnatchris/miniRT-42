/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 10:13:48 by christophed       #+#    #+#             */
/*   Updated: 2025/04/01 16:59:38 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"



// Function to store the chessboard parameters in the structure
// (The chessboard parameters are the color and the scale)
// Returns 0 if the chessboard was stored successfully
// Returns 1 if an error occured
static char	*store_pl_chessboard(t_plane *plane, char *arg, char *line, size_t *start)
{
	arg = next_and_advance(line, start, arg);
	if (store_color(&plane->color2, arg, line))
		return (ft_free((void **)&arg), NULL);
	arg = next_and_advance(line, start, arg);
	if (store_scale(&plane->scale, arg, line))
		return (ft_free((void **)&arg), NULL);
	plane->chessboard = 1;
	return (arg);
}

// Function to store the plane bonus parameters in the structure
// Returns 0 if the plane was stored successfully
// Returns 1 if an error occured
static int	store_pl_bonus(t_plane *plane, char *line, char *arg, size_t *start)
{
	plane->shininess = 32;
	create_ortho_basis(plane->normal, &plane->u, &plane->v);
	while (1)
	{
		arg = next_and_advance(line, start, arg);
		if (!arg)
			break ;
		if (!ft_strncmp(arg, "ch", 2))
			arg = store_pl_chessboard(plane, arg, line, start);
		if (!ft_strncmp(arg, "xp", 2))
			arg = store_pl_xpm(plane, arg, line, start);
		if (!arg)
			break ;
	}
	return (0);
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
	if (store_pl_bonus(plane, line, arg, &start))
		return (1);
	return (0);
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
	ft_memset(plane, 0, sizeof(t_plane));
	if (fill_plane_from_line(plane, line))
		return (ft_free((void **)&plane), 1);
	node = dclst_add_back(file->obj_list, plane);
	if (!node)
		return (ft_free((void **)&plane), perror("Error\nMalloc failed"), 1);
	node->type = PL;
	return (0);
}
