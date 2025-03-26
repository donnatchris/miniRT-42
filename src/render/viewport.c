#include "../includes/miniRT.h"

t_viewport	viewport(t_program *prog)
{
	t_viewport	view;
	t_vector	horizontal;
	t_vector	vertical;

	view.fov = DEG_TO_RAD(prog->file->camera.fov);
	view.forward = prog->file->camera.direction;
	normalize_vector(&view.forward);
	view.world_up = vector(0, 1, 0);
	view.right = cross_vector(view.forward, view.world_up);
	normalize_vector(&view.right);
	view.up = cross_vector(view.right, view.forward);
	normalize_vector(&view.up);
	view.height = 2.0 * tan(view.fov / 2.0);
	view.asp_ratio = (double) WIDTH / HEIGHT;
	view.width = view.height * view.asp_ratio;
	horizontal = mul_vector(view.right, view.width);
	vertical = mul_vector(view.up, view.height);
	// view.origin = sub_vector(add_vector(prog->file->camera.origin, view.forward), sub_vector(mul_vector(horizontal, 0.5), mul_vector(vertical, 0.5)));
	view.origin = sub_vector(
	sub_vector(add_vector(prog->file->camera.origin, view.forward),
	           mul_vector(horizontal, 0.5)),
				mul_vector(vertical, 0.5));
	return (view);
}

t_ray	generate_ray(t_viewport *view, int x, int y)
{
	double		new_x;
	double		new_y;
	t_ray		ray;


	new_x = (2.0 * ((x + 0.5) / WIDTH) - 1) * view->width;
	new_y = (1.0 - 2.0 * ((y + 0.5) / HEIGHT)) * view->height;
	ray.direction = add_vector(add_vector(view->forward, mul_vector(view->right, new_x)), mul_vector(view->up, new_y));
	normalize_vector(&ray.direction);
	ray.origin = view->origin;
	return (ray);
}

t_ray	generate_light_ray(t_hit hit, t_light light)
{
	t_ray		ray;
	t_vector	to_light;

	to_light = sub_vector(light.position, hit.point);
	ray.origin = add_vector(hit.point, mul_vector(hit.normal, 1e-4));
	ray.direction = to_light;
	normalize_vector(&ray.direction);
	return (ray);
}

int	init_img(t_program *prog)
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

int	scale_color(int color, double factor)
{
	int	r;
	int	g;
	int	b;

	r = ((color >> 16) & 0xFF) * factor;
	g = ((color >> 8) & 0xFF) * factor;
	b = (color & 0xFF) * factor;

	if (r > 255) r = 255;
	if (g > 255) g = 255;
	if (b > 255) b = 255;

	return ((r << 16) | (g << 8) | b);
}

int	lambert_color(t_hit hit, t_light light)
{
	t_vector	light_dir;
	double		intensity;
	int			r, g, b;

	// Vecteur lumière normalisé
	light_dir = sub_vector(light.position, hit.point);
	normalize_vector(&light_dir);

	// Intensité diffus : cos(theta) = dot(normal, light_dir)
	intensity = dot_vector(hit.normal, light_dir);
	if (intensity < 0)
		intensity = 0;
	if (intensity > 1)
		intensity = 1;

	// On combine la couleur de la lumière et celle de l'objet
	r = ((hit.color >> 16) & 0xFF) * ((light.color >> 16) & 0xFF) / 255;
	g = ((hit.color >> 8) & 0xFF) * ((light.color >> 8) & 0xFF) / 255;
	b = (hit.color & 0xFF) * (light.color & 0xFF) / 255;

	// On applique l'intensité de lumière (et le ratio de la lumière)
	r = r * intensity * light.ratio;
	g = g * intensity * light.ratio;
	b = b * intensity * light.ratio;

	// Clamp
	if (r > 255) r = 255;
	if (g > 255) g = 255;
	if (b > 255) b = 255;

	return ((r << 16) | (g << 8) | b);
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
				color = scale_color(prog->file->ambient_light.color, prog->file->ambient_light.ratio);
			else
			{
				light_ray = generate_light_ray(hit, prog->file->light);
				shadow = inter_scene(&light_ray, prog->file);
				if (shadow.hit)
					color = scale_color(prog->file->ambient_light.color, prog->file->ambient_light.ratio);
				else
					// color = lambert_color(shadow, prog->file->light);
					color = hit.color;



					// int diffuse = lambert_color(hit, prog->file->light);
					// int ambient = scale_color(prog->file->ambient_light.color, prog->file->ambient_light.ratio);
					// color = add_colors(ambient, diffuse);
			}
			// *(int *)(prog->img->addr + ((x + (y * WIDTH)) * (prog->img->bpp / 8))) = color;
			*(int *)(prog->img->addr + (y * prog->img->size_line + x * (prog->img->bpp / 8))) = color;
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(prog->mlx, prog->win, prog->img->img_ptr, 0, 0);
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

