#include "../includes/miniRT.h"

// Fonction init vecteurs
t_vector	vector(double x, double y, double z)
{
	t_vector	result;

	result.x = x;
	result.y = y;
	result.z = z;
	return (result);
}
// Fontion pour calculer la taille du vecteur
double	len_vector(t_vector v)
{
	return (sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z)));
}
// Fonction pour soustraire deux vecteurs
t_vector	sub_vector(t_vector a, t_vector b)
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
t_vector	*scale_vector(t_vector *vector, t_camera *ray, double scale)
{
	vector->x = ray->origin.x + scale * ray->direction.x;
	vector->y = ray->origin.y + scale * ray->direction.y;
	vector->z = ray->origin.z + scale * ray->direction.z;
	return (vector);
}
