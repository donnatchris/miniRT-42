#include "../includes/miniRT_bonus.h"

static void	print_vector(t_vector v, const char *label)
{
	printf("%s: (%.6f, %.6f, %.6f)\n", label, v.x, v.y, v.z);
}

static void	print_camera(t_file *file)
{
	if (!file)
	{
		printf("Camera: NULL file pointer\n");
		return;
	}
	printf("=== Camera ===\n");
	print_vector(file->camera.origin, "Origin");
	print_vector(file->camera.direction, "Direction");
	printf("FOV: %d\n", file->camera.fov);
}


// Pour afficher une couleur stockée sous forme d'entier RGB
static void	print_color(int color, const char *label)
{
	int	r = (color >> 16) & 0xFF;
	int	g = (color >> 8) & 0xFF;
	int	b = color & 0xFF;

	printf("%s: R=%d, G=%d, B=%d\n", label, r, g, b);
}

static void	print_light(t_list **list)
{
	t_list	*node;
	t_light	*light;

	if (!list)
	{
		printf("Light: NULL file pointer\n");
		return;
	}
	printf("=== Lights ===\n");
	node = *list;
	while (node)
	{
		light = (t_light *) node->content;
		print_vector(light->position, "Position");
		printf("Intensity Ratio: %.6f\n", light->ratio);
		print_color(light->color, "Color");
		node = node->next;
	}
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

static void	print_sphere(t_sphere *sp)
{
	if (!sp)
	{
		printf("Sphere: NULL pointer\n");
		return;
	}
	printf("=== Sphere ===\n");
	print_vector(sp->position, "Center");
	printf("Diameter: %.6f\n", sp->diameter);
	print_color(sp->color, "Color");
}

static void	print_cone(t_cone *co)
{
	if (!co)
	{
		printf("cone: NULL pointer\n");
		return;
	}
	printf("=== cone ===\n");
	print_vector(co->apex, "Sommet");
	print_vector(co->axis, "Axe");
	printf("Angle : %d\n", co->angle);
	printf("Radian: %.6f\n", co->angle_rad);
	printf("Height: %.6f\n", co->height);
	print_color(co->color, "Color");
}

static void	print_plane(t_plane *pl)
{
	if (!pl)
	{
		printf("Plane: NULL pointer\n");
		return;
	}
	printf("=== Plane ===\n");
	print_vector(pl->position, "Position");
	print_vector(pl->normal, "Normal");
	print_color(pl->color, "Color");
	print_color(pl->color2, "Color2");
}

static void	print_cylinder(t_cylinder *cy)
{
	if (!cy)
	{
		printf("Cylinder: NULL pointer\n");
		return;
	}
	printf("=== Cylinder ===\n");
	print_vector(cy->position, "Position");
	print_vector(cy->orientation, "Orientation (Normal)");
	printf("Diameter: %.6f\n", cy->diameter);
	printf("Height: %.6f\n", cy->height);
	print_color(cy->color, "Color");
}

static void	print_triangle(t_triangle *tr)
{
	if (!tr)
	{
		printf("Triangle: NULL pointer\n");
		return;
	}
	printf("=== Triangle ===\n");
	print_vector(tr->vertex[0], "Position");
	print_vector(tr->vertex[1], "Position");
	print_vector(tr->vertex[2], "Position");
	print_color(tr->color, "Color");
}

static void	print_object_list(t_dclst **head)
{
	t_dclst	*current;

	printf("=== Objects ===\n");
	if (!head || !*head)
	{
		printf("No object to print\n");
		return ;
	}
	current = *head;
	while (1)
	{
		if (current->type == SP)
			print_sphere((t_sphere *) current->data);
		else if (current->type == PL)
			print_plane((t_plane *) current->data);
		else if (current->type == CY)
			print_cylinder((t_cylinder *) current->data);
		else if (current->type == TR)
			print_triangle((t_triangle *) current->data);
		else if (current->type == CO)
			print_cone((t_cone *) current->data);
		else
			printf("ERROR: unknown object in list\n");
		current = current -> next;
		if (current == *head)
			break ;
	}
}

void	print_file(t_file *file)
{
	print_camera(file);
	print_light(file->light_list);
	print_ambient_light(file);
	print_object_list(file->obj_list);
}
