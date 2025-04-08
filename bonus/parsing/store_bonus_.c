/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:28:42 by christophed       #+#    #+#             */
/*   Updated: 2025/04/08 16:30:41 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

// Function to store the cone bonus parameters in the structure
// Returns 0 if the plane was stored successfully
// Returns 1 if an error occured
int	store_co_bonus(t_cone *cone, char *line, char *arg, size_t *start)
{
	cone->shininess = 32;
	cone->scale = 1;
	create_ortho_basis(cone->axis, &cone->u, &cone->v);
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
		else if (!ft_strncmp(arg, "sc", 2))
			arg = store_co_scale(cone, arg, line, start);
		else
			arg = next_and_advance(line, start, arg);
		if (!arg)
			break ;
	}
	return (ft_free((void **)&arg), 0);
}

// Function to store the plane bonus parameters in the structure
// Returns 0 if the plane was stored successfully
// Returns 1 if an error occured
int	store_cy_bonus(t_cylinder *cyl, char *line, char *arg,
	size_t *start)
{
	cyl->shininess = 32;
	cyl->scale = 1;
	create_ortho_basis(cyl->orientation, &cyl->u, &cyl->v);
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
		else if (!ft_strncmp(arg, "sc", 2))
			arg = store_cy_scale(cyl, arg, line, start);
		else
			arg = next_and_advance(line, start, arg);
		if (!arg)
			break ;
	}
	return (ft_free((void **)&arg), 0);
}

// Function to store the plane bonus parameters in the structure
// Returns 0 if the plane was stored successfully
// Returns 1 if an error occured
int	store_pl_bonus(t_plane *plane, char *line, char *arg,
	size_t *start)
{
	plane->shininess = 32;
	plane->scale = 1;
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
		else if (!ft_strncmp(arg, "sc", 2))
			arg = store_pl_scale(plane, arg, line, start);
		else
			arg = next_and_advance(line, start, arg);
		if (!arg)
			break ;
	}
	return (ft_free((void **)&arg), 0);
}

// Function to store the plane bonus parameters in the structure
// Returns 0 if the plane was stored successfully
// Returns 1 if an error occured
int	store_sp_bonus(t_sphere *sphere, char *line, char *arg,
	size_t *start)
{
	sphere->shininess = 32;
	sphere->scale = 1;
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
		else if (!ft_strncmp(arg, "xp", 2))
			arg = store_sp_xpm(sphere, arg, line, start);
		else if (!ft_strncmp(arg, "sc", 2))
			arg = store_sp_scale(sphere, arg, line, start);
		else
			arg = next_and_advance(line, start, arg);
		if (!arg)
			break ;
	}
	return (ft_free((void **)&arg), 0);
}
