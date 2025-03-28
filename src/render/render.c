#include "../includes/miniRT.h"

int multiply_colors(int c1, int c2)
{
    int r = ((c1 >> 16) & 0xFF) * ((c2 >> 16) & 0xFF) / 255;
    int g = ((c1 >> 8)  & 0xFF) * ((c2 >> 8)  & 0xFF) / 255;
    int b = (c1 & 0xFF) * (c2 & 0xFF) / 255;
    return ((r << 16) | (g << 8) | b);
}

// Additionne deux couleurs (capped à 255)
int add_colors(int c1, int c2) {
    int r = fmin(0xFF, ((c1 >> 16) & 0xFF) + ((c2 >> 16) & 0xFF));
    int g = fmin(0xFF, ((c1 >> 8)  & 0xFF) + ((c2 >> 8)  & 0xFF));
    int b = fmin(0xFF, (c1 & 0xFF) + (c2 & 0xFF));
    return ((r << 16) | (g << 8) | b);
}

int ambient_lighting(t_hit hit, t_ambient_light ambient)
{
    // 1. Extraire les composantes RGB de la lumière ambiante (avec ratio)
    int ambient_r = ((ambient.color >> 16) & 0xFF) * ambient.ratio;
    int ambient_g = ((ambient.color >> 8) & 0xFF) * ambient.ratio;
    int ambient_b = (ambient.color & 0xFF) * ambient.ratio;

    // 2. Extraire les composantes RGB de l'objet
    int obj_r = (hit.color >> 16) & 0xFF;
    int obj_g = (hit.color >> 8) & 0xFF;
    int obj_b = hit.color & 0xFF;

    // 3. Multiplier les couleurs (composante par composante) et normaliser
    int r = (obj_r * ambient_r) / 255;
    int g = (obj_g * ambient_g) / 255;
    int b = (obj_b * ambient_b) / 255;

    // 4. Clamper les valeurs (normalement inutile avec les calculs ci-dessus)
    r = fmin(r, 255);
    g = fmin(g, 255);
    b = fmin(b, 255);

    // 5. Reconstruire la couleur finale
    return ((r << 16) | (g << 8) | b);
}

static int	init_img(t_program *prog)
{
	t_image	*img;

	img = malloc(sizeof(t_image));
	if (!img)
		return (perror("malloc img failed"), 1);
	img->img_ptr = mlx_new_image(prog->mlx, WIDTH, HEIGHT);
	if (!img->img_ptr)
		return (perror("mlx_new_image failed"), free(img), 1);
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->size_line, &img->endian);
	if (!img->addr)
		return (perror("mlx_get_data_addr failed"), free(img), 1);
	prog->img = img;
	return (0);
}

void	render(t_program *prog)
{
	int			x;
	int			y;
	t_ray		ray;
	t_viewport	view;
	t_hit		hit;
	t_ray		light_ray;
	t_hit		shadow;
	int			color;

	view = viewport(prog);
	prog->view = &view;
	if (init_img(prog))
		return ; // sortir proprement
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray = generate_ray(&view, x, y);
			hit = inter_scene(&ray, prog->file);
			if (hit.hit == 0)
				color = 0;
			else
			{
				light_ray = generate_light_ray(hit, prog->file->light);
				shadow = inter_scene(&light_ray, prog->file);
				// if (shadow.hit)
				if (shadow.hit && shadow.distance < hit.distance)
					color = ambient_lighting(hit, prog->file->ambient_light);
				else
					color = phong_lighting(hit, prog->file->light, prog);
			}
			*(int *)(prog->img->addr + ((x + (y * WIDTH)) * (prog->img->bpp / 8))) = color;
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(prog->mlx, prog->win, prog->img->img_ptr, 0, 0);
	printf("IMAGE OK\n");
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

