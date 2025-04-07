/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_cone_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 20:42:16 by christophed       #+#    #+#             */
/*   Updated: 2025/04/07 14:43:41 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

static char	*store_co_xpm(t_cone *cone, char *arg, char *line,
	size_t *start)
{
		arg = next_and_advance(line, start, arg);
		cone->xpm = store_xpm(arg, cone->mlx_ptr);
		return (arg);
}

// Function to store the shininess parameter in the structure
// Returns arg
static char	*store_co_shininess(t_cone *cone, char *arg, char *line,
	size_t *start)
{
	arg = next_and_advance(line, start, arg);
	store_scale(&cone->shininess, arg, line);
	return (arg);
}

// Function to store the chessboard parameters in the structure
// (The chessboard parameters are the color and the scale)
// Returns arg
static char	*store_co_chessboard(t_cone *cone, char *arg, char *line,
	size_t *start)
{
	arg = next_and_advance(line, start, arg);
	if (store_color(&cone->color2, arg, line))
		return (arg);
	arg = next_and_advance(line, start, arg);
	if (store_scale(&cone->scale, arg, line))
		return (arg);
	cone->chessboard = 1;
	return (arg);
}

static char	*store_co_reflectivity(t_cone *cone, char *arg, char *line,
	size_t *start)
{
	arg = next_and_advance(line, start, arg);
	store_ratio(&cone->reflectivity, arg, line);
	return (arg);
}

// Function to store the cone bonus parameters in the structure
// Returns 0 if the plane was stored successfully
// Returns 1 if an error occured
int	store_co_bonus(t_cone *cone, char *line, char *arg, size_t *start)
{
	create_ortho_basis(cone->axis, &cone->u, &cone->v);
	cone->shininess = 32;
	arg = next_and_advance(line, start, arg);
	while (1)
	{
		if (!arg)
			break ;
		if (!ft_strncmp(arg, "ch", 2))
			arg = store_co_chessboard(cone, arg, line, start);
		else if (!ft_strncmp(arg, "sh", 2))
			arg = store_co_shininess(cone, arg, line, start);
		else if (!ft_strncmp(arg, "re", 2))
			arg = store_co_reflectivity(cone, arg, line, start);
		else if (!ft_strncmp(arg, "xp", 2))
			arg = store_co_xpm(cone, arg, line, start);
		else
			arg = next_and_advance(line, start, arg);
		if (!arg)
			break ;
	}
	return (ft_free((void **)&arg), 0);
}
