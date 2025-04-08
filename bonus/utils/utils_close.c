/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_close.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 16:50:20 by olthorel          #+#    #+#             */
/*   Updated: 2025/04/08 10:47:42 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

int	ft_close_windows(t_program *program)
{
	if (program)
		delete_program(program);
	exit(0);
	return (0);
}

int	ft_key_hook(int keycode, t_program *program)
{
	if (keycode == 65307)
		ft_close_windows(program);
	return (0);
}

void	delete_xpm(t_xpm *xpm)
{
	if (!xpm)
		return ;
	if (xpm->img_ptr)
		mlx_destroy_image(xpm->mlx_ptr, xpm->img_ptr);
	free(xpm);
}
