#include "../includes/miniRT.h"

// t_hit inter_cylinder(t_ray *ray, t_dclst *node)
// {
//     t_cylinder  *cy;
//     t_hit       hit;
//     t_quadratic q;
//     t_vector    u;
//     t_vector    v;

//     cy = (t_cylinder *)node->data;
//     init_hit(&hit, node);
// 	normalize_vector(&cy->orientation);
//     u = cross_vector(ray->direction, cy->orientation);
//     v = sub_vector(cy->position, ray->origin);
//     v = cross_vector(v, cy->orientation);
//     q.a = dot_vector(u, u);
//     q.b = 2 * dot_vector(u, v);
//     q.c = dot_vector(v, v) - ((cy->diameter / 2.0) * (cy->diameter / 2.0));
//     if (!solve_quadratic(&q) || (q.t2 <= EPS && q.t1 <= EPS))
//         return (hit);
//     if (q.t1 <= EPS || (q.t2 > EPS && (q.t2 < q.t1)))
//         q.t1 = q.t2;
//     hit.distance = q.t1;
//     ray_mul(&hit.point, ray, q.t1);
//     v = sub_vector(cy->position, hit.point);
//     hit.normal = cross_vector(v, cy->orientation);
//     hit.normal = cross_vector(hit.normal, cy->orientation);
//     normalize_vector(&hit.normal);
//     if (dot_vector(hit.normal, ray->direction))
//         hit.normal = inv_vector(hit.normal);
//     return (hit);
// }

