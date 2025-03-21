#include "../includes/miniRT.h"

int	is_inter_sphere(t_camera ray, t_sphere sphere, double *t)
{
	t_vector	vector;
	double		radius;
	double		discriminant;
	double		a;
	double		b;
	double		c;
	double		t1;
	double		t2;

	vector = subtract_vector(ray.origin, sphere.position);
	radius = sphere.diameter / 2.0;
	a = dot_vector(ray.direction, ray.direction);
	b = 2.0 * dot_vector(vector, ray.direction);
	c = dot_vector(vector, vector) - (radius * radius);
	discriminant = (b * b) - 4 * (a * c);
	if (discriminant < 0)
		return (0);
	if (fabs(a) < 1e-6)
        return (0);
	t1 = (-b - sqrt(discriminant)) / (2.0 * a);
	t2 = (-b + sqrt(discriminant)) / (2.0 * a);
	if (t1 > 0)
		*t = t1;
	else if (t2 > 0)
		*t = t2;
	else
		return (0);
	return (1);
}

int	is_inter_cylinder(t_camera ray, t_cylinder cylinder, double *t)
{
	t_vector	vector;
	t_vector	inter_point;
	double		radius;
	double		discriminant;
	double		projection;
	double		a;
	double		b;
	double		c;
	double		t1;
	double 		t2;

	vector = subtract_vector(ray.origin, cylinder.position);
	radius = cylinder.diameter / 2;
	a = dot_vector(ray.direction, ray.direction) - pow(dot_vector(ray.direction, cylinder.normal), 2);
	b = 2 * (dot_vector(ray.direction, vector) - dot_vector(ray.direction, cylinder.normal) * dot_vector(vector, cylinder.normal));
	c = dot_vector(vector, vector) - pow(dot_vector(vector, cylinder.normal), 2) - radius * radius;
	discriminant = (b * b) - 4 * (a * c);
	if (discriminant < 0)
		return (0);
	t1 = (-b - sqrt(discriminant)) / (2.0 * a);
	t2 = (-b + sqrt(discriminant)) / (2.0 * a);
	if (t1 > 0)
		*t = t1;
	else if (t2 > 0)
		*t = t2;
	else
		return (0);
	inter_point = add_vector(ray.origin, scale_vector(ray.direction, *t));
	projection = dot_vector(subtract_vector(inter_point, cylinder.position), cylinder.normal);
	if (projection < 0 || projection > cylinder.height)
		return (0);
	return (1);
}

int	is_inter_plane(t_camera ray, t_plane plane, double *t)
{
	t_vector	vector;
	double		denom;

	denom = dot_vector(plane.normal, ray.direction);
	if (fabs(denom) > 1e-6)
	{
		vector = subtract_vector(plane.position, ray.origin);
		*t = dot_vector(vector, plane.normal) / denom;
		return (*t > 0);
	}
	return (0);
}


//TEST IS_INTER_SPHERE

// int main() {
//     t_camera ray;
//     t_sphere sphere;
//     double t;

//     // 🔹 Cas 1 : Intersection simple devant la caméra
//     ray.origin = (t_vector){0, 0, -5};
//     ray.direction = (t_vector){0, 0, 1};
//     sphere.position = (t_vector){0, 0, 0};
//     sphere.diameter = 2.0;

//     if (is_inter_sphere(ray, sphere, &t))
//         printf("✅ Test 1 OK, intersection à t = %f\n", t);
//     else
//         printf("❌ Test 1 FAIL, pas d'intersection\n");

//     // 🔹 Cas 2 : Rayon qui ne touche pas la sphère
//     ray.origin = (t_vector){0, 0, -5};
//     ray.direction = (t_vector){1, 0, 1};  // Direction inclinée
//     sphere.position = (t_vector){0, 0, 0};
//     sphere.diameter = 2.0;

//     if (!is_inter_sphere(ray, sphere, &t))
//         printf("✅ Test 2 OK, pas d'intersection\n");
//     else
//         printf("❌ Test 2 FAIL, intersection incorrecte à t = %f\n", t);

//     // 🔹 Cas 3 : Rayon partant de l'intérieur de la sphère
//     ray.origin = (t_vector){0, 0, 0};
//     ray.direction = (t_vector){0, 0, 1};
//     sphere.position = (t_vector){0, 0, 0};
//     sphere.diameter = 2.0;

//     if (is_inter_sphere(ray, sphere, &t))
//         printf("✅ Test 3 OK, intersection à t = %f\n", t);
//     else
//         printf("❌ Test 3 FAIL, pas d'intersection\n");

//     return 0;
// }


//TEST IS_INTER_PLANE

// int main()
// {
//     t_camera ray;
//     t_plane plane;
//     double t;

//     // 🔹 Cas 1 : Intersection simple devant la caméra
//     ray.origin = (t_vector){0, 0, -5};
//     ray.direction = (t_vector){0, 0, 1}; // Rayon qui pointe vers l'axe Z
//     plane.position = (t_vector){0, 0, 5}; // Plan situé à z = 5
//     plane.normal = (t_vector){0, 0, -1};  // Normale dirigée vers le bas

