/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_xpm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 08:58:08 by christophed       #+#    #+#             */
/*   Updated: 2025/04/09 09:22:43 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

// Function to print the error message
// Returns NULL
void	*xpm_error(char *file)
{
	ft_putstr_fd("Error\n", 2);
	if (file)
	{
		ft_putstr_fd("Unable to create image from file: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd("\n", 2);
	}
	else
	{
		ft_putstr_fd("Unable to create image ", 2);
		ft_putstr_fd("(invalid file or mlx_ptr)\n", 2);
	}
	return (NULL);
}

// Function to store the xpm in the structure
// Returns the xpm structure
// Returns NULL if an error occured
t_xpm	*store_xpm(char *file, void *mlx_ptr)
{
	t_xpm	*xpm;

	if (!file || !mlx_ptr)
		return (xpm_error(NULL));
	xpm = (t_xpm *) malloc(sizeof(t_xpm));
	if (!xpm)
		return (perror("Error\nXPM Malloc failed"), NULL);
	ft_memset(xpm, 0, sizeof(t_xpm));
	xpm->mlx_ptr = mlx_ptr;
	xpm->img_ptr = mlx_xpm_file_to_image(xpm->mlx_ptr, file, &xpm->width,
			&xpm->height);
	if (!xpm->img_ptr)
		return (free(xpm), xpm_error(file));
	xpm->img_addr = mlx_get_data_addr(xpm->img_ptr, &xpm->bpp,
			&xpm->size_line, &xpm->endian);
	if (!xpm->img_addr)
		return (delete_xpm(xpm), xpm_error(file));
	printf("Image: %s has been loaded successfully\n", file);
	return (xpm);
}
