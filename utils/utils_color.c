#include "../includes/miniRT.h"

int	ft_iscolor(char *str)
{
	int	i;
	int	num;
	int	count;

	if (!str || *str == '\0' || *str == '\n')
		return (0);
	i = 0;
	count = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		num = ft_atoi(&str[i]);
		if (num < 0 || num > 255)
			return (0);
		count++;
		while (ft_isdigit(str[i]))
			i++;
		if (count == 3 && str[i])
			return (0);
		if (str[i] == ',')
		{
			if (!ft_isdigit(str[i + 1]))
				return (0);
			i++;
		}
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

// int	main()
// {
// 	printf("%d\n", ft_iscolor("255,128,64"));   // ✅ 1
// 	printf("%d\n", ft_iscolor("0,0,0"));        // ✅ 1
// 	printf("%d\n", ft_iscolor("300,200,100"));  // ❌ 0 (300 est invalide)
// 	printf("%d\n", ft_iscolor("50,25"));        // ❌ 0 (pas 3 valeurs)
// 	printf("%d\n", ft_iscolor("100,100,-1"));   // ❌ 0 (nombre négatif)
// 	printf("%d\n", ft_iscolor("abc,100,100"));  // ❌ 0 (lettres invalides)
// 	printf("%d\n", ft_iscolor("100,100,100,")); // ❌ 0 (virgule en trop)
// }

// int main()
// {
//     char *color_str = "255,255,255";
//     int color = ft_atoc(color_str);

//     if (color != -1)
//         printf("Couleur en format hexadécimal: 0x%06X\n", color);  // 0xFF8040
//     else
//         printf("Couleur invalide !\n");

//     return 0;
// }
