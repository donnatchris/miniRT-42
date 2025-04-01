#include "../../includes/miniRT_bonus.h"

typedef struct s_cone
{
	t_vector    apex;    // Sommet du cône
	t_vector    axis;    // Axe du cône (normalisé)
	int         color;    // Couleur du cône
}   t_cone;

t_hit   inter_cone(t_ray *ray, t_dclst *node)
{
	t_hit  		 hit;
	t_cone		*cone;
	t_vector	oc;
	t_vector	v;
	t_vector	temp;
	double		m;
	double		a;
	double		b;
	double		c;
	double		discriminant;
	double		t1;
	double		t2;
	double		cos2;
	double		sin2;

	init_hit(&hit, node);
	cone = (t_cone *)node->data;
	oc = sub_vector(ray->origin, cone->apex);
	cos2 = 0.5; //approximation angle fixe;
	sin2 = 1 - cos2;
	a = dot_vector(ray->direction, ray->direction) - cos2 * dot_vector(ray->direction, cone->axis) * dot_vector(ray->direction, cone->axis);
    b = 2 * (dot_vector(ray->direction, oc) - cos2 * dot_vector(ray->direction, cone->axis) * dot_vector(oc, cone->axis));
    c = dot_vector(oc, oc) - cos2 * dot_vector(oc, cone->axis) * dot_vector(oc, cone->axis);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (hit);
	t1 = (-b - sqrt(discriminant)) / (2 * a);
	t2 = (-b + sqrt(discriminant)) / (2 * a);
	if (t1 >= EPS)
		hit.distance = t1;
	else if (t2 >= EPS)
		hit.distance = t2;
	else
		return (hit);
	hit.point = add_vector(ray->origin, mul_vector(ray->direction, hit.distance));

	// Correction ici
	v = sub_vector(hit.point, cone->apex); // Initialisation correcte de v
	m = dot_vector(v, cone->axis); // Calcul de m

	temp = sub_vector(v, mul_vector(cone->axis, m * (1 + sin2 / cos2)));
	normalize_vector(&temp);
	hit.normal = temp; // Stockage correct de la normale

	hit.color = cone->color;
	hit.hit = 1;
	return (hit);
}

// int main()
// {
//     t_cone cone = {
//         .apex = {0, 0, 0},
//         .axis = {0, 1, 0},
//         .color = 0xFFFFFF
//     };
    
//     t_ray ray = {
//         .origin = {1, 2, -5},
//         .direction = {0, -0.5, 1}
//     };
    
//     t_dclst node = {
//         .data = &cone
//     };
    
//     t_hit hit = inter_cone(&ray, &node);
    
//     if (hit.hit)
//     {
//         printf("Intersection at: (%f, %f, %f)\n", hit.point.x, hit.point.y, hit.point.z);
//         printf("Normal: (%f, %f, %f)\n", hit.normal.x, hit.normal.y, hit.normal.z);
//         printf("Distance: %f\n", hit.distance);
//     }
//     else
//     {
//         printf("No intersection.\n");
//     }
    
//     return 0;
// }