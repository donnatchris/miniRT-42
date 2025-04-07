/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 10:13:57 by christophed       #+#    #+#             */
/*   Updated: 2025/04/07 11:07:28 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

// Function to fill the sphere structure from the line
// Returns 0 if the sphere was filled successfully
// Returns 1 if an error occured
static int	fill_sphere_from_line(t_sphere *sphere, char *line)
{
	size_t	start;
	char	*arg;

	start = 2;
	arg = next_arg(line, &start);
	if (store_vector(&sphere->position, arg, line))
		return (ft_free((void **)&arg), 1);
	arg = next_and_advance(line, &start, arg);
	if (store_double(&sphere->diameter, arg, line) || sphere->diameter <= 0)
		return (ft_free((void **)&arg), 1);
	arg = next_and_advance(line, &start, arg);
	if (store_color(&sphere->color, arg, line))
		return (ft_free((void **)&arg), 1);
	if (store_sp_bonus(sphere, line, arg, &start))
		return (1);
	return (0);
}

// Function to store the sphere in the file structure
// Returns 0 if the sphere was stored successfully
// Returns 1 if an error occured
int	store_sphere(t_file *file, char *line)
{
	t_sphere	*sphere;
	t_dclst		*node;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return (perror("Error\nMalloc failed"), 1);
	ft_memset(sphere, 0, sizeof(t_sphere));
	sphere->mlx_ptr = file->mlx_ptr;		//test xpm
	if (fill_sphere_from_line(sphere, line))
		return (ft_free((void **)&sphere), 1);
	node = dclst_add_back(file->obj_list, sphere);
	if (!node)
		return (ft_free((void **)&sphere),
			perror("Error\nMalloc failed"), 1);
	node->type = SP;
	return (0);
}
