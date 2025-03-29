#include "../includes/miniRT.h"

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
		else if (str[i] == '.')
		{
			point_count++;
			if (point_count > 1)
				return (0);
			i++;
		}
		else if ((str[i] == 'e' || str[i] == 'E') && e_count == 0)
		{
			e_count++;
			i++;
			if (str[i] == '-' || str[i] == '+')
				i++;
		}
		else
			return (0);
	}
	if (e_count > 0 && !ft_isdigit(str[i - 1]))
		return (0);
	return (1);
}
