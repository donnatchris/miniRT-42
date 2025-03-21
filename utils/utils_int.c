#include "../includes/miniRT.h"

int	ft_isint(char *str)
{
	int		i;
	int		sign;
	long	nb;

	i = 0;
	sign = 1;
	nb = 0;
	if (!str || !str[i])
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
		if ((sign == 1 && nb > INT_MAX) || (sign == -1 && -nb < INT_MIN))
			return (0);
		i++;
	}
	return (1);
}

// int main()
// {
//     char *tests[] = {"42", "-2147483648", "2147483647", "2147483648", "-2147483649", "abc", "12a", "--42", "", NULL};
//     for (int i = 0; tests[i]; i++)
//         printf("\"%s\" -> %s\n", tests[i], ft_isint(tests[i]) ? "Valid INT" : "Invalid INT");

//     return 0;
// }
