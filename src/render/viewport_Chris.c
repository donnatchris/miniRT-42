#include "../includes/miniRT.h"

t_viewport	viewport(t_program *prog)
{
	t_viewport	view;
	t_vector	horizontal;
	t_vector	vertical;

	view.asp_ratio = (double) WIDTH / HEIGHT;
	view.fov = DEG_TO_RAD(prog->file->camera.fov);
	view.height = 2.0 * tan(view.fov / 2.0);
	view.width = view.height * ((double) WIDTH / HEIGHT);
	view.world_up = vector(0, 1, 0);
	view.forward = normalize_vector(prog->file->camera.direction);
	view.right = normalize_vector(cross_vector(view.forward, view.world_up));
	view.up = normalize_vector(cross_vector(view.right, view.forward));
	horizontal = mul_vector(view.right, view.width);
	vertical = mul_vector(view.up, view.height);
	view.origin = sub_vector(add_vector(prog->file->camera.origin, view.forward), sub_vector(mul_vector(horizontal, 0.5), mul_vector(vertical, 0.5)));
	return (view);
}

t_ray	generate_ray(t_viewport *view, int x, int y)
{
	double		new_x;
	double		new_y;
	t_ray		ray;


	new_x = (2.0 * ((x + 0.5) / WIDTH) - 0.5) * view->width;
	new_y = (1.0 - 2.0 * ((y + 0.5) / HEIGHT)) * tan(view->fov / 2.0);
	ray.direction = normalize_vector(add_vector(add_vector(view->forward, mul_vector(view->right, new_x)), mul_vector(view->up, new_y)));
	ray.origin = view->origin;
	return (ray);
}

int get_color_pixel(t_ray *ray, t_file *file)
{
    t_hit hit;
    int color;

    if (is_inter_scene(ray, file->obj_list, &hit)) // Vérifie si le rayon intersecte un objet
        color = hit.color; // Couleur de l'objet touché
    else
        color = file->ambient_light.color; // Couleur de fond (ambiance)
    return (color);
}


int	init_img(t_program *prog)
{
	t_image	*img;

	img = malloc(sizeof(t_img));
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
			color = get_color_pixel(&ray, file); //recupere couleur du pixel
			//ft_coeur du programme a coder
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(prog->mlx, prog->win, prog->img->img_ptr, 0, 0);
}











🔁 Étapes du rendu dans le bon ordre
✅ 1. Lancer un rayon depuis la caméra pour chaque pixel
Appel de ta fonction generate_ray() pour obtenir un t_ray pour chaque (x, y)

✅ 2. Tester l’intersection entre ce rayon et tous les objets de la scène
Tu parcours tous les objets (sphère, plan, cylindre…)

Pour chaque objet, tu appelles sa fonction d’intersection (par exemple intersect_sphere(ray, sphere))

Tu conserves l’objet intersecté le plus proche (le plus petit t > 0)

C’est le vrai cœur du ray tracing : “quel objet ce rayon touche-t-il en premier ?”

✅ 3. Si aucune intersection : pixel = couleur de fond
Par exemple :

c
Copier
Modifier
put_pixel(prog->img, x, y, rgb_to_color(0, 0, 0)); // noir
✅ 4. Si intersection : calculer la lumière au point touché
💡 Pour ça, tu fais :

🔹 4.1 – Calcul du point d’intersection
c
Copier
Modifier
hit_point = ray.origin + t * ray.direction;
🔹 4.2 – Calcul de la normale à la surface
Pour une sphère :

c
Copier
Modifier
normal = normalize(hit_point - sphere->center);
🔹 4.3 – Calcul de la lumière (modèle de Lambert)
c
Copier
Modifier
light_dir = normalize(light->position - hit_point);
diffuse = max(0, dot(normal, light_dir));
🔹 4.4 – Ombres (facultatif au début)
Tu peux relancer un rayon shadow_ray depuis hit_point vers la lumière

S’il touche un autre objet avant la lumière ➜ le point est dans l’ombre

✅ 5. Calcul de la couleur finale
c
Copier
Modifier
final_color = ambient + (diffuse * object_color);
Tu peux d’abord commencer avec un éclairage ambiant uniquement, puis ajouter la lumière directe et les ombres après.

🧱 Plan clair et concret (ordre à suivre) :
✅ generate_ray() pour chaque pixel

✅ intersect_sphere() (et autres plus tard)

✅ trace_ray() → retourne une couleur uint32_t

✅ put_pixel()

🖼️ render() → appelle tout ça et affiche l’image

