#include "../../includes/miniRT.h"

// Function to check if the line is a scene line ('A', 'C' or 'L')
// Returns 1 if the line is a scene line
// Returns 0 if the line is not a scene line
int	is_scene(char *str)
{
	if (!str || *str == '\0' || *str == '\n')
		return (0);
	if (ft_strlen(str) < 1)
		return (0);
	if (str[0] == 'A' || str[0] == 'C' || str[0] == 'L')
		return (1);
	return (0);
}

// Function to check if the line is an object line ('sp', 'pl' or 'cy')
// Returns 1 if the line is an object line
// Returns 0 if the line is not an object line
int	is_object(char *str)
{
	if (!str || *str == '\0' || *str == '\n')
		return (0);
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

// Function to check if the argument is a valid vector
// Returns 1 if the argument is a valid vector
// Returns 0 if the argument is not a valid vector
int	ft_isvector(char *str)
{
	char	**tab;

	if (!str || *str == '\0' || *str == '\n')
		return (0);
	tab = ft_split(str, ',');
	if (!tab)
		return (0);
	if (str_array_size(tab) != 3)
		return (delete_str_array(tab), 0);
	if (!ft_isdouble(tab[0]) || !ft_isdouble(tab[1]) || !ft_isdouble(tab[2]))
		return (delete_str_array(tab), 0);
	delete_str_array(tab);
	return (1);
}

// Function to check if the argument is a valid normal vector
// Returns 1 if the argument is a valid normal vector
// Returns 0 if the argument is not a valid normal vector
int	ft_isorientation(char *str)
{
	char	**tab;
	double	n[3];
	int		i;

	if (!str || *str == '\0' || *str == '\n')
		return (0);
	if (!ft_isvector(str))
		return (0);
	tab = ft_split(str, ',');
	if (!tab)
		return (0);
	i = -1;
	while (++i < 3)
		n[i] = ft_atod(tab[i]);
	i = -1;
	while (++i < 3)
	{
		if (n[i] < -1 || n[i] > 1)
			return (pars_err_msg("invalid vector", str),
				delete_str_array(tab), 0);
	}
	if (n[0] == 0 && n[1] == 0 && n[2] == 0)
		return (pars_err_msg("invalid vector", str), delete_str_array(tab), 0);
	return (delete_str_array(tab), 1);
}

// Function to check if the argument is a valid ratio
// Returns 1 if the argument is a valid ratio
// Returns 0 if the argument is not a valid ratio
int	ft_isratio(char *str)
{
	double	n;

	if (!str || *str == '\0' || *str == '\n')
		return (0);
	if (!ft_isdouble(str))
		return (0);
	n = ft_atod(str);
	if (n < 0 || n > 1)
		return (0);
	return (1);
}
