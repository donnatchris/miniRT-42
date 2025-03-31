/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 10:14:06 by christophed       #+#    #+#             */
/*   Updated: 2025/03/31 10:11:44 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT_bonus.h"

// Function to store a vector in the structure
// Returns 0 if the vector was stored successfully
// Returns 1 if an error occured
int	store_vector(t_vector *vector, char *arg, char *line)
{
	char	**coordonates;

	if (!ft_isvector(arg))
		return (pars_err_msg("invalid vector", line));
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
		return (pars_err_msg("invalid vector", line));
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
