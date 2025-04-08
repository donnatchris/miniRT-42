/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_bonus_plane.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 20:34:40 by christophed       #+#    #+#             */
/*   Updated: 2025/04/08 16:40:26 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

// Function to store the xpm in the structure
// Returns arg
char	*store_pl_xpm(t_plane *plane, char *arg, char *line,
	size_t *start)
{
	arg = next_and_advance(line, start, arg);
	plane->xpm = store_xpm(arg, plane->mlx_ptr);
	return (arg);
}

// Function to store the shininess parameter in the structure
// Returns arg
char	*store_pl_shininess(t_plane *plane, char *arg, char *line,
	size_t *start)
{
	arg = next_and_advance(line, start, arg);
	store_scale(&plane->shininess, arg, line);
	return (arg);
}

// Function to store the chessboard parameters in the structure
// (The chessboard parameters are the color and the scale)
// Returns 0 if the chessboard was stored successfully
// Returns 1 if an error occured
char	*store_pl_chessboard(t_plane *plane, char *arg, char *line,
	size_t *start)
{
	arg = next_and_advance(line, start, arg);
	if (store_color(&plane->color2, arg, line))
		return (arg);
	plane->chessboard = 1;
	return (arg);
}

// Function to store the reflectivity parameter in the structure
// Returns arg
char	*store_pl_reflectivity(t_plane *pl, char *arg, char *line,
	size_t *start)
{
	arg = next_and_advance(line, start, arg);
	store_ratio(&pl->reflectivity, arg, line);
	return (arg);
}

char	*store_pl_scale(t_plane *plane, char *arg, char *line,
	size_t *start)
{
	arg = next_and_advance(line, start, arg);
	store_double(&plane->scale, arg, line);
	return (arg);
}
