/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 16:42:44 by olthorel          #+#    #+#             */
/*   Updated: 2025/03/31 11:33:42 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

void	ft_print_error(int exit_code)
{
	if (exit_code == 0)
		ft_putstr_fd("Error\nminiRT closed\n", 2);
	else if (exit_code == 1)
		ft_putstr_fd("Error\nWrong usage -> ./miniRT scenes/...rt\n", 2);
	else if (exit_code == 2)
		ft_putstr_fd("Error\nCannot read file.\n", 2);
	else if (exit_code == 3)
		ft_putstr_fd("Error\nCannot init miniRT.\n", 2);
	else if (exit_code == 4)
		ft_putstr_fd("Error\nCannot parse map.\n", 2);
	else if (exit_code == 5)
		ft_putstr_fd("Error\nCannot create image.\n", 2);
	else if (exit_code == 6)
		ft_putstr_fd("Error\nCannot init cam.\n", 2);
	else if (exit_code == 7)
		ft_putstr_fd("Error\nUnable to render.\n", 2);
	else if (exit_code == 8)
		ft_putstr_fd("Error\nCannot init color.\n", 2);
	return ;
}