//     if (is_inter_plane(ray, plane, &t))
//         printf("✅ Test 1 OK, intersection à t = %f\n", t);
//     else
//         printf("❌ Test 1 FAIL, pas d'intersection\n");

//     // 🔹 Cas 2 : Rayon parallèle au plan
//     ray.origin = (t_vector){0, 0, -5};
//     ray.direction = (t_vector){1, 0, 0};  // Rayon parallèle au plan (direction sur l'axe X)
//     plane.position = (t_vector){0, 0, 5}; // Plan situé à z = 5
//     plane.normal = (t_vector){0, 0, -1};  // Normale dirigée vers le bas

//     if (!is_inter_plane(ray, plane, &t))
//         printf("✅ Test 2 OK, pas d'intersection (rayon parallèle)\n");
//     else
//         printf("❌ Test 2 FAIL, intersection incorrecte à t = %f\n", t);

//     // 🔹 Cas 3 : Rayon partant de l'intérieur du plan
//     ray.origin = (t_vector){0, 0, 5}; // Rayon partant du plan (même position)
//     ray.direction = (t_vector){0, 0, 1}; // Rayon pointant vers l'extérieur du plan
//     plane.position = (t_vector){0, 0, 5}; // Plan situé à z = 5
//     plane.normal = (t_vector){0, 0, -1};  // Normale dirigée vers le bas

//     if (!is_inter_plane(ray, plane, &t))
//         printf("✅ Test 3 OK, pas d'intersection (rayon à l'intérieur du plan)\n");
//     else
//         printf("❌ Test 3 FAIL, intersection incorrecte à t = %f\n", t);

//     // 🔹 Cas 4 : Rayon qui touche le plan à un angle
//     ray.origin = (t_vector){0, 0, -5};
//     ray.direction = (t_vector){1, 1, 1};  // Rayon incliné (direction diagonale)
//     plane.position = (t_vector){0, 0, 5}; // Plan situé à z = 5
//     plane.normal = (t_vector){0, 0, -1};  // Normale dirigée vers le bas

//     if (is_inter_plane(ray, plane, &t))
//         printf("✅ Test 4 OK, intersection à t = %f\n", t);
//     else
//         printf("❌ Test 4 FAIL, pas d'intersection\n");

//     return 0;
// }

//TEST IS_INTER_CYLINDER

int main()
{
    t_camera ray;
    t_cylinder cylinder;
    double t;

    // 🔹 Cas 1 : Intersection simple devant la caméra
    ray.origin = (t_vector){0, 0, -5};  // Rayon partant de (0, 0, -5)
    ray.direction = (t_vector){0, 0, 1};  // Rayon dirigé vers l'axe Z
    cylinder.position = (t_vector){0, 0, 0};  // Cylindre centré à l'origine
    cylinder.normal = (t_vector){0, 1, 0};  // Normale du cylindre (verticale)
    cylinder.diameter = 2;  // Diamètre du cylindre
    cylinder.height = 10;  // Hauteur du cylindre

    if (is_inter_cylinder(ray, cylinder, &t))
        printf("✅ Test 1 OK, intersection à t = %f\n", t);
    else
        printf("❌ Test 1 FAIL, pas d'intersection\n");

    // 🔹 Cas 2 : Rayon parallèle au cylindre
    ray.origin = (t_vector){0, 0, -5};  // Rayon partant de (0, 0, -5)
    ray.direction = (t_vector){1, 0, 0};  // Rayon parallèle à l'axe X
    if (!is_inter_cylinder(ray, cylinder, &t))
        printf("✅ Test 2 OK, pas d'intersection (rayon parallèle)\n");
    else
        printf("❌ Test 2 FAIL, intersection incorrecte à t = %f\n", t);

    // 🔹 Cas 3 : Rayon partant de l'intérieur du cylindre
    ray.origin = (t_vector){0, 0, 2};  // Rayon partant de l'intérieur du cylindre
    ray.direction = (t_vector){0, 0, 1};  // Rayon dirigé vers l'extérieur du cylindre
    if (is_inter_cylinder(ray, cylinder, &t))
        printf("✅ Test 3 OK, intersection à t = %f\n", t);
    else
        printf("❌ Test 3 FAIL, pas d'intersection\n");

    // 🔹 Cas 4 : Rayon partant au-dessus du cylindre, sans intersection
    ray.origin = (t_vector){0, 5, -5};  // Rayon partant de (0, 5, -5)
    ray.direction = (t_vector){0, 0, 1};  // Rayon dirigé vers l'axe Z
    if (!is_inter_cylinder(ray, cylinder, &t))
        printf("✅ Test 4 OK, pas d'intersection (rayon au-dessus du cylindre)\n");
    else
        printf("❌ Test 4 FAIL, intersection incorrecte à t = %f\n", t);

    // 🔹 Cas 5 : Rayon qui touche le cylindre à un angle
    ray.origin = (t_vector){0, 0, -5};  // Rayon partant de (0, 0, -5)
    ray.direction = (t_vector){1, 1, 1};  // Rayon incliné (direction diagonale)
    if (is_inter_cylinder(ray, cylinder, &t))
        printf("✅ Test 5 OK, intersection à t = %f\n", t);
    else
        printf("❌ Test 5 FAIL, pas d'intersection\n");

    return 0;
}
