#include "../includes/miniRT.h"

int	is_inter_scene(t_ray *ray, t_file *file, t_hit *hit)
{
	t_hit	temp_hit;
	t_dclst	*current;
	int		inter;
	double	distance;

	inter = 0;
	hit->distance = DBL_MAX;
	current = file->obj_list; // a corriger
	while (current)
	{
		if (current->type == PL)
		{
			if (is_inter_plane(ray, (t_plane *)current->type, &temp_hit)) //plane a la place de type ?
			{
				if (temp_hit.distance < distance)
				{
					*hit = temp_hit;
					distance = temp_hit.distance;
					inter = 1;
				}
			}
		}
		else if (current->type == SP)
		{
			if (is_inter_sphere(ray, (t_sphere *)current->type, &temp_hit)) //sphere a la place de type ?
			{
				if (temp_hit.distance < distance)
				{
					*hit = temp_hit;
					distance = temp_hit.distance;
					inter = 1;
				}
			}
		}
		else if (current->type == CY)
		{
			if (is_inter_cylinder(ray, (t_cylinder *)current->type, &temp_hit)) //cylindre a la place de type ?
			{
				if (temp_hit.distance < distance)
				{
					*hit = temp_hit;
					distance = temp_hit.distance;
					inter = 1;
				}
			}
		}
		current = current->next;
	}
	return (inter);
}
