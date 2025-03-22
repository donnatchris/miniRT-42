#include "../../includes/miniRT.h"

// Function to fill the sphere structure from the line
// Returns 0 if the sphere was filled successfully
// Returns 1 if an error occured
static int	fill_sphere_from_line(t_sphere *sphere, char *line)
{
	size_t	start;
	char	*arg;

	start = 2;
	arg = next_arg(line, start);
	if (store_vector(&sphere->position, arg, line))
		return (ft_free((void **)&arg), 1);
	arg = next_and_advance(line, &start, arg);
	if (store_double(&sphere->diameter, arg, line) || sphere->diameter <= 0)
		return (ft_free((void **)&arg), 1);
	arg = next_and_advance(line, &start, arg);
	if (store_color(&sphere->color, arg, line))
		return (ft_free((void **)&arg), 1);
	return (ft_free((void **)&arg), 0);
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
		return (perror("malloc failed"), 1);
	if (fill_sphere_from_line(sphere, line))
		return (ft_free((void **)&sphere), 1);
	node = dclst_add_back(file->obj_list, sphere);
	if (!node)
		return (ft_free((void **)&sphere), perror("malloc failed"), 1);
	node->type = SP;
	return (0);
}
