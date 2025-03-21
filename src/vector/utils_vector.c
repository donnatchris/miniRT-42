#include "../includes/miniRT.h"

int	ft_isvector(char *str)
{
	char **tab;

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

// Fonction pour normaliser les vecteurs
void	normalize_vector(t_vector *vector)
{
	double	norm;

	norm = sqrt((pow(vector->x, 2)) + (pow(vector->y, 2)) + (pow(vector->z, 2)));
	if (norm != 0.0)
	{
		vector->x = vector->x / norm;
		vector->y = vector->y / norm;
		vector->z = vector->z / norm;
	}
}
