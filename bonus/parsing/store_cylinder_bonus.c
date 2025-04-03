/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_cylinder_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 20:39:27 by christophed       #+#    #+#             */
/*   Updated: 2025/04/03 20:40:26 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

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
int	store_cy_bonus(t_cylinder *cylinder, char *line, char *arg,
	size_t *start)
{
	cylinder->shininess = 32;
	arg = next_and_advance(line, start, arg);
	while (1)
	{
		if (!arg)
			break ;
		if (!ft_strncmp(arg, "ch", 2))
			arg = store_cy_chessboard(cylinder, arg, line, start);
		else if (!ft_strncmp(arg, "sh", 2))
			arg = store_cy_shininess(cylinder, arg, line, start);
		else if (!ft_strncmp(arg, "re", 2))
			arg = store_cy_reflectivity(cylinder, arg, line, start);
		else
			arg = next_and_advance(line, start, arg);
		if (!arg)
			break ;
	}
	return (ft_free((void **)&arg), 0);
}
