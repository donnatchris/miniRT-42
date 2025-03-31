/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 21:49:01 by christophed       #+#    #+#             */
/*   Updated: 2025/03/31 11:33:08 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

static void	viewport_len(t_viewport *view, t_program *prog)
{
	view->asp_ratio = (double) WIDTH / HEIGHT;
	view->fov = prog->file->camera.fov * PI / 180;
	view->width = 2.0 * tan(view->fov / 2.0);
	view->height = view->width / view->asp_ratio;
}

static void	viewport_vectors(t_viewport *view, t_program *prog)
{
	view->world_up = vector(0, 1, 0);
	view->forward = prog->file->camera.direction;
	normalize_vector(&view->forward);
	view->right = cross_vector(view->forward, view->world_up);
	if (len_vector(view->right) < EPS)
	{
		view->world_up = vector(1, 0, 0);
		view->right = cross_vector(view->forward, view->world_up);
	}
	normalize_vector(&view->right);
	view->up = cross_vector(view->right, view->forward);
}

static void	viewport_position(t_viewport *view, t_program *prog)
{
	t_vector	viewport_center;
	double		focal_dist;

	focal_dist = 1.0;
	viewport_center = add_vector(prog->file->camera.origin,
			mul_vector(view->forward, focal_dist));
	view->horizontal = mul_vector(view->right, view->width);
	view->vertical = mul_vector(view->up, view->height);
	view->origin = sub_vector(viewport_center,
			add_vector(mul_vector(view->horizontal, 0.5),
				mul_vector(view->vertical, 0.5)));
}

t_viewport	viewport(t_program *prog)
{
	t_viewport	view;

	viewport_len(&view, prog);
	viewport_vectors(&view, prog);
	viewport_position(&view, prog);
	return (view);
}
