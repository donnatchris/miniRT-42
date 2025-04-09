/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 22:32:59 by christophed       #+#    #+#             */
/*   Updated: 2025/04/09 11:04:18 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
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



void	*render_thread0(void *prog)
{
	int	x;
	int	y;
	int	color;

	y = -1;
	while (y++ < HEIGHT / 2)
	{
		x = -1;
		while (x++ < WIDTH / 2)
		{
			color = choose_color(prog, x, y);
			*(int *)(((t_program *) prog)->img->addr + ((WIDTH - x + (y * WIDTH))
						* (((t_program *) prog)->img->bpp / 8))) = color;
		}
	}
	return (NULL);
}

void	*render_thread1(void *prog)
{
	int	x;
	int	y;
	int	color;

	y = HEIGHT / 2 - 1;
	while (y++ < HEIGHT)
	{
		x = -1;
		while (x++ < WIDTH / 2)
		{
			color = choose_color(prog, x, y);
			*(int *)(((t_program *) prog)->img->addr + ((WIDTH - x + (y * WIDTH))
						* (((t_program *) prog)->img->bpp / 8))) = color;
		}
	}
	return (NULL);
}

void	*render_thread2(void *prog)
{
	int	x;
	int	y;
	int	color;

	y = -1;
	while (y++ < HEIGHT / 2)
	{
		x = WIDTH / 2 - 1;
		while (x++ < WIDTH)
		{
			color = choose_color(prog, x, y);
			*(int *)(((t_program *) prog)->img->addr + ((WIDTH - x + (y * WIDTH))
						* (((t_program *) prog)->img->bpp / 8))) = color;
		}
	}
	return (NULL);
}
void	*render_thread3(void *prog)
{
	int	x;
	int	y;
	int	color;

	y = HEIGHT / 2 - 1;
	while (y++ < HEIGHT)
	{
		x = WIDTH / 2 - 1;
		while (x++ < WIDTH)
		{
			color = choose_color(prog, x, y);
			*(int *)(((t_program *) prog)->img->addr + ((WIDTH - x + (y * WIDTH))
				* (((t_program *) prog)->img->bpp / 8))) = color;
		}
	}
	return (NULL);
}

void	render(t_program *prog)
{
	t_viewport	view;
	int			i;
	pthread_t	thread[4];

	view = viewport(prog);
	prog->view = &view;
	if (init_img(prog))
		return ;
	pthread_create(&thread[0], NULL, render_thread0, prog);
	pthread_create(&thread[1], NULL, render_thread1, prog);
	pthread_create(&thread[2], NULL, render_thread2, prog);
	pthread_create(&thread[3], NULL, render_thread3, prog);
	i = -1;
	while (i++ < 4)
		pthread_join(thread[i], NULL);
	mlx_put_image_to_window(prog->mlx, prog->win, prog->img->img_ptr, 0, 0);
	printf("IMAGE HAS BEEN GENERATED\n");
}
