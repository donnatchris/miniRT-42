/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 10:13:38 by christophed       #+#    #+#             */
/*   Updated: 2025/04/04 10:55:23 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

// Function to store the scene elements in the file structure
// (ambient light, camera and light)
// Returns 0 if the scene was stored successfully
// Returns 1 if an error occured
int	store_scene(t_file *file, char *line)
{
	if (line[0] == 'A')
		return (store_ambient(file, line));
	else if (line[0] == 'C')
		return (store_camera(file, line));
	else if (line[0] == 'L')
		return (store_light(file, line));
	return (1);
}

// Function to store the object in the file structure
// (sphere, plane or cylinder)
// Returns 0 if the object was stored successfully
// Returns 1 if an error occured
int	store_object(t_file *file, char *line)
{
	if (!ft_strncmp(line, "sp", 2))
		return (store_sphere(file, line));
	else if (!ft_strncmp(line, "pl", 2))
		return (store_plane(file, line));
	else if (!ft_strncmp(line, "cy", 2))
		return (store_cylinder(file, line));
	else if (!ft_strncmp(line, "tr", 2))
		return (store_triangle(file, line));
	else if (!ft_strncmp(line, "co", 2))
		return (store_cone(file, line));
	else
		return (1);
}
