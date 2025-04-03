/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 10:13:25 by christophed       #+#    #+#             */
/*   Updated: 2025/04/03 10:29:59 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

// Function to initialize the file structure
// with the default values
// Returns 0 if the initialization was successful
// Returns 1 if an error occured
static int	init_file_structure(t_file *file)
{
	ft_memset(file, 0, sizeof(t_file));
	file->obj_list = ft_calloc(1, sizeof(t_dclst *));
	if (!file->obj_list)
		return (perror("Error\nMalloc failed"), 1);
	file->camera.direction.x = 1;
	file->camera.fov = 1;
	file->ambient_light.ratio = 1;
	file->light_list = ft_calloc(1, sizeof(t_list *));
	if (!file->light_list)
		return (perror("Error\nMalloc failed\n"), 1);
	return (0);
}

// Function end the parsing process
// and free the file structure if an error occured
// Returns 1
static int	end_parse_error(t_file *file, int fd)
{
	char	*line;

	(void)file;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		ft_free((void **)&line);
	}
	delete_file(file);
	return (1);
}

// Function to parse the file descriptor
// and store the information in a t_file structure
// Returns 0 if the parsing was successful
// Returns 1 if an error occured
static int	parsing_loop(int fd, t_file *file)
{
	char	*line;

	line = NULL;
	while (1)
	{
		ft_free((void **)&line);
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[0] == '\n' || line[0] == '\0')
			continue ;
		if (is_object(line))
		{
			if (store_object(file, line))
				return (ft_free((void **)&line), end_parse_error(file, fd));
		}
		else if (is_scene(line))
		{
			if (store_scene(file, line))
				return (ft_free((void **)&line), end_parse_error(file, fd));
		}
	}
	return (0);
}

// Function to parse the file descriptor
// and store the information in a t_file structure
// Returns the t_file structure if the parsing was successful
// Returns NULL if an error occured
static t_file	*parse_fd(int fd)
{
	t_file	*file;

	file = (t_file *) malloc(sizeof(t_file));
	if (!file)
		return (perror("Error\nMalloc failed"), NULL);
	if (init_file_structure(file))
		return (free(file), NULL);
	if (parsing_loop(fd, file))
		return (NULL);
	return (file);
}

// Function to parse the input file
// and store the information in a t_file structure
// Returns the t_file structure if the parsing was successful
// Returns NULL if an error occured
t_file	*parse_input(char *input)
{
	int		fd;
	t_file	*file;

	if (check_input_file(input))
		return (NULL);
	fd = open(input, O_RDONLY);
	if (fd == -1)
		return (perror("Error\nOpening file"), NULL);
	file = NULL;
	file = parse_fd(fd);
	if (!file)
		return (close(fd), NULL);
	if (close(fd) == -1)
		return (perror("Error\nClosing file"), delete_file(file), NULL);
	return (file);
}
