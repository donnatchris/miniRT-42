/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 16:50:31 by olthorel          #+#    #+#             */
/*   Updated: 2025/03/30 17:04:09 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	ft_isint(char *str)
{
	int		sign;
	long	nb;

	sign = 1;
	nb = 0;
	if (!str || *str == '\0' || *str == '\n')
		return (0);
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if (!*str)
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		nb = (nb * 10) + (*str - 48);
		if ((sign == 1 && nb > INT_MAX) || (sign == -1 && - nb < INT_MIN))
			return (0);
		str++;
	}
	return (1);
}
