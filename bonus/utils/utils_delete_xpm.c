/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_delete_xpm.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:11:22 by chdonnat          #+#    #+#             */
/*   Updated: 2025/04/09 09:34:06 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

static void	delete_pl_xpm(t_plane *plane)
{
	if (plane->xpm)
		delete_xpm(plane->xpm);
}

static void	delete_sp_xpm(t_sphere *sphere)
{
	if (sphere->xpm)
		delete_xpm(sphere->xpm);
}

static void	delete_cy_xpm(t_cylinder *cyl)
{
	if (cyl->xpm)
		delete_xpm(cyl->xpm);
}

static void	delete_co_xpm(t_cone *cone)
{
	if (cone->xpm)
		delete_xpm(cone->xpm);
}

void	delete_all_xpm(t_dclst **head)
{
	t_dclst	*current;

	current = *head;
	while (1)
	{
		if (current->type == PL)
			delete_pl_xpm((t_plane *) current->data);
		else if (current->type == SP)
			delete_sp_xpm((t_sphere *) current->data);
		else if (current->type == CY)
			delete_cy_xpm((t_cylinder *) current->data);
		else if (current->type == CO)
			delete_co_xpm((t_cone *) current->data);
		current = current->next;
		if (current == *head)
			break ;
	}
}
