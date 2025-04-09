/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_bonus_sphere.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 20:27:34 by christophed       #+#    #+#             */
/*   Updated: 2025/04/09 09:32:50 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

// Function to store the xpm file in the structure
// Returns arg
char	*store_sp_xpm(t_sphere *sphere, char *arg, char *line,
	size_t *start)
{
	arg = next_and_advance(line, start, arg);
	if (!sphere->xpm)
		sphere->xpm = store_xpm(arg, sphere->mlx_ptr);
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
