#include "../includes/miniRT.h"

int is_inter_plane(t_camera *ray, t_plane *plane, t_hit *hit)
{
	t_vector	normal;
	t_vector	vector;
	t_vector	scaled_direction;  // Variable pour stocker la direction mise à l'échelle
	double		denom;

	normalize_vector(&plane->normal);  // Normaliser la normale du plan
	normal = plane->normal;  // Assigner la normale du plan à `normal`
	denom = dot_vector(normal, ray->direction);  // Calculer le dénominateur du plan
	if (fabs(denom) > 1e-6)  // Si le dénominateur n'est pas proche de zéro
	{
		vector = sub_vector(plane->position, ray->origin);  // Vecteur entre l'origine du rayon et le plan
		hit->distance = dot_vector(vector, normal) / denom;  // Calcul de la distance d'intersection
		if (hit->distance >= 1e-6)  // Si la distance est positive
		{
			// Utilisation correcte de mul_vector pour multiplier la direction du rayon par la distance
			scaled_direction = mul_vector(ray->direction, hit->distance);  // Calcul du point d'intersection
			hit->point = add_vector(ray->origin, scaled_direction);  // Calcul du point d'intersection
			hit->normal = normal;  // La normale du plan est la normale du plan
			hit->color = plane->color;  // La couleur du plan
			return (1);  // Retourner vrai si il y a une intersection
		}
	}
	return (0);  // Retourner faux si aucune intersection n'a eu lieu
}

int	is_inter_sphere(t_camera ray, t_sphere sphere, t_hit *hit)
{
	t_vector	vector;
	double		discriminant;
	double		t;
	double		sqrt_discriminant;

	vector = sub_vector(ray.origin, sphere.position); // Vector from ray origin to sphere center
	discriminant = pow(2 * dot_vector(vector, ray.direction), 2)
				 - 4 * dot_vector(ray.direction, ray.direction)
				 * (dot_vector(vector, vector) - sphere.rayon2); // Discriminant calculation
	if (discriminant < 0)
		return (0);
	sqrt_discriminant = sqrt(discriminant); // Calculate the square root of discriminant
	t = (-2 * dot_vector(vector, ray.direction) - sqrt_discriminant)
		/ (2 * dot_vector(ray.direction, ray.direction)); // t1
	if (t < 1e-6) // If t1 < 0, check for the second intersection t2
		t = (-2 * dot_vector(vector, ray.direction) + sqrt_discriminant)
			/ (2 * dot_vector(ray.direction, ray.direction)); // t2
	if (t < 1e-6) // No valid intersection
		return (0);
	mul_vector(hit->point, t); // Calculate the point of intersection
	hit->normal = sub_vector(hit->point, sphere.position); // Calculate the normal vector
	normalize_vector(&hit->normal); // Normalize the normal vector
	hit->distance = t; // Store the intersection distance
	hit->color = sphere.color; // Store the sphere's color
	return (1);
}

// int infinite_cyl_inter(t_camera *ray, t_cylinder *cy, t_hit *hit)
// {
//     t_quadratic q;
//     t_vector u, v;

//     u = cross_vector(ray->direction, cy->orientation);
//     v = sub_vector(cy->position, ray->origin);
//     v = cross_vector(v, cy->orientation);

//     q.a = dot_vector(u, u);
//     q.b = 2 * dot_vector(u, v);
//     q.c = dot_vector(v, v) - cy->rayon2;

//     printf("\n[DEBUG] Résolution quadratique :\n");
//     printf("a = %f, b = %f, c = %f\n", q.a, q.b, q.c);

//     if (q.a == 0)
//     {
//         printf("[ERREUR] a = 0, la direction du rayon est parallèle au cylindre !\n");
//         return 0;
//     }

//     if (!is_quadratic(&q))
//     {
//         printf("[ERREUR] Pas de solution réelle pour l'intersection !\n");
//         return 0;
//     }

