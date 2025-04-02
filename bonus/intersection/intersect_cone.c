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
    if (!solve_quadratic(&q))
        return hit;
    double t = find_closest_intersection(q.t1, q.t2);
    if (t < EPS)
        return hit;
    hit.point = add_vector(ray->origin, mul_vector(ray->direction, t));
    // Vérification de la hauteur
    double m = dot_vector(sub_vector(hit.point, cone->apex), cone->axis);
    if (m < 0 || m > cone->height)
        return hit;
    if (cone->height > 0 && (m < -EPS || m > cone->height + EPS))
        return hit; 
    // Calcul de la normale
    t_vector apex_to_p = sub_vector(hit.point, cone->apex);
    double proj_len = dot_vector(apex_to_p, axis);
    t_vector proj = mul_vector(axis, proj_len);
    hit.normal = sub_vector(apex_to_p, mul_vector(proj, 1 + k));
	normalize_vector(&hit.normal);  
    // Inverser la normale si le rayon est à l'intérieur
    if (dot_vector(hit.normal, ray->direction) > 0)
        hit.normal = mul_vector(hit.normal, -1); 
    hit.distance = t;
    hit.hit = 1;
    hit.color = choose_co_color(cone, hit);
    hit.shininess = cone->shininess;
    hit.reflectivity = cone->reflectivity;
    return hit;
}
