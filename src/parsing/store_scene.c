#include "../../includes/miniRT.h"

// need ft_isdouble ft_iscolor, ft_isvector, ft_isint

static int	store_ambient(t_file *file, char *line)
{
	size_t	start;
	char	*arg;

	start = 1;
	arg = next_arg(line, start);
	if (!arg || !ft_isdouble(arg))
		return (ft_free(arg), 1);
	file->ambient_light.ratio = ft_atod(arg);
	start = start + ft_strlen(arg);
	ft_free(arg);
	if (line[start] == '\0' || line[start] == '\n')
		return (1);
	arg = next_arg(line, start);
	if (!arg || !ft_iscolor(arg))
		return (ft_free(arg), 1);
	file->ambient_light.color = ft_atoc(arg);
	return (ft_free(arg), 0);
}

static int	store_camera(t_file *file, char *line)
{
	size_t	start;
	char	*arg;

	start = 1;
	arg = next_arg(line, start);
	if (!arg || !ft_isvector(arg))
		return (ft_free(arg), 1);
	store_vector(&file->camera.origin, arg);
	start = start + ft_strlen(arg);
	ft_free(arg);
	if (line[start] == '\0' || line[start] == '\n')
		return (1);
	arg = next_arg(line, start);
	if (!arg || !ft_isvector(arg))
		return (ft_free(arg), 1);
	store_vector(&file->camera.direction, arg);
	start = start + ft_strlen(arg);
	ft_free(arg);
	if (line[start] == '\0' || line[start] == '\n')
		return (1);
	arg = next_arg(line, start);
	if (!arg || !ft_isdouble(arg))
		return (ft_free(arg), 1);
	file->camera.fov = ft_atod(arg);
	return (ft_free(arg), 0);
}

static int	store_light(t_file *file, char *line)
{
	size_t	start;
	char	*arg;

	start = 1;
	arg = next_arg(line, start);
	if (!arg || !ft_isvector(arg))
		return (ft_free(arg), 1);
	store_vector(&file->light.position, arg);
	start = start + ft_strlen(arg);
	ft_free(arg);
	if (line[start] == '\0' || line[start] == '\n')
		return (1);
	arg = next_arg(line, start);
	if (!arg || !ft_isdouble(arg))
		return (ft_free(arg), 1);
	file->light.ratio = ft_atod(arg);
	start = start + ft_strlen(arg);
	ft_free(arg);
	if (line[start] == '\0' || line[start] == '\n')
		return (1);
	arg = next_arg(line, start);
	if (!arg || !ft_iscolor(arg))
		return (ft_free(arg), 1);
	file->light.color = ft_atoc(arg);
	return (ft_free(arg), 0);
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
