/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 10:13:43 by christophed       #+#    #+#             */
/*   Updated: 2025/04/01 09:17:12 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

// Function to store the chessboard parameters in the structure
// (The chessboard parameters are the color and the scale)
// Returns 0 if the chessboard was stored successfully
// Returns 1 if an error occured
static char	*store_cy_chessboard(t_cylinder *cylinder, char *arg, char *line, size_t *start)
{
	arg = next_and_advance(line, start, arg);
	if (store_color(&cylinder->color2, arg, line))
		return (ft_free((void **)&arg), NULL);
	arg = next_and_advance(line, start, arg);
	if (store_scale(&cylinder->scale, arg, line))
		return (ft_free((void **)&arg), NULL);
	cylinder->chessboard = 1;
	return (arg);
}

// Function to store the plane bonus parameters in the structure
// Returns 0 if the plane was stored successfully
// Returns 1 if an error occured
static int	store_cy_bonus(t_cylinder *cylinder, char *line, char *arg, size_t *start)
{
	cylinder->shininess = 32;
	while (1)
	{
		arg = next_and_advance(line, start, arg);
		if (!arg)
			break ;
		if (!ft_strncmp(arg, "ch", 2))
			arg = store_cy_chessboard(cylinder, arg, line, start);
		if (!arg)
			break ;
	}
	return (0);
}

// Function to fill the cylinder structure from the line
// Returns 0 if the cylinder was filled successfully
// Returns 1 if an error occured
static int	fill_cylinder_from_line(t_cylinder *cylinder, char *line)
{
	size_t	start;
	char	*arg;

	start = 2;
	arg = next_arg(line, &start);
	if (store_vector(&cylinder->position, arg, line))
		return (ft_free((void **)&arg), 1);
	arg = next_and_advance(line, &start, arg);
	if (store_orientation(&cylinder->orientation, arg, line))
		return (ft_free((void **)&arg), 1);
	arg = next_and_advance(line, &start, arg);
	if (store_double(&cylinder->diameter, arg, line) || cylinder->diameter <= 0)
		return (ft_free((void **)&arg), 1);
	arg = next_and_advance(line, &start, arg);
	if (store_double(&cylinder->height, arg, line) || cylinder->height <= 0)
		return (ft_free((void **)&arg), 1);
	arg = next_and_advance(line, &start, arg);
	if (store_color(&cylinder->color, arg, line))
		return (ft_free((void **)&arg), 1);
	if (store_cy_bonus(cylinder, line, arg, &start))
		return (1);
	return (0);
}

// Function to store the cylinder in the file structure
// Returns 0 if the cylinder was stored successfully
// Returns 1 if an error occured
int	store_cylinder(t_file *file, char *line)
{
	t_cylinder	*cylinder;
	t_dclst		*node;

	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (perror("Error\nMalloc failed"), 1);
	ft_memset(cylinder, 0, sizeof(t_cylinder));
	if (fill_cylinder_from_line(cylinder, line))
		return (ft_free((void **)&cylinder), 1);
	node = dclst_add_back(file->obj_list, cylinder);
	if (!node)
		return (ft_free((void **)&cylinder), perror("Error\nMalloc failed"), 1);
	node->type = CY;
	return (0);
}
