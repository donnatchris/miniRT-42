/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_bonus_cone.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 20:42:16 by christophed       #+#    #+#             */
/*   Updated: 2025/04/09 09:32:02 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

// Function to store the xpm in the structure
// Returns arg
char	*store_co_xpm(t_cone *cone, char *arg, char *line,
	size_t *start)
{
	arg = next_and_advance(line, start, arg);
	if (!cone->xpm)
		cone->xpm = store_xpm(arg, cone->mlx_ptr);
	else
	{
		ft_putstr_fd("Error\nImage: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("\nfrom line: ", 2);
		ft_putstr_fd(line, 2);
		ft_putstr_fd("\nhas been ignored ", 2);
		ft_putstr_fd("(previous image already stored in object)\n", 2);
	}
	return (arg);
}

// Function to store the shininess parameter in the structure
// Returns arg
char	*store_co_shininess(t_cone *cone, char *arg, char *line,
	size_t *start)
{
	arg = next_and_advance(line, start, arg);
	store_scale(&cone->shininess, arg, line);
	return (arg);
}

// Function to store the chessboard parameters in the structure
// (The chessboard parameters are the color and the scale)
// Returns arg
char	*store_co_chessboard(t_cone *cone, char *arg, char *line,
	size_t *start)
{
	arg = next_and_advance(line, start, arg);
	if (store_color(&cone->color2, arg, line))
		return (arg);
	cone->chessboard = 1;
	return (arg);
}

// Function to store the reflectivity parameter in the structure
// Returns arg
char	*store_co_reflectivity(t_cone *cone, char *arg, char *line,
	size_t *start)
{
	arg = next_and_advance(line, start, arg);
	store_ratio(&cone->reflectivity, arg, line);
	return (arg);
}

char	*store_co_scale(t_cone *cone, char *arg, char *line,
	size_t *start)
{
	arg = next_and_advance(line, start, arg);
	store_double(&cone->scale, arg, line);
	return (arg);
}
