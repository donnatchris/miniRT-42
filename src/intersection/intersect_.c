#include "../includes/miniRT.h"

t_hit	inter_scene(t_ray *ray, t_file *file)
{
	t_hit	hit;
    t_hit   temp;
	t_dclst	*current;

    hit.hit = 0;
	hit.distance = DBL_MAX;
	current = *file->obj_list;
	while (current)
	{
		if (current->type == PL)
		{
			temp = inter_plane(ray, current);
			{
				if (temp.hit && temp.distance < hit.distance)
                    hit = temp;
			}
		}
        if (current->type == SP)
		{
			temp = inter_sphere(ray, current);
			{
				if (temp.hit && temp.distance < hit.distance)
                    hit = temp;
			}
		}
        if (current->type == CY)
		{
			temp = inter_cylinder(ray, current);
			{
				if (temp.hit && temp.distance < hit.distance)
                    hit = temp;
			}
		}
		current = current->next;
        if (current == *file->obj_list)
            break ;
	}
	return (hit);
}