#include "../includes/miniRT.h"

t_ray generate_ray(t_viewport *view, int x, int y) {
    double new_x;
    double new_y;
    t_ray ray;

    // Calcul des coordonnées x et y du rayon en prenant en compte l'aspiration de l'écran
    new_x = ((x + 0.5) / WIDTH - 0.5) * view->width;
    new_y = (0.5 - (y + 0.5) / HEIGHT) * view->height;

    // Calcul de la direction du rayon
    ray.direction = add_vector(add_vector(view->forward, mul_vector(view->right, new_x)), mul_vector(view->up, new_y));
    normalize_vector(&ray.direction);

    // L'origine du rayon vient de l'origine de la caméra
    ray.origin = view->origin;

    return ray;
}

t_ray	generate_light_ray(t_hit hit, t_light light)
{
	t_ray		ray;
	t_vector	to_light;

	to_light = sub_vector(light.position, hit.point);
	ray.origin = add_vector(hit.point, mul_vector(hit.normal, 1e-4));
	ray.direction = to_light;
	normalize_vector(&ray.direction);
    ray.distance = distance_vector(hit.point, light.position);
	return (ray);
}







// 🔁 Étapes du rendu dans le bon ordre
// ✅ 1. Lancer un rayon depuis la caméra pour chaque pixel
// Appel de ta fonction generate_ray() pour obtenir un t_ray pour chaque (x, y)

// ✅ 2. Tester l’intersection entre ce rayon et tous les objets de la scène
// Tu parcours tous les objets (sphère, plan, cylindre…)

// Pour chaque objet, tu appelles sa fonction d’intersection (par exemple intersect_sphere(ray, sphere))

// Tu conserves l’objet intersecté le plus proche (le plus petit t > 0)

// C’est le vrai cœur du ray tracing : “quel objet ce rayon touche-t-il en premier ?”

// ✅ 3. Si aucune intersection : pixel = couleur de fond
// Par exemple :

// c
// Copier
// Modifier
// put_pixel(prog->img, x, y, rgb_to_color(0, 0, 0)); // noir
// ✅ 4. Si intersection : calculer la lumière au point touché
// 💡 Pour ça, tu fais :

// 🔹 4.1 – Calcul du point d’intersection
// c
// Copier
// Modifier
// hit_point = ray.origin + t * ray.direction;
// 🔹 4.2 – Calcul de la normale à la surface
// Pour une sphère :

// c
// Copier
// Modifier
// normal = normalize(hit_point - sphere->center);
// 🔹 4.3 – Calcul de la lumière (modèle de Lambert)
// c
// Copier
// Modifier
// light_dir = normalize(light->position - hit_point);
// diffuse = max(0, dot(normal, light_dir));
// 🔹 4.4 – Ombres (facultatif au début)
// Tu peux relancer un rayon shadow_ray depuis hit_point vers la lumière

// S’il touche un autre objet avant la lumière ➜ le point est dans l’ombre

// ✅ 5. Calcul de la couleur finale
// c
// Copier
// Modifier
// final_color = ambient + (diffuse * object_color);
// Tu peux d’abord commencer avec un éclairage ambiant uniquement, puis ajouter la lumière directe et les ombres après.

// 🧱 Plan clair et concret (ordre à suivre) :
// ✅ generate_ray() pour chaque pixel

// ✅ intersect_sphere() (et autres plus tard)

// ✅ trace_ray() → retourne une couleur uint32_t

// ✅ put_pixel()

// 🖼️ render() → appelle tout ça et affiche l’image

