#include "../includes/miniRT.h"

int	is_inter_plane(t_camera *ray, t_plane *plane, t_hit *hit)
{
	t_vector	vector;
	double		denom;

	denom = dot_vector(plane->normal, ray->direction);
	if (fabs(denom) > 1e-6)
	{
		vector = sub_vector(plane->position, ray->origin);
		hit->distance = dot_vector(vector, plane->normal) / denom;
		if (hit->distance > 0)
		{
			scale_vector(&hit->point, ray, hit->distance);
			hit->normal = plane->normal;
			hit->color = plane->color;
			return (1);
		}
	}
	return (0);
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
    scale_vector(&hit->point, &ray, t); // Calculate the point of intersection
    hit->normal = sub_vector(hit->point, sphere.position); // Calculate the normal vector
    normalize_vector(&hit->normal); // Normalize the normal vector
    hit->distance = t; // Store the intersection distance
    hit->color = sphere.color; // Store the sphere's color
    return (1);
}

// int	is_inter_cylinder(t_camera ray, t_cylinder cylinder, double *t)
// {
// 	t_vector	vector;
// 	t_vector	inter_point;
// 	double		radius;
// 	double		discriminant;
// 	double		projection;
// 	double		a;
// 	double		b;
// 	double		c;
// 	double		t1;
// 	double 		t2;

// 	vector = sub_vector(ray.origin, cylinder.position);
// 	radius = cylinder.diameter / 2;
// 	a = dot_vector(ray.direction, ray.direction) - pow(dot_vector(ray.direction, cylinder.normal), 2);
// 	b = 2 * (dot_vector(ray.direction, vector) - dot_vector(ray.direction, cylinder.normal) * dot_vector(vector, cylinder.normal));
// 	c = dot_vector(vector, vector) - pow(dot_vector(vector, cylinder.normal), 2) - radius * radius;
// 	discriminant = (b * b) - 4 * (a * c);
// 	if (discriminant < 0)
// 		return (0);
// 	if (fabs(a) < 1e-6)
//         return (0);
// 	t1 = (-b - sqrt(discriminant)) / (2.0 * a);
// 	t2 = (-b + sqrt(discriminant)) / (2.0 * a);
// 	if (t1 > 0)
// 		*t = t1;
// 	else if (t2 > 0)
// 		*t = t2;
// 	else
// 		return (0);
// 	inter_point = add_vector(ray.origin, scale_vector(ray.direction, *t));
// 	projection = dot_vector(sub_vector(inter_point, cylinder.position), cylinder.normal);
// 	if (projection < 0 || projection > cylinder.height)
// 		return (0);
// 	return (1);
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
//     t_camera ray;
//     t_plane plane;
//     t_hit hit;

//     // 🔹 Cas 1 : Intersection simple devant la caméra
//     ray.origin = (t_vector){0, 0, -5};
//     ray.direction = (t_vector){0, 0, 1}; // Rayon qui pointe vers l'axe Z
//     plane.position = (t_vector){0, 0, 5}; // Plan situé à z = 5
//     plane.normal = (t_vector){0, 0, -1};  // Normale dirigée vers le bas
//     plane.color = 1;  // Exemple de couleur (arbitraire)

//     if (is_inter_plane(&ray, &plane, &hit))
//         printf("✅ Test 1 OK, intersection à t = %f, point d'impact = (%f, %f, %f), normale = (%f, %f, %f), couleur = %d\n",
//             hit.distance, hit.point.x, hit.point.y, hit.point.z, hit.normal.x, hit.normal.y, hit.normal.z, hit.color);
//     else
//         printf("❌ Test 1 FAIL, pas d'intersection\n");

//     // 🔹 Cas 2 : Rayon parallèle au plan
//     ray.origin = (t_vector){0, 0, -5};
//     ray.direction = (t_vector){1, 0, 0};  // Rayon parallèle au plan (direction sur l'axe X)
//     plane.position = (t_vector){0, 0, 5}; // Plan situé à z = 5
//     plane.normal = (t_vector){0, 0, -1};  // Normale dirigée vers le bas

//     if (!is_inter_plane(&ray, &plane, &hit))
//         printf("✅ Test 2 OK, pas d'intersection (rayon parallèle)\n");
//     else
//         printf("❌ Test 2 FAIL, intersection incorrecte à t = %f\n", hit.distance);

//     // 🔹 Cas 3 : Rayon partant de l'intérieur du plan
//     ray.origin = (t_vector){0, 0, 5}; // Rayon partant du plan (même position)
//     ray.direction = (t_vector){0, 0, 1}; // Rayon pointant vers l'extérieur du plan
//     plane.position = (t_vector){0, 0, 5}; // Plan situé à z = 5
//     plane.normal = (t_vector){0, 0, -1};  // Normale dirigée vers le bas

//     if (!is_inter_plane(&ray, &plane, &hit))
//         printf("✅ Test 3 OK, pas d'intersection (rayon à l'intérieur du plan)\n");
//     else
//         printf("❌ Test 3 FAIL, intersection incorrecte à t = %f\n", hit.distance);

//     // 🔹 Cas 4 : Rayon qui touche le plan à un angle
//     ray.origin = (t_vector){0, 0, -5};
//     ray.direction = (t_vector){1, 1, 1};  // Rayon incliné (direction diagonale)
//     plane.position = (t_vector){0, 0, 5}; // Plan situé à z = 5
//     plane.normal = (t_vector){0, 0, -1};  // Normale dirigée vers le bas

//     if (is_inter_plane(&ray, &plane, &hit))
//         printf("✅ Test 4 OK, intersection à t = %f, point d'impact = (%f, %f, %f), normale = (%f, %f, %f), couleur = %d\n",
//             hit.distance, hit.point.x, hit.point.y, hit.point.z, hit.normal.x, hit.normal.y, hit.normal.z, hit.color);
//     else
//         printf("❌ Test 4 FAIL, pas d'intersection\n");

//     return 0;
// }
