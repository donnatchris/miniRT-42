/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 10:13:53 by christophed       #+#    #+#             */
/*   Updated: 2025/04/08 08:56:17 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

// Function to store the camera in the file structure
// Returns 0 if the scene was stored successfully
// Returns 1 if an error occured
int	store_camera(t_file *file, char *line)
{
	size_t		start;
	char		*arg;
	static int	cam = 0;

	if (cam++ > 0)
		return (ft_putstr_fd("Error\nToo many cameras in file\n", 2), 1);
	start = 1;
	arg = next_arg(line, &start);
	if (store_vector(&file->camera.origin, arg, line))
		return (ft_free((void **)&arg), 1);
	arg = next_and_advance(line, &start, arg);
	if (store_orientation(&file->camera.direction, arg, line))
		return (ft_free((void **)&arg), 1);
	arg = next_and_advance(line, &start, arg);
	if (store_angle(&file->camera.fov, arg, line))
		return (ft_free((void **)&arg), 1);
	return (ft_free((void **)&arg), 0);
}

// Function to store the ambient light in the file structure
// Returns 0 if the ambient light was stored successfully
// Returns 1 if an error occured
int	store_ambient(t_file *file, char *line)
{
	size_t		start;
	char		*arg;
	static int	ambient = 0;

	if (ambient++ > 0)
		return (ft_putstr_fd("Error\nToo many ambient in file\n", 2), 1);
	start = 1;
	arg = next_arg(line, &start);
	if (store_ratio(&file->ambient_light.ratio, arg, line))
		return (ft_free((void **)&arg), 1);
	arg = next_and_advance(line, &start, arg);
	if (store_color(&file->ambient_light.color, arg, line))
		return (ft_free((void **)&arg), 1);
	return (ft_free((void **)&arg), 0);
}

// Function to store one or more lights in the file structure
// (in a linked list)
// Returns 0 if the light was stored successfully
// Returns 1 if an error occured
int	store_light(t_file *file, char *line)
{
	size_t		start;
	char		*arg;
	t_light		*light;
	t_list		*node;

	light = (t_light *) malloc(sizeof(t_light));
	if (!light)
		return (perror("Error\nMalloc failed\n"), 1);
	start = 1;
	arg = next_arg(line, &start);
	if (store_vector(&light->position, arg, line))
		return (ft_free((void **)&arg), 1);
	arg = next_and_advance(line, &start, arg);
	if (store_ratio(&light->ratio, arg, line))
		return (ft_free((void **)&arg), 1);
	arg = next_and_advance(line, &start, arg);
	if (store_color(&light->color, arg, line))
		return (ft_free((void **)&arg), 1);
	node = ft_lstnew((void *) light);
	if (!node)
		return (ft_free((void **)&arg), perror("Error\nMalloc failed\n"), 1);
	ft_lstadd_back(file->light_list, node);
	return (ft_free((void **)&arg), 0);
}
