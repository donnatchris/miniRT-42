#include "../../includes/miniRT.h"

// Function to store an angle in the structure
// Returns 0 if the angle was stored successfully
// Returns 1 if an error occured
int	store_angle(int *storage, char *arg, char *line)
{
	if (!ft_isangle(arg))
		return (pars_err_msg("invalid angle", line));
	*storage = ft_atoi(arg);
	return (0);
}

// Function to store a double in the structure
// Returns 0 if the double was stored successfully
// Returns 1 if an error occured
int	store_double(double *storage, char *arg, char *line)
{
	if (!ft_isdouble(arg))
		return (pars_err_msg("invalid double", line));
	*storage = ft_atod(arg);
	return (0);
}

// Function to store a ratio in the structure
// Returns 0 if the ratio was stored successfully
// Returns 1 if an error occured
int	store_ratio(double *storage, char *arg, char *line)
{
	if (!ft_isratio(arg))
		return (pars_err_msg("invalid ratio", line));
	*storage = ft_atod(arg);
	return (0);
}

// Function to store a color in the structure
// Returns 0 if the color was stored successfully
// Returns 1 if an error occured
int	store_color(int *storage, char *arg, char *line)
{
	if (!ft_iscolor(arg))
		return (pars_err_msg("invalid color", line));
	*storage = ft_atoc(arg);
	return (0);
}
