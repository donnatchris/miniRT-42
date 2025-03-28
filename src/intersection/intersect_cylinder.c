#include "../includes/miniRT.h"

// static int	hit_distance()
// {
	
// }

t_hit inter_cylinder(t_ray *ray, t_dclst *node)
{//test
    t_hit      hit;
    t_cylinder *cyl;
    t_vector   OC, CP;
	double		rayon2;
    double     a, b, c, delta, m;
    double     t1, t2, t;

    init_hit(&hit, node);
    cyl = (t_cylinder *)node->data;
	rayon2 = (cyl->diameter / 2) * (cyl->diameter / 2);
    
    // Vecteur origine-rayon → centre-cylindre
    OC = sub_vector(ray->origin, cyl->position);
    
    // Coefficients de l'équation quadratique
    a = dot_vector(ray->direction, ray->direction) - 
        pow(dot_vector(ray->direction, cyl->orientation), 2);
    
    b = 2 * (dot_vector(OC, ray->direction) - 
             dot_vector(OC, cyl->orientation) * dot_vector(ray->direction, cyl->orientation));
    
    c = dot_vector(OC, OC) - 
        pow(dot_vector(OC, cyl->orientation), 2) - 
        rayon2;
    
    delta = b*b - 4*a*c;
    if (delta < 0)
        return (hit);  // Pas d'intersection
    
    t1 = (-b - sqrt(delta)) / (2*a);
    t2 = (-b + sqrt(delta)) / (2*a);
    
    // Sélection de la solution valide la plus proche
    t = (t1 > EPS) ? fmin(t1, t2) : t2;
    if (t < EPS)
        return (hit);  // Intersection derrière ou trop proche
    
    // Calcul du point et de la normale
    hit.point = add_vector(ray->origin, mul_vector(ray->direction, t));
    CP = sub_vector(hit.point, cyl->position);
    m = dot_vector(CP, cyl->orientation);
    hit.normal = sub_vector(CP, mul_vector(cyl->orientation, m));
	normalize_vector(&hit.normal);
    hit.hit = 1;
    hit.distance = t;
    hit.color = cyl->color;
    hit.hit = 1;
    return (hit);
}

