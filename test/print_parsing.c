#include "../includes/miniRT.h"

static void	print_vector(t_vector v, const char *label)
{
	printf("%s: (%.6f, %.6f, %.6f)\n", label, v.x, v.y, v.z);
}

void	print_camera(t_file *file)
{
	if (!file)
	{
		printf("Camera: NULL file pointer\n");
		return;
	}
	printf("=== Camera ===\n");
	print_vector(file->camera.origin, "Origin");
	print_vector(file->camera.direction, "Direction");
	printf("FOV: %.6f°\n", file->camera.fov);
}


// Pour afficher une couleur stockée sous forme d'entier RGB
static void	print_color(int color, const char *label)
{
	int	r = (color >> 16) & 0xFF;
	int	g = (color >> 8) & 0xFF;
	int	b = color & 0xFF;

	printf("%s: R=%d, G=%d, B=%d\n", label, r, g, b);
}

void	print_light(t_file *file)
{
	if (!file)
	{
		printf("Light: NULL file pointer\n");
		return;
	}
	printf("=== Light ===\n");
	print_vector(file->light.position, "Position");
	printf("Intensity Ratio: %.6f\n", file->light.ratio);
	print_color(file->light.color, "Color");
}

void	print_ambient_light(t_file *file)
{
	if (!file)
	{
		printf("Ambient light: NULL file pointer\n");
		return;
	}
	printf("=== Ambient Light ===\n");
	printf("Intensity Ratio: %.6f\n", file->ambient_light.ratio);
	print_color(file->ambient_light.color, "Color");
}
