#include "../../includes/miniRT_bonus.h"

static int choose_co_color(t_cone *cone, t_hit hit)
{
	t_vector	dir;
	t_vector	axis;
	t_vector	radial;
	t_vector	u_vec, v_vec, w_vec;
	double		u, v;
	int			x, y;

	if (!cone->chessboard)
		return (cone->color);
	axis = cone->axis;
	w_vec = axis;
	t_vector tmp = (fabs(w_vec.y) > 0.999) ? (t_vector){1, 0, 0} : (t_vector){0, 1, 0};
	u_vec = cross_vector(tmp, w_vec);
    normalize_vector(&u_vec);
	v_vec = cross_vector(w_vec, u_vec);
	dir = sub_vector(hit.point, cone->apex);
	radial = sub_vector(dir, mul_vector(w_vec, dot_vector(dir, w_vec)));
	u = 0.5 + atan2(dot_vector(radial, v_vec), dot_vector(radial, u_vec)) / (2 * M_PI);
	v = dot_vector(dir, w_vec) / cone->height;
	x = (int)(floor(u * cone->scale));
	y = (int)(floor(v * cone->scale));
	if ((x + y) % 2 == 0)
		return (cone->color);
	else
		return (cone->color2);
}


static double find_closest_intersection(double t1, double t2) {
    if (t1 > EPS && (t2 < EPS || t1 < t2))
        return t1;
    if (t2 > EPS)
        return t2;
    return -1;
}

// t_vector calculate_cone_normal(t_cone *cone, t_vector point) {
//     t_vector apex_to_point = sub_vector(point, cone->apex);
//     double m = dot_vector(apex_to_point, cone->axis);
//     t_vector proj = mul_vector(cone->axis, m);
//     t_vector normal = sub_vector(apex_to_point, proj);
//     double len = sqrt(dot_vector(normal, normal));
//     normal = mul_vector(normal, 1.0 / len);
//     return normal;
// }

