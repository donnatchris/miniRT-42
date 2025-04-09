/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_threading.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 22:32:59 by christophed       #+#    #+#             */
/*   Updated: 2025/04/09 15:26:46 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

static void	*render_thread0(void *prog)
{
	int	x;
	int	y;
	int	color;

	y = -1;
	while (++y < HEIGHT / 2)
	{
		x = -1;
		while (++x < WIDTH / 2)
		{
			color = choose_color(prog, x, y);
			*(int *)(((t_program *) prog)->img->addr
					+ ((WIDTH - x + (y * WIDTH))
						* (((t_program *) prog)->img->bpp / 8))) = color;
		}
	}
	return (NULL);
}

static void	*render_thread1(void *prog)
{
	int	x;
	int	y;
	int	color;

	y = HEIGHT / 2 - 1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH / 2)
		{
			color = choose_color(prog, x, y);
			*(int *)(((t_program *) prog)->img->addr
					+ ((WIDTH - x + (y * WIDTH))
						* (((t_program *) prog)->img->bpp / 8))) = color;
		}
	}
	return (NULL);
}

static void	*render_thread2(void *prog)
{
	int	x;
	int	y;
	int	color;

	y = -1;
	while (++y < HEIGHT / 2)
	{
		x = WIDTH / 2 - 1;
		while (++x < WIDTH)
		{
			color = choose_color(prog, x, y);
			*(int *)(((t_program *) prog)->img->addr
					+ ((WIDTH - x + (y * WIDTH))
						* (((t_program *) prog)->img->bpp / 8))) = color;
		}
	}
	return (NULL);
}

static void	*render_thread3(void *prog)
{
	int	x;
	int	y;
	int	color;

	y = HEIGHT / 2 - 1;
	while (++y < HEIGHT)
	{
		x = WIDTH / 2 - 1;
		while (++x < WIDTH)
		{
			color = choose_color(prog, x, y);
			*(int *)(((t_program *) prog)->img->addr
					+ ((WIDTH - x + (y * WIDTH))
						* (((t_program *) prog)->img->bpp / 8))) = color;
		}
	}
	return (NULL);
}

int	multi_threading(t_program *prog)
{
	pthread_t	thread[4];
	int			i;

	if (pthread_create(&thread[0], NULL, render_thread0, prog))
		return (1);
	if (pthread_create(&thread[1], NULL, render_thread1, prog))
		return (1);
	if (pthread_create(&thread[2], NULL, render_thread2, prog))
		return (1);
	if (pthread_create(&thread[3], NULL, render_thread3, prog))
		return (1);
	i = -1;
	while (++i < 4)
	{
		if (pthread_join(thread[i], NULL))
			return (1);
	}
	return (0);
}
