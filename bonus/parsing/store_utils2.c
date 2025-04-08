/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 10:14:06 by christophed       #+#    #+#             */
/*   Updated: 2025/04/08 08:51:45 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

// Function to store a vector in the structure
// Returns 0 if the vector was stored successfully
// Returns 1 if an error occured
int	store_vector(t_vector *vector, char *arg, char *line)
{
	char	**coordonates;

	if (!ft_isvector(arg))
		return (pars_err_msg("Invalid vector", line));
	coordonates = NULL;
	coordonates = ft_split(arg, ',');
	if (!coordonates || str_array_size(coordonates) != 3)
		return (delete_str_array(coordonates), 1);
	vector->x = ft_atod(coordonates[0]);
	vector->y = ft_atod(coordonates[1]);
	vector->z = ft_atod(coordonates[2]);
	return (delete_str_array(coordonates), 0);
}

// Function to store an orientation vector in the structure
// Returns 0 if the orientation vector was stored successfully
// Returns 1 if an error occured
int	store_orientation(t_vector *vector, char *arg, char *line)
{
	char	**coordonates;

	if (!ft_isvector(arg))
		return (pars_err_msg("Invalid vector", line));
	coordonates = NULL;
	coordonates = ft_split(arg, ',');
	if (!coordonates || str_array_size(coordonates) != 3)
		return (delete_str_array(coordonates), 1);
	vector->x = ft_atod(coordonates[0]);
	vector->y = ft_atod(coordonates[1]);
	vector->z = ft_atod(coordonates[2]);
	normalize_vector(vector);
	return (delete_str_array(coordonates), 0);
}

// Function to create an orthonormal basis from a normal vector
// The function takes a normal vector and two pointers to store the
// orthonormal basis vectors u and v
void	create_ortho_basis(t_vector normal, t_vector *u, t_vector *v)
{
	t_vector	up;

	if (fabs(normal.y) < 0.999)
		up = (t_vector){0, 1, 0};
	else
		up = (t_vector){1, 0, 0};
	*u = cross_vector(up, normal);
	normalize_vector(u);
	*v = cross_vector(normal, *u);
	normalize_vector(v);
}
