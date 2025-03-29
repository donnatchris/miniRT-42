#include "../includes/miniRT.h"

int	ft_isint(char *str)
{
	int		i;
	int		sign;
	long	nb;

	i = 0;
	sign = 1;
	nb = 0;
	if (!str || *str == '\0' || *str == '\n')
		return (0);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		nb = (nb * 10) + (str[i] - 48);
		if ((sign == 1 && nb > INT_MAX) || (sign == -1 && - nb < INT_MIN))
			return (0);
		i++;
	}
	return (1);
}
