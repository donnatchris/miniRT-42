#include "../includes/miniRT.h"

double ft_atod(char *str)
{
	double	result;
	double	decimal;
	double	div;
	int		sign;

	decimal = 0.0;
	div = 1.0;
	sign = 1;
	// Vérification du signe
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	// Vérifier si la chaîne est vide ou commence mal
	if (!ft_isdigit(*str) && *str != '.')
		return (0.0);
	// Vérifier si la chaîne commence directement par un "." mais n'a rien après
	if (*str == '.' && !ft_isdigit(*(str + 1)))
		return (0.0);
	// Conversion de la partie entière
	result = (double)ft_atoi(str);
	// Avancer `str` après la partie entière
	while (*str && ft_isdigit(*str))
		str++;
	// Gestion de la partie fractionnaire
	if (*str == '.')
	{
		str++; // Passer le '.'

		while (*str && ft_isdigit(*str))
		{
			decimal += (double)(*str - 48) / (div *= 10.0);
			str++;
		}
	}
	// Vérifier qu'on est bien à la fin de la chaîne (éviter "12.34abc")
	if (*str != '\0')
		return (0.0);
	// Retourner le résultat final avec le bon signe
	return ((result + decimal) * sign);
}

int ft_atoc(char *str)
{
	int		result;

	result = ft_atoi(str);
	if (result < 0)
		return (0);
	if (result > 255)
		return (255);
	return (result);
}
