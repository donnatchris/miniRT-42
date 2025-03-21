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

static t_file	*parse_fd(int fd)
{
	t_file	*file;
	char	*line;

	file = (t_file *) malloc(sizeof(t_file));
	if (!file)
		return (perror("malloc failed"), NULL);
	ft_memset(file, 0, sizeof(file));
	file->obj_list = (t_dclst **) malloc(sizeof(t_dclst *));
	if (!file->obj_list)
		return (perror("malloc failed"), ft_free(file), NULL);
	file->obj_list = NULL;
	line = NULL;
	while (1)
	{
		ft_free(line);
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[0] == '\n' || line[0] == '\0')
			continue ;
		if (is_object(line))
			store_object(file, line);
		else if (is_scene(line))
			store_scene(file, line);
	}
	return (ft_free(line), file);
}

t_file	*parse_input(char *input)
{
	int		fd;
	t_file	*file;

	fd = open(input, O_RDONLY);
	if (fd == -1)
		return (perror("Error opening file"), NULL);
	file = parse_fd(fd);
	if (!file)
		return (NULL);
	if (close(fd) == -1)
		return (perror("Error closing file"), NULL);	//passer par la fonction qui va tout free
	return (file);
}
// Attention, une fois file retourné, il faut controler sa validité
