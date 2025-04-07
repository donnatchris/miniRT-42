/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_cylinder_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 20:39:27 by christophed       #+#    #+#             */
/*   Updated: 2025/04/07 14:33:59 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

static char	*store_cy_xpm(t_cylinder *cyl, char *arg, char *line,
	size_t *start)
{
		arg = next_and_advance(line, start, arg);
		cyl->xpm = store_xpm(arg, cyl->mlx_ptr);
		return (arg);
}

// Function to store the shininess parameter in the structure
// Returns arg
static char	*store_cy_shininess(t_cylinder *cy, char *arg, char *line,
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
static char	*store_cy_chessboard(t_cylinder *cylinder, char *arg, char *line,
	size_t *start)
{
	arg = next_and_advance(line, start, arg);
	if (store_color(&cylinder->color2, arg, line))
		return (arg);
	arg = next_and_advance(line, start, arg);
	if (store_scale(&cylinder->scale, arg, line))
		return (arg);
	cylinder->chessboard = 1;
	return (arg);
}

static char	*store_cy_reflectivity(t_cylinder *cy, char *arg, char *line,
	size_t *start)
{
	arg = next_and_advance(line, start, arg);
	store_ratio(&cy->reflectivity, arg, line);
	return (arg);
}

// Function to store the plane bonus parameters in the structure
// Returns 0 if the plane was stored successfully
// Returns 1 if an error occured
int	store_cy_bonus(t_cylinder *cyl, char *line, char *arg,
	size_t *start)
{
	create_ortho_basis(cyl->orientation, &cyl->u, &cyl->v);
	cyl->shininess = 32;
	arg = next_and_advance(line, start, arg);
	while (1)
	{
		if (!arg)
			break ;
		if (!ft_strncmp(arg, "ch", 2))
			arg = store_cy_chessboard(cyl, arg, line, start);
		else if (!ft_strncmp(arg, "sh", 2))
			arg = store_cy_shininess(cyl, arg, line, start);
		else if (!ft_strncmp(arg, "re", 2))
			arg = store_cy_reflectivity(cyl, arg, line, start);
		else if (!ft_strncmp(arg, "xp", 2))
			arg = store_cy_xpm(cyl, arg, line, start);
		else
			arg = next_and_advance(line, start, arg);
		if (!arg)
			break ;
	}
	return (ft_free((void **)&arg), 0);
}
