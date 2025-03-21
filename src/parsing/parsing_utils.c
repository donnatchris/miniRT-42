#include "../../includes/miniRT.h"

char	*next_arg(char *line, size_t start)
{
	char	*arg;
	int		end;

	arg = NULL;
	while (ft_strchr(WHITESPACE, line[start]))
		start++;
	if (line[start] == '\0' || line[start] == '\n')
		return (NULL);
	end = start + 1;
	while (!ft_strchr(WHITESPACE, line[end]) && line[end] != '\0' && line[end] != '\n')
		end++;
	arg = ft_substr(line, start, end - start);

	// printf("ARG : %s\n", arg);

	return (arg);
}

int	store_vector(t_vector *vector, char *arg)
{
	char	**coordonates;

	coordonates = NULL;
	coordonates = ft_split(arg, ',');
	if (!coordonates || str_array_size(coordonates) != 3)
		return (delete_str_array(coordonates), 1);
	vector->x = ft_atod(coordonates[0]);
	vector->y = ft_atod(coordonates[1]);
	vector->z = ft_atod(coordonates[2]);
	return (delete_str_array(coordonates), 0);
}
