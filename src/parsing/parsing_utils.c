#include "../../includes/miniRT.h"

char	*next_arg(char *line, size_t start)
{
	char	*arg;
	int		end;

	arg = NULL;
	while (ft_strchr(WHITESPACE, line[start]))
		start++;
	if (line[start] == '\0' || line[start] == '\n')
		return (NULL);
	end = start + 1;
	while (!ft_strchr(WHITESPACE, line[end]) && line[end] != '\0' && line[end] != '\n')
		end++;
	arg = ft_substr(line, start, end - start);
	return (arg);
}

int	ft_isorientation(char *str)
{
	char 	**tab;
	double	n[3];
	int		i;

	if (!ft_isvector(str))
		return (0);
	tab = ft_split(str, ',');
	if (!tab)
		return (0);
	i = -1;
	while (++i < 3)
		n[i] = ft_atod(tab[i]);
	i = -1;
	while (++i < 3)
	{
		if (n[i] < -1 || n[i] > 1)
			return (delete_str_array(tab), 0);
	}
	if (n[0] == 0 && n[1] == 0 && n[2] == 0)
		return (delete_str_array(tab), 0);
	delete_str_array(tab);
	return (1);
}

int	ft_isratio(char *str)
{
	double	n;

	if (!ft_isdouble(str))
		return (0);
	n = ft_atod(str);
	if (n < 0 || n > 1)
		return (0);
	return (1);
}

int	ft_isangle(char *str)
{
	int	n;

	if (!ft_isint(str))
		return (0);
	n = ft_atoi(str);
	if (n <= 0 || n >= 180)
		return (0);
	return (1);
}
