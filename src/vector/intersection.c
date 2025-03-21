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
