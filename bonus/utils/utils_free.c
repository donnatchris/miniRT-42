/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 16:50:29 by olthorel          #+#    #+#             */
/*   Updated: 2025/04/08 10:47:28 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

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

void	delete_light_list(void *content)
{
	free(content);
	return ;
}

void	delete_file(t_file *file)
{
	if (!file)
		return ;
	if (file->light_list)
	{
		ft_lstclear(file->light_list, &delete_light_list);
		free(file->light_list);
	}
	if (file->obj_list)
		dclst_clear(file->obj_list);
	ft_free((void **)&file);
}

void	delete_program(t_program *program)
{
	if (!program)
		return ;
	delete_file(program->file);
	if (program->img && program->img->img_ptr)
		mlx_destroy_image(program->mlx, program->img->img_ptr);
	free(program->img);
	mlx_destroy_window(program->mlx, program->win);
	mlx_destroy_display(program->mlx);
	free(program->mlx);
	free(program);
}
