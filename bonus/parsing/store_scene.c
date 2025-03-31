/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 10:13:53 by christophed       #+#    #+#             */
/*   Updated: 2025/03/31 11:32:35 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

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

int	store_light(t_file *file, char *line)
{
	size_t		start;
	char		*arg;
	static int	light = 0;

	if (light++ > 0)
		return (ft_putstr_fd("Error\nToo many lights in file\n", 2), 1);
	start = 1;
	arg = next_arg(line, &start);
	if (store_vector(&file->light.position, arg, line))
		return (ft_free((void **)&arg), 1);
	arg = next_and_advance(line, &start, arg);
	if (store_ratio(&file->light.ratio, arg, line))
		return (ft_free((void **)&arg), 1);
	arg = next_and_advance(line, &start, arg);
	if (store_color(&file->light.color, arg, line))
		return (ft_free((void **)&arg), 1);
	return (ft_free((void **)&arg), 0);
}
