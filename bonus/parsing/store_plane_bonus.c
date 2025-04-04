/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_plane_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 20:34:40 by christophed       #+#    #+#             */
/*   Updated: 2025/04/04 12:07:59 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

static char	*store_pl_xpm(t_plane *plane, char *arg, char *line,
	size_t *start)
{
		arg = next_and_advance(line, start, arg);
		plane->xpm = store_xpm(arg, plane->mlx_ptr);
		return (arg);
}

// Function to store the shininess parameter in the structure
// Returns arg
static char	*store_pl_shininess(t_plane *plane, char *arg, char *line,
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
static char	*store_pl_chessboard(t_plane *plane, char *arg, char *line,
	size_t *start)
{
	arg = next_and_advance(line, start, arg);
	if (store_color(&plane->color2, arg, line))
		return (arg);
	arg = next_and_advance(line, start, arg);
	if (store_scale(&plane->scale, arg, line))
		return (arg);
	plane->chessboard = 1;
	return (arg);
}

static char	*store_pl_reflectivity(t_plane *pl, char *arg, char *line,
	size_t *start)
{
	arg = next_and_advance(line, start, arg);
	store_ratio(&pl->reflectivity, arg, line);
	return (arg);
}

// Function to store the plane bonus parameters in the structure
// Returns 0 if the plane was stored successfully
// Returns 1 if an error occured
int	store_pl_bonus(t_plane *plane, char *line, char *arg,
	size_t *start)
{
	plane->shininess = 32;
	create_ortho_basis(plane->normal, &plane->u, &plane->v);
	arg = next_and_advance(line, start, arg);
	while (1)
	{
		if (!arg)
			break ;
		if (!ft_strncmp(arg, "ch", 2))
			arg = store_pl_chessboard(plane, arg, line, start);
		else if (!ft_strncmp(arg, "sh", 2))
			arg = store_pl_shininess(plane, arg, line, start);
		else if (!ft_strncmp(arg, "re", 2))
			arg = store_pl_reflectivity(plane, arg, line, start);
		else if (!ft_strncmp(arg, "xp", 2))
			arg = store_pl_xpm(plane, arg, line, start);
		else
			arg = next_and_advance(line, start, arg);
		if (!arg)
			break ;
	}
	return (ft_free((void **)&arg), 0);
}
