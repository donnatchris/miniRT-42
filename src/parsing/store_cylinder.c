#include "../../includes/miniRT.h"

int	store_cylinder(t_file *file, char *line)
{
	t_cylinder	*cylinder;
	t_dclst		*node;
	size_t		start;
	char		*arg;

	cylinder = (t_cylinder *) malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (perror("malloc failed"), 1);
	start = 2;
	arg = next_arg(line, start);
	if (!arg || !ft_isvector(arg))
		return (ft_free(arg), ft_free(cylinder), 1);
	store_vector(&cylinder->position, arg);
	start = start + ft_strlen(arg) + 1;
	ft_free(arg);
	if (line[start] == '\0' || line[start] == '\n')
		return (ft_free(cylinder), 1);
	arg = next_arg(line, start);
	if (!arg || !ft_isorientation(arg))
		return (ft_free(arg), ft_free(cylinder), 1);
	store_vector(&cylinder->normal, arg);
	start = start + ft_strlen(arg) + 1;
	ft_free(arg);
	if (line[start] == '\0' || line[start] == '\n')
		return (ft_free(cylinder), 1);
	arg = next_arg(line, start);
	if (!arg || !ft_isdouble(arg))
		return (ft_free(arg), ft_free(cylinder), 1);
	cylinder->diameter = ft_atod(arg);
	if (cylinder->diameter <= 0)
		return (ft_free(arg), ft_free(cylinder), 1);
	start = start + ft_strlen(arg) + 1;
	ft_free(arg);
	if (line[start] == '\0' || line[start] == '\n')
		return (ft_free(cylinder), 1);
	arg = next_arg(line, start);
	if (!arg || !ft_isdouble(arg))
		return (ft_free(arg), ft_free(cylinder), 1);
	cylinder->height = ft_atod(arg);
	if (cylinder->height <= 0)
		return (ft_free(arg), ft_free(cylinder), 1);
	start = start + ft_strlen(arg) + 1;
	ft_free(arg);
	if (line[start] == '\0' || line[start] == '\n')
		return (ft_free(cylinder), 1);
	arg = next_arg(line, start);
	if (!arg || !ft_iscolor(arg))
		return (ft_free(arg), ft_free(cylinder), 1);
	cylinder->color = ft_atoc(arg);
	ft_free(arg);
	node = dclst_add_back(file->obj_list, cylinder);
	if (!node)
		return (ft_free(cylinder), perror("malloc failed"), 1);
	node->type = CY;
	return (0);
}
