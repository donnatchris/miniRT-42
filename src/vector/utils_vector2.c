#include "../includes/miniRT.h"

// Fonction pour calculer le produit scalaire
double	dot_vector(t_vector a, t_vector b)
{
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}
// Fonction pour soustraire deux vecteurs
t_vector	subtract_vector(t_vector a, t_vector b)
{
	t_vector	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return (result);
}
// Fonction pour additionner deux vecteurs
t_vector	add_vector(t_vector a, t_vector b)
{
	t_vector	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}
// Fonction pour multiplier chaque composant par le scalaire
t_vector	scale_vector(t_vector a, double scale)
{
	t_vector	result;

	result.x = a.x * scale;
	result.y = a.y * scale;
	result.z = a.z * scale;
	return (result);
}
