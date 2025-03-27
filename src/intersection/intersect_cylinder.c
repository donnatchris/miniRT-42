#include "../includes/miniRT.h"

static double verif_inter_cylinder(t_cylinder *cy, t_ray *ray, t_quadratic *eq, t_hit *hit)
{
    t_vector inter1, inter2, hit_normal;
    double t1, t2;
    double proj1, proj2;

    t1 = eq->t1;
    t2 = eq->t2;

    // Ignorer les valeurs négatives de t
    if (t1 < 1e-6 && t2 < 1e-6)
        return -1;

    // Calcul des points d'intersection
    inter1 = add_vector(ray->origin, mul_vector(ray->direction, t1));
    inter2 = add_vector(ray->origin, mul_vector(ray->direction, t2));

    // Projection des points d'intersection sur l'axe du cylindre
    proj1 = dot_vector(sub_vector(inter1, cy->p1), cy->orientation);
    proj2 = dot_vector(sub_vector(inter2, cy->p1), cy->orientation);

    // Vérification des limites du cylindre et calcul de la normale
    if (proj1 >= 0 && proj1 <= cy->height && t1 > 1e-6)
    {
        hit->point = inter1;
        hit_normal = sub_vector(inter1, add_vector(cy->p1, mul_vector(cy->orientation, proj1)));
        normalize_vector(&hit_normal);
        return t1;
    }
    if (proj2 >= 0 && proj2 <= cy->height && t2 > 1e-6)
    {
        hit->point = inter2;
        hit_normal = sub_vector(inter2, add_vector(cy->p1, mul_vector(cy->orientation, proj2)));
        normalize_vector(&hit_normal);
        return t2;
    }

    return -1; // Aucune intersection valide
}

t_hit inter_cylinder(t_ray *ray, t_dclst *node)
{
    t_hit       hit;
    t_cylinder  *cylinder;
    t_vector    co;
    t_quadratic eq;
    double      t;

    cylinder = (t_cylinder *) node->data;
    init_hit(&hit, node);

    // Initialisation des solutions quadratiques
    eq.t1 = -1;
    eq.t2 = -1;

    // Calcul des coefficients de l'équation quadratique
    co = sub_vector(ray->origin, cylinder->p1);
    eq.a = dot_vector(ray->direction, ray->direction) - pow(dot_vector(ray->direction, cylinder->orientation), 2);
    eq.b = 2 * (dot_vector(ray->direction, co) - (dot_vector(ray->direction, cylinder->orientation) * dot_vector(co, cylinder->orientation)));
    eq.c = dot_vector(co, co) - pow(dot_vector(co, cylinder->orientation), 2) - cylinder->rayon2;
    
    // Résolution de l'équation quadratique
    if (!solve_quadratic(&eq))
        return hit;

    // Vérification des intersections avec le cylindre
    t = verif_inter_cylinder(cylinder, ray, &eq, &hit);
    if (t > 1e-6)
    {
        hit.distance = t;
        hit.color = cylinder->color;
        hit.hit = 1;
    }
    return hit;
}
