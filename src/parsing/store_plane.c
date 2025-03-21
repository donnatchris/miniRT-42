#include "../../includes/miniRT.h"

int	store_plane(t_file *file, char *line)
{
	t_plane	*plane;
	t_dclst	*node;
	size_t	start;
	char	*arg;

	plane = (t_plane *) malloc(sizeof(t_plane));
	if (!plane)
		return (perror("malloc failed"), 1);
	start = 2;
	arg = next_arg(line, start);
	if (!arg || !ft_isvector(arg))
		return (ft_free((void **)&arg), ft_free((void **)&plane), 1);
	store_vector(&plane->position, arg);
	start = start + ft_strlen(arg) + 1;
	ft_free((void **)&arg);
    if (line[start] == '\0' || line[start] == '\n')
		return (ft_free((void **)&plane), 1);
    arg = next_arg(line, start);
	if (!arg || !ft_isorientation(arg))
		return (ft_free((void **)&arg), ft_free((void **)&plane), 1);
	store_vector(&plane->normal, arg);
	start = start + ft_strlen(arg) + 1;
	ft_free((void **)&arg);
    if (line[start] == '\0' || line[start] == '\n')
		return (ft_free((void **)&plane), 1);
	arg = next_arg(line, start);
	if (!arg || !ft_iscolor(arg))
		return (ft_free((void **)&arg), ft_free((void **)&plane), 1);
	plane->color = ft_atoc(arg);
	ft_free((void **)&arg);
    node = dclst_add_back(file->obj_list, plane);
	if (!node)
		return (ft_free((void **)&plane), perror("malloc failed"), 1);
	node->type = PL;
	return (0);
}
