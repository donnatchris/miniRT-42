#include "../../includes/miniRT.h"

static int	is_scene(char *str)
{
	if (ft_strlen(str) < 1)
		return (0);
	if (str[0] == 'A' || str[0] == 'C' || str[0] == 'L')
		return (1);
	return (0);
}

static int	is_object(char *str)
{
	if (ft_strlen(str) < 2)
		return (0);
	if (!ft_strncmp(str, "sp", 2))
		return (1);
	if (!ft_strncmp(str, "pl", 2))
		return (1);
	if (!ft_strncmp(str, "cy", 2))
		return (1);
	return (0);
}

static int	store_object(t_file *file, char *line)
{
	if (!ft_strncmp(line, "sp", 2))
	{
		return(store_sphere(file, line));
	}
	else if (!ft_strncmp(line, "pl", 2))
	{
		return(store_plane(file, line));
	}
	else if (!ft_strncmp(line, "cy", 2))
	{
		return(store_cylinder(file, line));
	}
	else
		return (1);
}

static int	init_file_structure(t_file *file)
{
	ft_memset(file, 0, sizeof(t_file *));
	file->obj_list = ft_calloc(1, sizeof(t_dclst *));
	if (!file->obj_list)
		return (perror("malloc failed"), ft_free((void **)&file), 1);
	file->camera.direction.x = 1;
	file->camera.fov = 1;
	file->light.ratio = 1;
	file->ambient_light.ratio = 1;
	return (0);
}

static t_file	*parse_fd(int fd)
{
	t_file	*file;
	char	*line;

	file = (t_file *) malloc(sizeof(t_file));
	if (!file)
		return (perror("malloc failed"), NULL);
	if (init_file_structure(file))
		return (NULL);
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
				return (ft_free((void **)&line), delete_file(file), NULL);
		}
		else if (is_scene(line))
		{
			if (store_scene(file, line))
				return (ft_free((void **)&line), delete_file(file), NULL);
		}
	}
	return (ft_free((void **)&line), file);
}

t_file	*parse_input(char *input)
{
	int		fd;
	t_file	*file;

	fd = open(input, O_RDONLY);
	if (fd == -1)
		return (perror("Error opening file"), NULL);
	file = NULL;
	file = parse_fd(fd);
	if (!file)
		return (NULL);
	if (close(fd) == -1)
		return (perror("Error closing file"),  delete_file(file), NULL);
	return (file);
}