//     printf("[DEBUG] Racines trouvées : t1 = %f, t2 = %f\n", q.t1, q.t2);

//     if (q.t1 <= 1e-6 && q.t2 <= 1e-6)
//         return 0;

//     if (q.t1 > q.t2)
//     {
//         double tmp = q.t1;
//         q.t1 = q.t2;
//         q.t2 = tmp;
//     }

//     if (q.t1 <= 1e-6 || (q.t2 > 1e-6 && (q.t2 < q.t1)))
//         q.t1 = q.t2;

//     hit->distance = q.t1;
//     ray_mul(&hit->point, ray, q.t1);  // Calcul du point d'impact avec t1

//     printf("[DEBUG] Avant d'assigner, t1 = %f, t2 = %f\n", q.t1, q.t2);
//     printf("[DEBUG] Intersection à t1 = %f\n", q.t1);
//     printf("[DEBUG] Point d'impact : (%f, %f, %f)\n", hit->point.x, hit->point.y, hit->point.z);

//     v = sub_vector(cy->position, hit->point);
//     hit->normal = cross_vector(v, cy->orientation);
//     hit->normal = cross_vector(hit->normal, cy->orientation);
//     normalize_vector(&hit->normal);

//     if (dot_vector(hit->normal, ray->direction))
//         hit->normal = inv_vector(hit->normal);

//     return 1;
// }

// int	is_inter_cylinder(t_camera *ray, t_cylinder *cy, t_hit *hit)
// {
// 	t_plane	pl;
// 	t_hit	tmp_hit;

// 	hit->distance = INFINITY;
// 	pl.position = cy->p1;
// 	pl.normal = cy->orientation;
// 	if (is_inter_plane(ray, &pl, &tmp_hit)
// 		&& distance_vector(tmp_hit.point, cy->p1)
// 		<= cy->diameter * 0.5 && hit->distance > tmp_hit.distance)
// 	{
// 		printf("\n[DEBUG] Intersection avec une base trouvée !\n");
// 		printf("Distance: %f\n", tmp_hit.distance);
// 		printf("Point d'impact: (%f, %f, %f)\n", tmp_hit.point.x, tmp_hit.point.y, tmp_hit.point.z);
// 		printf("Distance au centre de la base: %f\n", distance_vector(tmp_hit.point, pl.position));
// 		*hit = tmp_hit;
// 	}
// 	else
// 		printf("[DEBUG] Aucune intersection avec cette base.\n");
// 	pl.position = cy->p2;
// 	if (is_inter_plane(ray, &pl, &tmp_hit)
// 		&& distance_vector(tmp_hit.point, cy->p2) <= cy->diameter * 0.5
// 		&& hit->distance > tmp_hit.distance)
// 		*hit = tmp_hit;
// 	if (infinite_cyl_inter(ray, cy, &tmp_hit)
// 		&& pow(distance_vector(cy->position, tmp_hit.point), 2)
// 		<= pow(cy->height * 0.5, 2) + cy->rayon2
// 		&& hit->distance > tmp_hit.distance)
// 		*hit = tmp_hit;
// 	return (hit->distance < INFINITY && hit->distance > 1e-6);
// }

//TEST IS_INTER_SPHERE
// int main() {
//     t_camera ray;
//     t_sphere sphere;
//     t_hit hit;

//     // 🔹 Cas 1 : Intersection simple devant la caméra
//     ray.origin = (t_vector){0, 0, -5};
//     ray.direction = (t_vector){0, 0, 1};
//     sphere.position = (t_vector){0, 0, 0};
//     sphere.diameter = 2.0;
//     sphere.rayon2 = (sphere.diameter / 2) * (sphere.diameter / 2);  // Rayon²
//     sphere.color = 0xFF0000;  // Rouge

