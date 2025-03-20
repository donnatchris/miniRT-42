#include "../../includes/miniRT.h"
typedef struct s_sphere
{
	int			type;
	t_vector	position;
	double		diameter;
	int			color;
}	t_sphere;

static int	store_sphere(t_file *file, char *line)
{
	t_sphere *sphere;
	t_dclst	*node;
	size_t	start;
	char	*arg;

	sphere = (t_sphere *) malloc(sizeof(t_sphere));
	if (!sphere)
		return (perror("malloc failed"), 1);
	sphere->type = SP;
	start = 1;
	arg = next_arg(line, start);
	if (!arg || !ft_isvector(arg))
		return (ft_free(arg), 1);
	store_vector(&sphere->position, arg);
	start = start + ft_strlen(arg);
	ft_free(arg);
	if (line[start] == '\0' || line[start] == '\n')
		return (1);
	arg = next_arg(line, start);
	if (!arg || !ft_isdouble(arg))
		return (ft_free(arg), 1);
	sphere->diameter = ft_atod(arg);
	start = start + ft_strlen(arg);
	ft_free(arg);
	if (line[start] == '\0' || line[start] == '\n')
		return (1);
	arg = next_arg(line, start);
	if (!arg || !ft_iscolor(arg))
		return (ft_free(arg), 1);
	sphere->color = ft_atoc(arg);
	ft_free(arg);
	node = dclst_add_back(file->obj_list, sphere);
	if (!node)
		return (ft_free(sphere), perror("malloc failed"), 1);
	return (0);
}

int	store_object(t_file *file, char *line)
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
