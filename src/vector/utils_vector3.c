#include "../includes/miniRT.h"

// Fonction pour calculer le produit scalaire
double	dot_vector(t_vector a, t_vector b)
{
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}
// Fonction pour verifier si les vecteurs se croisent
t_vector	cross_vector(t_vector a, t_vector b)
{
	t_vector	result;

	result.x = (a.y * b.z) - (a.z * b.y);
	result.y = (a.z * b.x) - (a.x * b.z);
	result.z = (a.x * b.y) - (a.y * b.x);
	return (result); 
}
// Fonction pour calculer la distance du vecteur
double	distance_vector(t_vector a, t_vector b)
{
	double	x;
	double	y;
	double	z;

	x = a.x - b.x;
	y = a.y - b.y;
	z = a.z - b.z;
	x = pow(x, 2);
	y = pow(y, 2);
	z = pow(z, 2);
	return (sqrt(x + y + z));
}
// Fonction pour inverser la valeur du vecteur
t_vector	inv_vector(t_vector vector)
{
	vector.x = -vector.x;
	vector.y = -vector.y;
	vector.z = -vector.z;
	return (vector);
}
// Fonction pour normaliser les vecteurs
void	normalize_vector(t_vector *vector)
{
	double	norm;

	norm = sqrt((pow(vector->x, 2)) + (pow(vector->y, 2)) + (pow(vector->z, 2)));
	if (norm > 1e-6)
	{
		vector->x = vector->x / norm;
		vector->y = vector->y / norm;
		vector->z = vector->z / norm;
	}
}