//     if (is_inter_sphere(ray, sphere, &hit)) {
//         printf("✅ Test 1 OK, intersection à t = %f, couleur : 0x%x\n", hit.distance, hit.color);
//     } else {
//         printf("❌ Test 1 FAIL, pas d'intersection\n");
//     }

//     // 🔹 Cas 2 : Rayon qui ne touche pas la sphère
//     ray.origin = (t_vector){0, 0, -5};
//     ray.direction = (t_vector){1, 0, 1};  // Direction inclinée
//     sphere.position = (t_vector){0, 0, 0};
//     sphere.diameter = 2.0;
//     sphere.rayon2 = (sphere.diameter / 2) * (sphere.diameter / 2);
//     sphere.color = 0x00FF00;  // Vert

//     if (!is_inter_sphere(ray, sphere, &hit)) {
//         printf("✅ Test 2 OK, pas d'intersection\n");
//     } else {
//         printf("❌ Test 2 FAIL, intersection incorrecte à t = %f\n", hit.distance);
//     }

//     // 🔹 Cas 3 : Rayon partant de l'intérieur de la sphère
//     ray.origin = (t_vector){0, 0, 0};
//     ray.direction = (t_vector){0, 0, 1};
//     sphere.position = (t_vector){0, 0, 0};
//     sphere.diameter = 2.0;
//     sphere.rayon2 = (sphere.diameter / 2) * (sphere.diameter / 2);
//     sphere.color = 0x0000FF;  // Bleu

//     if (is_inter_sphere(ray, sphere, &hit)) {
//         printf("✅ Test 3 OK, intersection à t = %f, couleur : 0x%x\n", hit.distance, hit.color);
//     } else {
//         printf("❌ Test 3 FAIL, pas d'intersection\n");
//     }

//     // 🔹 Cas 4 : Rayon parallèle à la sphère (pas d'intersection)
//     ray.origin = (t_vector){0, 0, -5};
//     ray.direction = (t_vector){1, 0, 0};  // Direction parallèle à l'axe X
//     sphere.position = (t_vector){0, 0, 0};
//     sphere.diameter = 2.0;
//     sphere.rayon2 = (sphere.diameter / 2) * (sphere.diameter / 2);
//     sphere.color = 0xFFFF00;  // Jaune

//     if (!is_inter_sphere(ray, sphere, &hit)) {
//         printf("✅ Test 4 OK, pas d'intersection\n");
//     } else {
//         printf("❌ Test 4 FAIL, intersection incorrecte à t = %f\n", hit.distance);
//     }

//     // 🔹 Cas 5 : Rayon tangent à la sphère
//     ray.origin = (t_vector){0, -1, -5};
//     ray.direction = (t_vector){0, 0, 1};  // Rayon tangent à la sphère
//     sphere.position = (t_vector){0, 0, 0};
//     sphere.diameter = 2.0;
//     sphere.rayon2 = (sphere.diameter / 2) * (sphere.diameter / 2);
//     sphere.color = 0x00FFFF;  // Cyan

//     if (is_inter_sphere(ray, sphere, &hit)) {
//         printf("✅ Test 5 OK, intersection à t = %f, couleur : 0x%x\n", hit.distance, hit.color);
//     } else {
//         printf("❌ Test 5 FAIL, pas d'intersection\n");
//     }

//     return 0;
// }

//TEST IS_INTER_PLANE
// int main() {
// 	t_camera ray;
// 	t_plane plane;
// 	t_hit hit;

// 	// 🔹 Cas 1 : Intersection simple devant la caméra
// 	ray.origin = (t_vector){0, 0, -5};
// 	ray.direction = (t_vector){0, 0, 1}; // Rayon qui pointe vers l'axe Z
// 	plane.position = (t_vector){0, 0, 5}; // Plan situé à z = 5
// 	plane.normal = (t_vector){0, 0, -1};  // Normale dirigée vers le bas
// 	plane.color = 1;  // Exemple de couleur (arbitraire)

