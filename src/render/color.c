#include "../includes/miniRT.h"

int	scale_color(int color, double factor)
{
	int	r;
	int	g;
	int	b;

	r = ((color >> 16) & 0xFF) * factor;
	g = ((color >> 8) & 0xFF) * factor;
	b = (color & 0xFF) * factor;

	if (r > 255) r = 255;
	if (g > 255) g = 255;
	if (b > 255) b = 255;
	if (r < 0) r = 0;
	if (g < 0) g = 0;
	if (b < 0) b = 0;

	return ((r << 16) | (g << 8) | b);
}

// int	mix_colors(int color1, int color2, double factor)
// {
// 	int	r, g, b;

// 	// Clamp le facteur entre 0 et 1
// 	if (factor < 0) factor = 0;
// 	if (factor > 1) factor = 1;

// 	// Extraction des composants RGB
// 	int r1 = (color1 >> 16) & 0xFF;
// 	int g1 = (color1 >> 8) & 0xFF;
// 	int b1 = color1 & 0xFF;

// 	int r2 = (color2 >> 16) & 0xFF;
// 	int g2 = (color2 >> 8) & 0xFF;
// 	int b2 = color2 & 0xFF;

// 	// Mélange des couleurs selon le facteur
// 	r = (int)(r1 * (1 - factor) + r2 * factor);
// 	g = (int)(g1 * (1 - factor) + g2 * factor);
// 	b = (int)(b1 * (1 - factor) + b2 * factor);

// 	// Reconstruction de la couleur
// 	return ((r << 16) | (g << 8) | b);
// }


int mix_colors(int color1, int color2)
{
    // Extraction des composantes RGB de la première couleur
    int r1 = (color1 >> 16) & 0xFF;
    int g1 = (color1 >> 8) & 0xFF;
    int b1 = color1 & 0xFF;
    
    // Extraction des composantes RGB de la deuxième couleur
    int r2 = (color2 >> 16) & 0xFF;
    int g2 = (color2 >> 8) & 0xFF;
    int b2 = color2 & 0xFF;
    
    // Calcul de la moyenne pour chaque composante
    int mixed_r = (r1 + r2) / 2;
    int mixed_g = (g1 + g2) / 2;
    int mixed_b = (b1 + b2) / 2;
    
    // Reconstruction de la couleur mélangée
    return (mixed_r << 16) | (mixed_g << 8) | mixed_b;
}