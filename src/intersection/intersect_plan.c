#include "../includes/miniRT.h"

t_hit inter_plane(t_ray *ray, t_dclst *node) {
    t_hit      hit;
    t_plane    *plane = (t_plane *)node->data;
    t_vector   unit_normal = plane->normal;
	normalize_vector(&unit_normal);
    double     denom = dot_vector(unit_normal, ray->direction);
    double     tolerance = 1e-3; // Ajustable

    init_hit(&hit, node);
    
    if (fabs(denom) > tolerance) {
        t_vector vec_to_plane = sub_vector(plane->position, ray->origin);
        hit.distance = dot_vector(vec_to_plane, unit_normal) / denom;
        
        if (hit.distance >= tolerance) {
            hit.point = add_vector(ray->origin, mul_vector(ray->direction, hit.distance));
            hit.normal = (denom < 0) ? unit_normal : mul_vector(unit_normal, -1);
            hit.color = plane->color;
            hit.hit = 1;
        }
    }
    return hit;
}