// 	if (is_inter_plane(&ray, &plane, &hit))
// 		printf("✅ Test 1 OK, intersection à t = %f, point d'impact = (%f, %f, %f), normale = (%f, %f, %f), couleur = %d\n",
// 			hit.distance, hit.point.x, hit.point.y, hit.point.z, hit.normal.x, hit.normal.y, hit.normal.z, hit.color);
// 	else
// 		printf("❌ Test 1 FAIL, pas d'intersection\n");

// 	// 🔹 Cas 2 : Rayon parallèle au plan
// 	ray.origin = (t_vector){0, 0, -5};
// 	ray.direction = (t_vector){1, 0, 0};  // Rayon parallèle au plan (direction sur l'axe X)
// 	plane.position = (t_vector){0, 0, 5}; // Plan situé à z = 5
// 	plane.normal = (t_vector){0, 0, -1};  // Normale dirigée vers le bas

// 	if (!is_inter_plane(&ray, &plane, &hit))
// 		printf("✅ Test 2 OK, pas d'intersection (rayon parallèle)\n");
// 	else
// 		printf("❌ Test 2 FAIL, intersection incorrecte à t = %f\n", hit.distance);

// 	// 🔹 Cas 3 : Rayon partant de l'intérieur du plan
// 	ray.origin = (t_vector){0, 0, 5}; // Rayon partant du plan (même position)
// 	ray.direction = (t_vector){0, 0, 1}; // Rayon pointant vers l'extérieur du plan
// 	plane.position = (t_vector){0, 0, 5}; // Plan situé à z = 5
// 	plane.normal = (t_vector){0, 0, -1};  // Normale dirigée vers le bas

// 	if (!is_inter_plane(&ray, &plane, &hit))
// 		printf("✅ Test 3 OK, pas d'intersection (rayon à l'intérieur du plan)\n");
// 	else
// 		printf("❌ Test 3 FAIL, intersection incorrecte à t = %f\n", hit.distance);

// 	// 🔹 Cas 4 : Rayon qui touche le plan à un angle
// 	ray.origin = (t_vector){0, 0, -5};
// 	ray.direction = (t_vector){1, 1, 1};  // Rayon incliné (direction diagonale)
// 	plane.position = (t_vector){0, 0, 5}; // Plan situé à z = 5
// 	plane.normal = (t_vector){0, 0, -1};  // Normale dirigée vers le bas

// 	if (is_inter_plane(&ray, &plane, &hit))
// 		printf("✅ Test 4 OK, intersection à t = %f, point d'impact = (%f, %f, %f), normale = (%f, %f, %f), couleur = %d\n",
// 			hit.distance, hit.point.x, hit.point.y, hit.point.z, hit.normal.x, hit.normal.y, hit.normal.z, hit.color);
// 	else
// 		printf("❌ Test 4 FAIL, pas d'intersection\n");

// 	return 0;
// }

