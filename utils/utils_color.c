#include "../includes/miniRT.h"

int	ft_iscolor(char *str)
{
	int	num;
	int	count;

	count = 0;
	num = 0;
	if (!str || !*str || *str == '\n')
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		num = atoi(str);
		if (num > 255)
			return (0);
		count++;
		while (ft_isdigit(*str))
			str++;
		if (*str == ',' && count < 3)
			str++;
		else if (*str)
			return (0);
	}
	return (count == 3);
}

static void	ft_atocolor(char *str, int *rgb)
{
	int	i;
	int	count;

	if (!ft_iscolor(str))
	{
		rgb[0] = -1;
		rgb[1] = -1;
		rgb[2] = -1;
		return ;
	}
	i = 0;
	count = 0;
	while (str[i] && count < 3)
	{
		rgb[count] = ft_atoi(&str[i]);
		while (ft_isdigit(str[i]))
			i++;
		if (str[i] == ',')
			i++;
		count++;
	}
}

int	ft_atoc(char *str)
{
	int	rgb[3];

	ft_atocolor(str, rgb);
	if (rgb[0] == -1)
		return (-1);
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}
