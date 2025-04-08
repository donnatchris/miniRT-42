/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_bonus_sphere.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 20:27:34 by christophed       #+#    #+#             */
/*   Updated: 2025/04/08 16:43:03 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

// Function to store the xpm file in the structure
// Returns arg
char	*store_sp_xpm(t_sphere *sphere, char *arg, char *line,
	size_t *start)
{
	arg = next_and_advance(line, start, arg);
	sphere->xpm = store_xpm(arg, sphere->mlx_ptr);
	return (arg);
}

// Function to store the shininess parameter in the structure
// Returns arg
char	*store_sp_shininess(t_sphere *sphere, char *arg, char *line,
	size_t *start)
{
	arg = next_and_advance(line, start, arg);
	store_scale(&sphere->shininess, arg, line);
	return (arg);
}

// Function to store the chessboard parameters in the structure
// (The chessboard parameters are the color and the scale)
// Returns arg
char	*store_sp_chessboard(t_sphere *sphere, char *arg, char *line,
	size_t *start)
{
	arg = next_and_advance(line, start, arg);
	if (store_color(&sphere->color2, arg, line))
		return (arg);
	sphere->chessboard = 1;
	return (arg);
}

// Function to store the reflectivity parameter in the structure
// Returns arg
char	*store_sp_reflectivity(t_sphere *sphere, char *arg, char *line,
	size_t *start)
{
	arg = next_and_advance(line, start, arg);
	store_ratio(&sphere->reflectivity, arg, line);
	return (arg);
}

char	*store_sp_scale(t_sphere *sphere, char *arg, char *line,
	size_t *start)
{
	arg = next_and_advance(line, start, arg);
	store_double(&sphere->scale, arg, line);
	return (arg);
}
