/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 16:50:26 by olthorel          #+#    #+#             */
/*   Updated: 2025/03/30 17:43:50 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static int	ft_handle_point(char *str, int *i, int *point_count)
{
	if (str[*i] == '.')
	{
		(*point_count)++;
		if (*point_count > 1)
			return (0);
		(*i)++;
		return (1);
	}
	return (0);
}

static int	ft_handle_exponent(char *str, int *i, int *e_count)
{
	if ((str[*i] == 'e' || str[*i] == 'E') && *e_count == 0)
	{
		(*e_count)++;
		(*i)++;
		if (str[*i] == '-' || str[*i] == '+')
			(*i)++;
		return (1);
	}
	return (0);
}

int	ft_isdouble(char *str)
{
	int		i;
	int		point_count;
	int		e_count;

	if (!str || *str == '\0' || *str == '\n')
		return (0);
	i = 0;
	point_count = 0;
	e_count = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			i++;
		else if (ft_handle_point(str, &i, &point_count))
			continue ;
		else if (ft_handle_exponent(str, &i, &e_count))
			continue ;
		else
			return (0);
	}
	if (e_count > 0 && !ft_isdigit(str[i - 1]))
		return (0);
	return (1);
}
