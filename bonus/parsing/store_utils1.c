/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 10:14:02 by christophed       #+#    #+#             */
/*   Updated: 2025/03/31 19:47:54 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

// Function to store an angle in the structure
// Returns 0 if the angle was stored successfully
// Returns 1 if an error occured
int	store_angle(int *storage, char *arg, char *line)
{
	if (!ft_isangle(arg))
		return (pars_err_msg("Invalid angle", line));
	*storage = ft_atoi(arg);
	return (0);
}

// Function to store a double in the structure
// Returns 0 if the double was stored successfully
// Returns 1 if an error occured
int	store_double(double *storage, char *arg, char *line)
{
	if (!ft_isdouble(arg))
		return (pars_err_msg("Invalid double", line));
	*storage = ft_atod(arg);
	return (0);
}

// Function to store a ratio in the structure
// Returns 0 if the ratio was stored successfully
// Returns 1 if an error occured
int	store_ratio(double *storage, char *arg, char *line)
{
	if (!ft_isratio(arg))
		return (pars_err_msg("Invalid ratio", line));
	*storage = ft_atod(arg);
	return (0);
}

// Function to store a color in the structure
// Returns 0 if the color was stored successfully
// Returns 1 if an error occured
int	store_color(int *storage, char *arg, char *line)
{
	if (!ft_iscolor(arg))
		return (pars_err_msg("Invalid color", line));
	*storage = ft_atoc(arg);
	return (0);
}

// Function to store an angle in the structure
// Returns 0 if the angle was stored successfully
// Returns 1 if an error occured
int	store_scale(int *storage, char *arg, char *line)
{
	if (!ft_isint(arg))
		return (pars_err_msg("Invalid scale", line));
	*storage = ft_atoi(arg);
	if (storage <= 0)
		return (pars_err_msg("Invalid scale", line));
	return (0);
}