//TEST IS_INFINITE_CYLINDER
int main()
{
    // Déclaration de rayons (avec origine et direction)
    t_camera ray1, ray2, ray3;
    ray1.origin = (t_vector){0.0f, 0.0f, 0.0f};
    ray1.direction = (t_vector){1.0f, 0.0f, 0.0f};  // Rayon orienté le long de l'axe X

    ray2.origin = (t_vector){0.0f, 0.0f, -2.0f};
    ray2.direction = (t_vector){0.0f, 0.0f, 1.0f};  // Rayon dirigé le long de l'axe Z

    ray3.origin = (t_vector){-1.0f, 0.0f, 0.0f};
    ray3.direction = (t_vector){1.0f, 0.0f, 0.0f};  // Rayon orienté le long de l'axe X, côté négatif

    // Déclaration de cylindres (avec position, orientation, rayon, et hauteur)
    t_cylinder cyl1, cyl2, cyl3;
    
    cyl1.position = (t_vector){1.0f, 0.0f, 0.0f};  // Cylindre centré à (1, 0, 0)
    cyl1.orientation = (t_vector){0.0f, 1.0f, 0.0f}; // Cylindre orienté le long de l'axe Y
    cyl1.rayon2 = 1.0f;  // Rayon au carré du cylindre
    cyl1.height = 5.0f;   // Hauteur du cylindre
    cyl1.p1 = (t_vector){0.0f, -2.5f, 0.0f};  // Base inférieure
    cyl1.p2 = (t_vector){0.0f, 2.5f, 0.0f};   // Base supérieure

    cyl2.position = (t_vector){0.0f, 0.0f, 0.0f};  // Cylindre centré à l'origine
    cyl2.orientation = (t_vector){0.0f, 1.0f, 0.0f}; // Cylindre orienté le long de l'axe Y
    cyl2.rayon2 = 0.5f;  // Rayon au carré du cylindre
    cyl2.height = 4.0f;   // Hauteur du cylindre
    cyl2.p1 = (t_vector){-0.25f, -2.0f, 0.0f};  // Base inférieure
    cyl2.p2 = (t_vector){-0.25f, 2.0f, 0.0f};   // Base supérieure

    cyl3.position = (t_vector){0.0f, 0.0f, 0.0f};  // Cylindre centré à l'origine
    cyl3.orientation = (t_vector){1.0f, 0.0f, 0.0f}; // Cylindre orienté le long de l'axe X
    cyl3.rayon2 = 2.0f;  // Rayon au carré du cylindre
    cyl3.height = 5.0f;   // Hauteur du cylindre
    cyl3.p1 = (t_vector){-1.0f, -2.5f, 0.0f};  // Base inférieure
    cyl3.p2 = (t_vector){-1.0f, 2.5f, 0.0f};   // Base supérieure

    // Variables pour stocker les résultats d'impact
    t_hit hit1, hit2, hit3;

    // Test 1 : Intersection entre le rayon 1 et cylindre 1
    printf("Test 1 : Intersection entre ray1 et cylindre1\n");
    if (is_inter_cylinder(&ray1, &cyl1, &hit1))
    {
        printf("Intersection trouvée!\n");
        printf("Distance de l'impact: %f\n", hit1.distance);
        printf("Point d'impact: (%f, %f, %f)\n", hit1.point.x, hit1.point.y, hit1.point.z);
        printf("Normale à l'impact: (%f, %f, %f)\n", hit1.normal.x, hit1.normal.y, hit1.normal.z);
    }
    else
    {
        printf("Aucune intersection trouvée.\n");
    }

    // Test 2 : Intersection entre le rayon 2 et cylindre 2
    printf("\nTest 2 : Intersection entre ray2 et cylindre2\n");
    if (is_inter_cylinder(&ray2, &cyl2, &hit2))
    {
        printf("Intersection trouvée!\n");
        printf("Distance de l'impact: %f\n", hit2.distance);
        printf("Point d'impact: (%f, %f, %f)\n", hit2.point.x, hit2.point.y, hit2.point.z);
        printf("Normale à l'impact: (%f, %f, %f)\n", hit2.normal.x, hit2.normal.y, hit2.normal.z);
    }
    else
    {
        printf("Aucune intersection trouvée.\n");
    }

    // Test 3 : Intersection entre le rayon 3 et cylindre 3
    printf("\nTest 3 : Intersection entre ray3 et cylindre3\n");
    if (is_inter_cylinder(&ray3, &cyl3, &hit3))
    {
        printf("Intersection trouvée!\n");
        printf("Distance de l'impact: %f\n", hit3.distance);
        printf("Point d'impact: (%f, %f, %f)\n", hit3.point.x, hit3.point.y, hit3.point.z);
        printf("Normale à l'impact: (%f, %f, %f)\n", hit3.normal.x, hit3.normal.y, hit3.normal.z);
    }
    else
    {
        printf("Aucune intersection trouvée.\n");
    }

    return 0;
}
