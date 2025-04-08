/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_bonus_cylinder.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 20:39:27 by christophed       #+#    #+#             */
/*   Updated: 2025/04/08 16:43:18 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

// Function to store the xpm in the structure
// Returns arg
char	*store_cy_xpm(t_cylinder *cyl, char *arg, char *line,
	size_t *start)
{
	arg = next_and_advance(line, start, arg);
	cyl->xpm = store_xpm(arg, cyl->mlx_ptr);
	return (arg);
}

// Function to store the shininess parameter in the structure
// Returns arg
char	*store_cy_shininess(t_cylinder *cy, char *arg, char *line,
	size_t *start)
{
	arg = next_and_advance(line, start, arg);
	store_scale(&cy->shininess, arg, line);
	return (arg);
}

// Function to store the chessboard parameters in the structure
// (The chessboard parameters are the color and the scale)
// Returns 0 if the chessboard was stored successfully
// Returns 1 if an error occured
char	*store_cy_chessboard(t_cylinder *cylinder, char *arg, char *line,
	size_t *start)
{
	arg = next_and_advance(line, start, arg);
	if (store_color(&cylinder->color2, arg, line))
		return (arg);
	cylinder->chessboard = 1;
	return (arg);
}

// Function to store the reflectivity parameter in the structure
// Returns arg
char	*store_cy_reflectivity(t_cylinder *cy, char *arg, char *line,
	size_t *start)
{
	arg = next_and_advance(line, start, arg);
	store_ratio(&cy->reflectivity, arg, line);
	return (arg);
}

char	*store_cy_scale(t_cylinder *cyl, char *arg, char *line,
	size_t *start)
{
	arg = next_and_advance(line, start, arg);
	store_double(&cyl->scale, arg, line);
	return (arg);
}
