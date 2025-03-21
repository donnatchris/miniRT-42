#include "../../includes/miniRT.h"

int	store_sphere(t_file *file, char *line)
{
	t_sphere *sphere;
	t_dclst	*node;
	size_t	start;
	char	*arg;

	sphere = (t_sphere *) malloc(sizeof(t_sphere));
	if (!sphere)
		return (perror("malloc failed"), 1);
	start = 2;
	arg = next_arg(line, start);
	if (!arg || !ft_isvector(arg))
		return (ft_free(arg), ft_free(sphere), 1);
	store_vector(&sphere->position, arg);
	start = start + ft_strlen(arg) + 1;
	ft_free(arg);
	if (line[start] == '\0' || line[start] == '\n')
		return (ft_free(sphere), 1);
	arg = next_arg(line, start);
	if (!arg || !ft_isdouble(arg))
		return (ft_free(arg), ft_free(sphere), 1);
	sphere->diameter = ft_atod(arg);
	if (sphere->diameter < 0)	//controle
		return (ft_free(arg), ft_free(sphere), 1);
	start = start + ft_strlen(arg) + 1;
	ft_free(arg);
	if (line[start] == '\0' || line[start] == '\n')
		return (ft_free(sphere), 1);
	arg = next_arg(line, start);
	if (!arg || !ft_iscolor(arg))
		return (ft_free(arg), ft_free(sphere), 1);
	sphere->color = ft_atoc(arg);
	ft_free(arg);
	node = dclst_add_back(file->obj_list, sphere);
	if (!node)
		return (ft_free(sphere), perror("malloc failed"), 1);
	node->type = SP;
	return (0);
}
