#include "../../includes/miniRT.h"

// need ft_isdouble ft_iscolor, ft_isvector, ft_isint

static int	store_ambient(t_file *file, char *line)
{
	size_t		start;
	char		*arg;
	static int	ambient = 0;

	if (ambient > 0)
		return (printf("Too many ambient in file\n"), 1);
	ambient++;
	start = 1;
	arg = next_arg(line, start);
	if (!arg || !ft_isratio(arg))
		return (ft_free((void **)&arg), 1);
	file->ambient_light.ratio = ft_atod(arg);
	start = start + ft_strlen(arg) + 1;
	ft_free((void **)&arg);
	if (line[start] == '\0' || line[start] == '\n')
		return (1);
	arg = next_arg(line, start);
	if (!arg || !ft_iscolor(arg))
		return (ft_free((void **)&arg), 1);
	file->ambient_light.color = ft_atoc(arg);
	return (ft_free((void **)&arg), 0);
}

static int	store_camera(t_file *file, char *line)
{
	size_t		start;
	char		*arg;
	static int	cam = 0;

	if (cam > 0)
		return (printf("Too many cameras in file\n"), 1);
	cam++;
	start = 1;
	arg = next_arg(line, start);
	if (!arg || !ft_isvector(arg))
		return (ft_free((void **)&arg), 1);
	store_vector(&file->camera.origin, arg);
	start = start + ft_strlen(arg) + 1;
	ft_free((void **)&arg);
	if (line[start] == '\0' || line[start] == '\n')
		return (1);
	arg = next_arg(line, start);
	if (!arg || !ft_isorientation(arg))
		return (ft_free((void **)&arg), 1);
	store_vector(&file->camera.direction, arg);
	start = start + ft_strlen(arg) + 1;
	ft_free((void **)&arg);
	if (line[start] == '\0' || line[start] == '\n')
		return (1);
	arg = next_arg(line, start);
	if (!arg || !ft_isangle(arg))
		return (ft_free((void **)&arg), 1);
	file->camera.fov = ft_atoi(arg);
	return (ft_free((void **)&arg), 0);
}

static int	store_light(t_file *file, char *line)
{
	size_t		start;
	char		*arg;
	static int	light = 0;

	if (light > 0)
		return (printf("Too many lights in file\n"), 1);
	light++;
	start = 1;
	arg = next_arg(line, start);
	if (!arg || !ft_isvector(arg))
		return (ft_free((void **)&arg), 1);
	store_vector(&file->light.position, arg);
	start = start + ft_strlen(arg) + 1;
	ft_free((void **)&arg);
	if (line[start] == '\0' || line[start] == '\n')
		return (1);
	arg = next_arg(line, start);
	if (!arg || !ft_isratio(arg))
		return (ft_free((void **)&arg), 1);
	file->light.ratio = ft_atod(arg);
	start = start + ft_strlen(arg) + 1;
	ft_free((void **)&arg);
	if (line[start] == '\0' || line[start] == '\n')
		return (1);
	arg = next_arg(line, start);
	if (!arg || !ft_iscolor(arg))
		return (ft_free((void **)&arg), 1);
	file->light.color = ft_atoc(arg);
	return (ft_free((void **)&arg), 0);
}

int store_scene(t_file *file, char *line)
{
	if (line[0] == 'A')	// manque a controler si jamais il y a plus d'un A
	{
		if (store_ambient(file, line))
			return (1);
	}
	else if (line[0] == 'C')
	{
		if (store_camera(file, line))
			return (1);
	}
	else if (line[0] == 'L')
	{
		if (store_light(file, line))
			return (1);
	}
	else
		return (1);
	return (0);
}
