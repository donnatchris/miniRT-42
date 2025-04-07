/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_sphere_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 20:27:34 by christophed       #+#    #+#             */
/*   Updated: 2025/04/07 11:08:41 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

static char	*store_sp_xpm(t_sphere *sphere, char *arg, char *line,
	size_t *start)
{
		arg = next_and_advance(line, start, arg);
		sphere->xpm = store_xpm(arg, sphere->mlx_ptr);
		return (arg);
}

// Function to store the shininess parameter in the structure
// Returns arg
static char	*store_sp_shininess(t_sphere *sphere, char *arg, char *line,
	size_t *start)
{
	arg = next_and_advance(line, start, arg);
	store_scale(&sphere->shininess, arg, line);
	return (arg);
}

// Function to store the chessboard parameters in the structure
// (The chessboard parameters are the color and the scale)
// Returns arg
static char	*store_sp_chessboard(t_sphere *sphere, char *arg, char *line,
	size_t *start)
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

static char	*store_sp_reflectivity(t_sphere *sphere, char *arg, char *line,
	size_t *start)
{
	arg = next_and_advance(line, start, arg);
	store_ratio(&sphere->reflectivity, arg, line);
	return (arg);
}

// Function to store the plane bonus parameters in the structure
// Returns 0 if the plane was stored successfully
// Returns 1 if an error occured
int	store_sp_bonus(t_sphere *sphere, char *line, char *arg,
	size_t *start)
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
		else if (!ft_strncmp(arg, "xp", 2))
			arg = store_sp_xpm(sphere, arg, line, start);
		else
			arg = next_and_advance(line, start, arg);
		if (!arg)
			break ;
	}
	return (ft_free((void **)&arg), 0);
}
