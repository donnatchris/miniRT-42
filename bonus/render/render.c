/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 22:32:59 by christophed       #+#    #+#             */
/*   Updated: 2025/04/09 11:23:51 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

static int	init_img(t_program *prog)
{
	t_image	*img;

	img = malloc(sizeof(t_image));
	if (!img)
		return (perror("Error\nMalloc img failed"), 1);
	img->img_ptr = mlx_new_image(prog->mlx, WIDTH, HEIGHT);
	if (!img->img_ptr)
		return (perror("mlx_new_image failed"), free(img), 1);
	img->addr = mlx_get_data_addr(img->img_ptr,
			&img->bpp, &img->size_line, &img->endian);
	if (!img->addr)
		return (perror("Error\nMlx_get_data_addr failed"), free(img), 1);
	prog->img = img;
	return (0);
}

void	render(t_program *prog)
{
	t_viewport	view;

	view = viewport(prog);
	prog->view = &view;
	if (init_img(prog))
		return ;
	multi_threading(prog);
	mlx_put_image_to_window(prog->mlx, prog->win, prog->img->img_ptr, 0, 0);
	printf("IMAGE HAS BEEN GENERATED\n");
}
