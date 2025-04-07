#include "../../includes/miniRT_bonus.h"

void	get_cone_uv(t_hit *hit, t_cone *cone)
{
	t_vector	local;
	t_vector	axis = cone->axis; // doit être normalisé
	t_vector	height_proj;
	t_vector	radial;
	double		height;
	double		theta;

	// Vecteur depuis la base du cône vers le point d'impact
	local = sub_vector(hit->point, cone->axis);

	// Projette sur l'axe pour obtenir la hauteur
	height = dot_vector(local, axis);
	hit->v = height / cone->height; // facultatif : normalise v ∈ [0,1]

	// Partie radiale perpendiculaire à l'axe
	height_proj = mul_vector(axis, height);
	radial = sub_vector(local, height_proj);
	normalize_vector(&radial);

	// Calcul de l'angle autour du cône (u)
	theta = atan2(dot_vector(radial, cone->v), dot_vector(radial, cone->u));
	hit->u = 0.5 + theta / (2.0 * M_PI);
}

void	apply_cone_bump(t_hit *hit, t_cone *cone)
{
	double		tex_u;
	double		tex_v;
	int			px;
	int			py;

	if (!cone->xpm)
		return ;
	tex_u = fmod(fabs(hit->u), 1.0);
	tex_v = fmod(fabs(hit->v), 1.0);
	px = (int)(tex_u * cone->xpm->width);
	py = (int)(tex_v * cone->xpm->height);
	if (px >= cone->xpm->width)
		px = cone->xpm->width - 1;
	if (py >= cone->xpm->height)
		py = cone->xpm->height - 1;
	hit->normal = perturbed_normal(cone->xpm, px, py, hit->normal);
}

static int choose_co_color(t_cone *cone, t_hit hit)
{
	t_vector	dir;
	t_vector	axis;
	t_vector	radial;
	t_vector	u_vec, v_vec, w_vec;
	double		u, v;
	int			x, y;

	axis = cone->axis;
	w_vec = axis;

	// Base orthonormée locale temporaire (si cone->u/v non stockés)
	t_vector tmp = (fabs(w_vec.y) > 0.999) ? (t_vector){1, 0, 0} : (t_vector){0, 1, 0};
	u_vec = cross_vector(tmp, w_vec);
	normalize_vector(&u_vec);
	v_vec = cross_vector(w_vec, u_vec);
	normalize_vector(&v_vec);

	// Coordonnées locales
	dir = sub_vector(hit.point, cone->apex);
	radial = sub_vector(dir, mul_vector(w_vec, dot_vector(dir, w_vec)));
	u = 0.5 + atan2(dot_vector(radial, v_vec), dot_vector(radial, u_vec)) / (2 * M_PI);
	v = dot_vector(dir, w_vec) / cone->height;

	// ✅ Si texture XPM présente
	if (cone->xpm)
	{
		double tex_u = fmod(fabs(u), 1.0);
		double tex_v = fmod(fabs(v), 1.0);
		x = (int)(tex_u * cone->xpm->width);
		y = (int)(tex_v * cone->xpm->height);

		if (x >= cone->xpm->width)
			x = cone->xpm->width - 1;
		if (y >= cone->xpm->height)
			y = cone->xpm->height - 1;

		return get_pixel_color(cone->xpm, x, y);
	}

	// ✅ Sinon : checkerboard
	if (cone->chessboard)
	{
		x = (int)(floor(u * cone->scale));
		y = (int)(floor(v * cone->scale));
		if ((x + y) % 2 == 0)
			return (cone->color);
		else
			return (cone->color2);
	}

	// ✅ Sinon : couleur fixe
	return (cone->color);
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
	get_cone_uv(&hit, cone);
	apply_cone_bump(&hit, cone);
    hit.color = choose_co_color(cone, hit);
    hit.shininess = cone->shininess;
    hit.reflectivity = cone->reflectivity;
    return hit;
}
