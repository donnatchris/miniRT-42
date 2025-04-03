/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 10:13:57 by christophed       #+#    #+#             */
/*   Updated: 2025/04/03 14:40:47 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

// Function to store the shininess parameter in the structure
// Returns arg
static char	*store_sp_shininess(t_sphere *sphere, char *arg, char *line, size_t *start)
{
	arg = next_and_advance(line, start, arg);
	store_scale(&sphere->shininess, arg, line);
	return (arg);
}

// Function to store the chessboard parameters in the structure
// (The chessboard parameters are the color and the scale)
// Returns arg
static char	*store_sp_chessboard(t_sphere *sphere, char *arg, char *line, size_t *start)
{
	arg = next_and_advance(line, start, arg);
	if (store_color(&sphere->color2, arg, line))
		return (arg);
	arg = next_and_advance(line, start, arg);
	if (store_scale(&sphere->scale, arg, line))
		return (arg);
	sphere->chessboard = 1;
	return (arg);
}

static char	*store_sp_reflectivity(t_sphere *sphere, char *arg, char *line, size_t *start)
{
	arg = next_and_advance(line, start, arg);
	store_ratio(&sphere->reflectivity, arg, line);
	return (arg);
}

// Function to store the plane bonus parameters in the structure
// Returns 0 if the plane was stored successfully
// Returns 1 if an error occured
static int	store_sp_bonus(t_sphere *sphere, char *line, char *arg, size_t *start)
{
	sphere->shininess = 32;
	arg = next_and_advance(line, start, arg);
	while (1)
	{
		if (!arg)
			break ;
		if (!ft_strncmp(arg, "ch", 2))
			arg = store_sp_chessboard(sphere, arg, line, start);
		else if (!ft_strncmp(arg, "sh", 2))
			arg = store_sp_shininess(sphere, arg, line, start);
		else if (!ft_strncmp(arg, "re", 2))
			arg = store_sp_reflectivity(sphere, arg, line, start);
		else
			arg = next_and_advance(line, start, arg);
		if (!arg)
			break ;
	}
	return (ft_free((void **)&arg), 0);
}

// Function to fill the sphere structure from the line
// Returns 0 if the sphere was filled successfully
// Returns 1 if an error occured
static int	fill_sphere_from_line(t_sphere *sphere, char *line)
{
	size_t	start;
	char	*arg;

	start = 2;
	arg = next_arg(line, &start);
	if (store_vector(&sphere->position, arg, line))
		return (ft_free((void **)&arg), 1);
	arg = next_and_advance(line, &start, arg);
	if (store_double(&sphere->diameter, arg, line) || sphere->diameter <= 0)
		return (ft_free((void **)&arg), 1);
	arg = next_and_advance(line, &start, arg);
	if (store_color(&sphere->color, arg, line))
		return (ft_free((void **)&arg), 1);
	if (store_sp_bonus(sphere, line, arg, &start))
		return (1);
	return (0);
}

// Function to store the sphere in the file structure
// Returns 0 if the sphere was stored successfully
// Returns 1 if an error occured
int	store_sphere(t_file *file, char *line)
{
	t_sphere	*sphere;
	t_dclst		*node;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return (perror("Error\nMalloc failed"), 1);
	ft_memset(sphere, 0, sizeof(t_sphere));
	if (fill_sphere_from_line(sphere, line))
		return (ft_free((void **)&sphere), 1);
	node = dclst_add_back(file->obj_list, sphere);
	if (!node)
		return (ft_free((void **)&sphere),
			perror("Error\nMalloc failed"), 1);
	node->type = SP;
	return (0);
}
