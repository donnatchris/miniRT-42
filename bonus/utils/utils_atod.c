/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_atod.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 17:25:14 by olthorel          #+#    #+#             */
/*   Updated: 2025/03/30 17:25:14 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

static void	ft_handle_sign(char **str, double *sign)
{
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			*sign = -1.0;
		(*str)++;
	}
}

static void	ft_handle_digit(char **str, double *result, double *div, int point)
{
	if (point)
	{
		*div *= 10.0;
		*result = *result + (**str - '0') / *div;
	}
	else
		*result = *result * 10.0 + (**str - '0');
}

static void	ft_parse_decimal(char **str, double *result, double *div)
{
	int		point;

	point = 0;
	while (**str)
	{
		if (ft_isdigit(**str))
			ft_handle_digit(str, result, div, point);
		else if (**str == '.')
		{
			if (point)
				return ;
			point = 1;
		}
		else if (**str == 'e' || **str == 'E')
			break ;
		else
			break ;
		(*str)++;
	}
}

static void	ft_parse_exponent(char **str, double *result)
{
	int	exp;
	int	exp_sign;

	exp_sign = 1;
	exp = 0;
	if (**str == 'e' || **str == 'E')
	{
		(*str)++;
		if (**str == '-' || **str == '+')
		{
			if (**str == '-')
				exp_sign = -1;
			(*str)++;
		}
		while (ft_isdigit(**str))
		{
			exp = (exp * 10) + (**str - '0');
			(*str)++;
		}
		if (exp_sign == -1)
			*result = *result / pow(10.0, exp);
		else
			*result = *result * pow(10.0, exp);
	}
}

double	ft_atod(char *str)
{
	double	result;
	double	sign;
	double	div;

	result = 0.0;
	sign = 1.0;
	div = 1.0;
	ft_handle_sign(&str, &sign);
	ft_parse_decimal(&str, &result, &div);
	ft_parse_exponent(&str, &result);
	return (result * sign);
}
