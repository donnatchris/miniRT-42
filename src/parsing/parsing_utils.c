#include "../../includes/miniRT.h"

// Function to count the size of an array of strings
// Returns the size of the array or 0 if the array does not exist
size_t	str_array_size(char **array)
{
	size_t	size;

	if (!array)
		return (0);
	size = 0;
	while (array[size])
		size++;
	return (size);
}

// Function to free an array of strings and put all its pointers to NULL
void	delete_str_array(char **array)
{
	size_t	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		ft_free(array[i]);
		i++;
	}
	ft_free(array);
}

char	*next_arg(char *line, size_t start)
{
	char	*arg;
	int		end;

	arg = NULL;
	while (ft_strchr(WHITESPACE, line[start]))
		start++;
	if (line[start] == '\0' || '\n')
		return (NULL);
	end = start + 1;
	while (!ft_strchr(WHITESPACE, line[end]) && line[end] != '\0' && line[end] != '\n')
		end++;
	arg = ft_substr(line, start, end - start - 1);
	return (arg);
}

int	store_vector(t_vector *vector, char *arg)
{
	char	**coordonates;

	coordonates = NULL;
	coordonates = ft_split(arg, ',');
	if (!coordonates || str_array_size(coordonates) != 3)
		return (delete_str_array(coordonates), 1);
	if (!ft_isint(coordonates[0]))
		return (delete_str_array(coordonates), 1);
	vector->x = ft_atoi(coordonates[0]);
	if (!ft_isint(coordonates[1]))
		return (delete_str_array(coordonates), 1);
	vector->x = ft_atoi(coordonates[0]);
	if (!ft_isint(coordonates[2]))
		return (delete_str_array(coordonates), 1);
	vector->x = ft_atoi(coordonates[0]);
		return (delete_str_array(coordonates), 0);
}