t_hit inter_cone(t_ray *ray, t_dclst *node)
{
    t_hit hit;
    t_cone *cone = (t_cone *)node->data;
    init_hit(&hit, node);
    
    // Normalisation de l'axe du cône
	t_vector axis = cone->axis;
    double k = pow(tan(cone->angle_rad), 2);
    t_vector co = sub_vector(ray->origin, cone->apex);
    
    // Coefficients quadratiques
    double dv = dot_vector(ray->direction, cone->axis);
    double coa = dot_vector(co, cone->axis);
    
    t_quadratic q;
    q.a = dot_vector(ray->direction, ray->direction) - (1 + k) * dv * dv;
    q.b = 2 * (dot_vector(ray->direction, co) - (1 + k) * dv * coa);
    q.c = dot_vector(co, co) - (1 + k) * coa * coa;
    // printf("Coefficients quadratiques:\n");
    // printf("a: %f, b: %f, c: %f\n", q.a, q.b, q.c);
    if (!solve_quadratic(&q))
    {
        // printf("Pas de solution quadratique, aucun rayon n'intersecte le cône.\n");
        return hit;
    }
    // printf("Solutions quadratiques:\n");
    // printf("t1: %f, t2: %f\n", q.t1, q.t2);
    double t = find_closest_intersection(q.t1, q.t2);
    if (t < EPS)
    {
        // printf("Aucune intersection valide trouvée, t: %f\n", t);
        return hit;
    }
    hit.point = add_vector(ray->origin, mul_vector(ray->direction, t));
    // printf("Point d'impact : (%.2f, %.2f, %.2f)\n", hit.point.x, hit.point.y, hit.point.z);
    // Vérification de la hauteur
    double m = dot_vector(sub_vector(hit.point, cone->apex), cone->axis);
    // printf("Point d'impact : (%f, %f, %f)\n", hit.point.x, hit.point.y, hit.point.z);
    // printf("Apex du cône : (%f, %f, %f)\n", cone->apex.x, cone->apex.y, cone->apex.z);
    // printf("Direction de l'axe du cône : (%f, %f, %f)\n", cone->axis.x, cone->axis.y, cone->axis.z);
    // printf("Hauteur du point par rapport à l'apex : %f\n", m);
    if (m < 0 || m > cone->height)
    {
        // printf("Le point d'impact est hors de la portée du cône (hauteur).\n");
        return hit;
    }
    // printf("Hauteur du point par rapport à l'apex du cône : %f\n", m);

    if (cone->height > 0 && (m < -EPS || m > cone->height + EPS))
    {
        // printf("Le point d'impact est hors de la portée du cône.\n");
        return hit;
    }
    
    // Calcul de la normale
    t_vector apex_to_p = sub_vector(hit.point, cone->apex);
    double proj_len = dot_vector(apex_to_p, axis);
    t_vector proj = mul_vector(axis, proj_len);
    hit.normal = sub_vector(apex_to_p, mul_vector(proj, 1 + k));
    // printf("Normale avant normalisation : (%.2f, %.2f, %.2f)\n", hit.normal.x, hit.normal.y, hit.normal.z);
	normalize_vector(&hit.normal);
    //printf("Normale après normalisation : (%.2f, %.2f, %.2f)\n", hit.normal.x, hit.normal.y, hit.normal.z);
    
    // Inverser la normale si le rayon est à l'intérieur
    if (dot_vector(hit.normal, ray->direction) > 0)
        hit.normal = mul_vector(hit.normal, -1);
    
    hit.distance = t;
    hit.hit = 1;
    hit.color = choose_co_color(cone, hit);
    hit.shininess = cone->shininess;
    // if (hit.hit) 
    // {
    //     // printf("Intersection trouvée !\n");
    //     // printf("Point d'impact : (%.2f, %.2f, %.2f)\n", hit.point.x, hit.point.y, hit.point.z);
    //     // printf("Normale : (%.2f, %.2f, %.2f)\n", hit.normal.x, hit.normal.y, hit.normal.z);
    //     // printf("Distance : %.2f\n", hit.distance);
    //     // printf("Couleur : 0x%X\n", hit.color);
    // }
    // else
        // printf("Aucune intersection.\n");
    return hit;
}

// int main() {
//     // Définition du cône
//     t_cone cone;
//     cone.apex = (t_vector){0, 0, 0};  // Sommet du cône à l'origine
//     cone.axis = (t_vector){0, 1, 0};
// 	normalize_vector(&cone.axis);  // Axe orienté vers le haut
//     cone.angle = M_PI / 6;  // Angle d'ouverture (30 degrés)
//     cone.height = 5;  // Hauteur maximale du cône
//     cone.color = 0xFF0000;  // Rouge
//     cone.shininess = 50;
    
//     // Définition du rayon
//     t_ray ray;
//     ray.origin = (t_vector){2, 3, -5};  // Point de départ du rayon
//     ray.direction = (t_vector){-0.4, -0.6, 1};
// 	normalize_vector(&ray.direction);  // Direction normalisée
    
//     // Création du nœud de la liste pour l'objet
//     t_dclst node;
//     node.data = &cone;
    
//     // Calcul de l'intersection
//     t_hit hit = inter_cone(&ray, &node);
    
//     // Affichage du résultat
//     if (hit.hit) {
//         printf("Intersection trouvée !\n");
//         printf("Point d'impact : (%.2f, %.2f, %.2f)\n", hit.point.x, hit.point.y, hit.point.z);
//         printf("Normale : (%.2f, %.2f, %.2f)\n", hit.normal.x, hit.normal.y, hit.normal.z);
//         printf("Distance : %.2f\n", hit.distance);
//         printf("Couleur : 0x%X\n", hit.color);
//     } else {
//         printf("Aucune intersection.\n");
//     }
    
//     return 0;
// }
