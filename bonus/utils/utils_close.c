/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_close.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 16:50:20 by olthorel          #+#    #+#             */
/*   Updated: 2025/03/31 10:12:19 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT_bonus.h"

int	ft_close_windows(t_program *program)
{
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
