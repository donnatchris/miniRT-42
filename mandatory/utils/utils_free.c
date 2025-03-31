/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 16:50:29 by olthorel          #+#    #+#             */
/*   Updated: 2025/03/31 11:17:19 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	ft_free(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	delete_str_array(char **array)
{
	size_t	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		ft_free((void **)&array[i]);
		i++;
	}
	ft_free((void **)&array);
}

void	delete_file(t_file *file)
{
	if (!file)
		return ;
	if (file->obj_list)
		dclst_clear(file->obj_list);
	ft_free((void **)&file);
}

void	delete_program(t_program *program)
{
	if (!program)
		return ;
	delete_file(program->file);
	mlx_destroy_image(program->mlx, program->img->img_ptr);
	free(program->img);
	mlx_destroy_window(program->mlx, program->win);
	mlx_destroy_display(program->mlx);
	free(program->mlx);
	free(program);
}
