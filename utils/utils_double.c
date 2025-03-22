#include "../includes/miniRT.h"

double ft_atod(char *str)
{
	double	result;
	double	sign;
	double	div;
	int		exp;
	int		point;
	int		exp_sign;
	int		i;

	result = 0.0;
	sign = 1.0;
	div = 1.0;
	i = 0;
	point = 0;
	exp_sign = 1;
	exp = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1.0;
		i++;
	}
    while (str[i]) 
	{
        if (ft_isdigit(str[i])) 
		{
            if (point) 
			{
                div *= 10.0;
                result = result + (str[i] - '0') / div;
            } 
			else 
                result = result * 10.0 + (str[i] - '0');
        } 
		else if (str[i] == '.') 
		{
            if (point)
                return (1);
            point = 1;
        } 
		else if (str[i] == 'e' || str[i] == 'E')
            break;
		else 
            break;
        i++;
    }
    if (str[i] == 'e' || str[i] == 'E') 
	{
        i++;
        if (str[i] == '-' || str[i] == '+')
		{
            if (str[i] == '-')
                exp_sign = -1;
            i++;
        }
        while (ft_isdigit(str[i])) 
		{
            exp = (exp * 10) + (str[i] - '0');
            i++;
        }
		if (exp_sign == -1)
       		result = result / pow(10.0, exp);
		else
			result = result * pow(10.0, exp);
    }
    return (result * sign);
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


// int main()
// {
//     char *str1 = "123.456";
//     char *str2 = "-123.456e10";
//     char *str3 = "123e-2";
//     char *str4 = "123..456";  // invalide
//     char *str5 = "abc123";    // invalide
    
//     printf("ft_isdouble(\"%s\") = %d\n", str1, ft_isdouble(str1));  // 1
//     printf("ft_isdouble(\"%s\") = %d\n", str2, ft_isdouble(str2));  // 1
//     printf("ft_isdouble(\"%s\") = %d\n", str3, ft_isdouble(str3));  // 1
//     printf("ft_isdouble(\"%s\") = %d\n", str4, ft_isdouble(str4));  // 0
//     printf("ft_isdouble(\"%s\") = %d\n", str5, ft_isdouble(str5));  // 0
    
//     printf("ft_atod(\"%s\") = %f\n", str1, ft_atod(str1));  // 123.456000
//     printf("ft_atod(\"%s\") = %f\n", str2, ft_atod(str2));  // -1234560000000000.000000
//     printf("ft_atod(\"%s\") = %f\n", str3, ft_atod(str3));  // 0.000000123000

//     return 0;
// }