/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_cone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 10:13:57 by christophed       #+#    #+#             */
/*   Updated: 2025/04/01 09:27:06 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

// Function to store the shininess parameter in the structure
// Returns arg
// static char	*store_sp_shininess(t_sphere *sphere, char *arg, char *line, size_t *start)
// {
// 	arg = next_and_advance(line, start, arg);
// 	if (store_scale(&sphere->shininess, arg, line))
// 		return (ft_free((void **)&arg), NULL);
// 	return (arg);
// }

// // Function to store the chessboard parameters in the structure
// // (The chessboard parameters are the color and the scale)
// // Returns arg
// static char	*store_sp_chessboard(t_sphere *sphere, char *arg, char *line, size_t *start)
// {
// 	arg = next_and_advance(line, start, arg);
// 	if (store_color(&sphere->color2, arg, line))
// 		return (ft_free((void **)&arg), NULL);
// 	arg = next_and_advance(line, start, arg);
// 	if (store_scale(&sphere->scale, arg, line))
// 		return (ft_free((void **)&arg), NULL);
// 	sphere->chessboard = 1;
// 	return (arg);
// }

// // Function to store the plane bonus parameters in the structure
// // Returns 0 if the plane was stored successfully
// // Returns 1 if an error occured
// static int	store_co_bonus(t_sphere *sphere, char *line, char *arg, size_t *start)
// {
// 	sphere->shininess = 32;
// 	while (1)
// 	{
// 		arg = next_and_advance(line, start, arg);
// 		if (!arg)
// 			break ;
// 		if (!ft_strncmp(arg, "ch", 2))
// 			arg = store_sp_chessboard(sphere, arg, line, start);
// 		if (!ft_strncmp(arg, "sh", 2))
// 			arg = store_sp_shininess(sphere, arg, line, start);
// 		if (!arg)
// 			break ;
// 	}
// 	return (ft_free((void **)&arg), 0);
// }

// Function to fill the sphere structure from the line
// Returns 0 if the sphere was filled successfully
// Returns 1 if an error occured
static int	fill_cone_from_line(t_cone *cone, char *line)
{
	size_t	start;
	char	*arg;

	start = 2;
	arg = next_arg(line, &start);
	if (store_vector(&cone->apex, arg, line))
		return (ft_free((void **)&arg), 1);
	arg = next_and_advance(line, &start, arg);
	if (store_orientation(&cone->axis, arg, line))
		return (ft_free((void **)&arg), 1);
	arg = next_and_advance(line, &start, arg);
	if (store_angle(&cone->angle, arg, line))
		return (ft_free((void **)&arg), 1);
	cone->angle_rad = cone->angle * M_PI / 180;
	arg = next_and_advance(line, &start, arg);
	if (store_double(&cone->height, arg, line) || cone->height <= 0)
		return (ft_free((void **)&arg), 1);
	arg = next_and_advance(line, &start, arg);
	if (store_color(&cone->color, arg, line))
		return (ft_free((void **)&arg), 1);
	// if (store_sp_bonus(cone, line, arg, &start))
	// 	return (1);
	return (0);
}

// Function to store the sphere in the file structure
// Returns 0 if the sphere was stored successfully
// Returns 1 if an error occured
int	store_cone(t_file *file, char *line)
{
	t_cone		*cone;
	t_dclst		*node;

	cone = malloc(sizeof(t_cone));
	if (!cone)
		return (perror("Error\nMalloc failed"), 1);
	ft_memset(cone, 0, sizeof(t_cone));
	if (fill_cone_from_line(cone, line))
		return (ft_free((void **)&cone), 1);
	node = dclst_add_back(file->obj_list, cone);
	if (!node)
		return (ft_free((void **)&cone),
			perror("Error\nMalloc failed"), 1);
	node->type = CO;
	return (0);
}
