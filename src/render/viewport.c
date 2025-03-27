#include "../includes/miniRT.h"

t_viewport	viewport(t_program *prog)
{
	t_viewport	view;
	t_vector	horizontal;
	t_vector	vertical;

// 	view.asp_ratio = (double) WIDTH / HEIGHT;
// 	view.fov = DEG_TO_RAD(prog->file->camera.fov);
// 	view.height = 2.0 * tan(view.fov / 2.0);
// 	view.width = view.height * view.asp_ratio;
// 	view.world_up = vector(0, 1, 0);
// 	view.forward = prog->file->camera.direction;
// 	normalize_vector(&view.forward);
// 	view.right = cross_vector(view.forward, view.world_up);
// 	normalize_vector(&view.right);
// 	view.up = cross_vector(view.right, view.forward);
// 	normalize_vector(&view.up);
// 	horizontal = mul_vector(view.right, view.width);
// 	vertical = mul_vector(view.up, view.height);

// 	// Correction : Bien positionner l'origine du viewport
// 	view.origin = prog->file->camera.origin;
// 	// view.origin = sub_vector(add_vector(prog->file->camera.origin, view.forward),
// 	// 	add_vector(mul_vector(view.right, 0.5 * view.width), mul_vector(view.up, 0.5 * view.height)));

// 	return (view);
// }


double vector_length(t_vector v)
{
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

// Deepseek correction
t_viewport    viewport(t_program *prog)
{
    t_viewport    view;
    t_vector    horizontal;
    t_vector    vertical;
    double      focal_dist = 1.0; // Distance focale arbitraire (peut être ajustée)

    // 1. Calculer le ratio et la taille du viewport
    view.asp_ratio = (double) WIDTH / HEIGHT;
    view.fov = DEG_TO_RAD (prog->file->camera.fov);
	view.width = 2.0 * tan(view.fov / 2.0);
	view.height = view.width / view.asp_ratio; 

    // 2. Définir les vecteurs de base de la caméra (forward, right, up)
    view.world_up = vector(0, 1, 0); // Up par défaut
    view.forward = prog->file->camera.direction;
    normalize_vector(&view.forward);

    // Calculer right et up orthogonaux
    view.right = cross_vector(view.forward, view.world_up);
    if (vector_length(view.right) < 1e-6) { // Cas où forward est parallèle à world_up
        view.world_up = vector(1, 0, 0); // Changer world_up pour éviter le vecteur nul
        view.right = cross_vector(view.forward, view.world_up);
    }
    normalize_vector(&view.right);
    view.up = cross_vector(view.right, view.forward); // Up réel (déjà normalisé car right et forward le sont)

    // 3. Calculer les coins du viewport
    // - Le centre du viewport est à camera.origin + focal_dist * forward
    // - Les coins sont calculés à partir du centre ± (width/2 * right) ± (height/2 * up)
    t_vector viewport_center = add_vector(prog->file->camera.origin, 
                                        mul_vector(view.forward, focal_dist));
    
    horizontal = mul_vector(view.right, view.width);  // Vecteur horizontal total
    vertical = mul_vector(view.up, view.height);     // Vecteur vertical total

    // Coin inférieur gauche (pour le lancer de rayons)
    view.origin = sub_vector(viewport_center, 
                            add_vector(mul_vector(horizontal, 0.5), 
                                      mul_vector(vertical, 0.5)));

    // Stocker aussi les vecteurs horizontaux/verticaux pour le lancer de rayons
    view.horizontal = horizontal;
    view.vertical = vertical;

    return (view);
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

