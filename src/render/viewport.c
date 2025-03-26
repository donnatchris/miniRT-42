#include "../includes/miniRT.h"

t_viewport	viewport(t_program *prog)
{
	t_viewport	view;
	t_vector	horizontal;
	t_vector	vertical;

	view.asp_ratio = (double) WIDTH / HEIGHT;
	view.fov = DEG_TO_RAD(prog->file->camera.fov);
	view.height = 2.0 * tan(view.fov / 2.0);
	view.width = view.height * view.asp_ratio;
	view.world_up = vector(0, 1, 0);
	view.forward = prog->file->camera.direction;
	normalize_vector(&view.forward);
	view.right = cross_vector(view.forward, view.world_up);
	normalize_vector(&view.right);
	view.up = cross_vector(view.right, view.forward);
	normalize_vector(&view.up);
	horizontal = mul_vector(view.right, view.width);
	vertical = mul_vector(view.up, view.height);

	// Correction : Bien positionner l'origine du viewport
	// view.origin = prog->file->camera.origin;
	view.origin = sub_vector(add_vector(prog->file->camera.origin, view.forward),
		add_vector(mul_vector(view.right, 0.5 * view.width), mul_vector(view.up, 0.5 * view.height)));

	return (view);
}

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
	if (r < 0) r = 0;
	if (g < 0) g = 0;
	if (b < 0) b = 0;

	return ((r << 16) | (g << 8) | b);
}

int	mix_color(int color1, int color2, double factor)
{
	int	r, g, b;

	// Clamp le facteur entre 0 et 1
	if (factor < 0) factor = 0;
	if (factor > 1) factor = 1;

	// Extraction des composants RGB
	int r1 = (color1 >> 16) & 0xFF;
	int g1 = (color1 >> 8) & 0xFF;
	int b1 = color1 & 0xFF;

	int r2 = (color2 >> 16) & 0xFF;
	int g2 = (color2 >> 8) & 0xFF;
	int b2 = color2 & 0xFF;

	// Mélange des couleurs selon le facteur
	r = (int)(r1 * (1 - factor) + r2 * factor);
	g = (int)(g1 * (1 - factor) + g2 * factor);
	b = (int)(b1 * (1 - factor) + b2 * factor);

	// Reconstruction de la couleur
	return ((r << 16) | (g << 8) | b);
}

int	phong_lighting(t_hit hit, t_light light, t_program *prog)
{
	t_vector	light_dir;
	t_vector	reflect_dir;
	t_vector	view_dir;
	double		diffuse;
	double		specular;
	double		intensity;
	double		shininess;
	int			r, g, b;

	shininess = 32; //brillance specular
	//vecteur lumere normalise
	light_dir = sub_vector(light.position, hit.point);
	normalize_vector(&light_dir);
	//diffuse Lambert
	diffuse = dot_vector(hit.normal, light_dir);
	if (diffuse < 0)
		diffuse = 0;
	//specular Phong
	reflect_dir = sub_vector(mul_vector(hit.normal, 2 * dot_vector(hit.normal, light_dir)), light_dir);
    normalize_vector(&reflect_dir);
    view_dir = sub_vector(prog->view->origin, hit.point);
    normalize_vector(&view_dir);
    specular = pow(fmax(dot_vector(reflect_dir, view_dir), 0.0), shininess);
	//intensite finale
	intensity = (light.ratio * diffuse) + (0.5 * specular);
    if (intensity > 1)
	{
        intensity = 1;
	}
	//application couleur
	r = ((hit.color >> 16) & 0xFF) * ((light.color >> 16) & 0xFF) / 255 * intensity;
    g = ((hit.color >> 8) & 0xFF) * ((light.color >> 8) & 0xFF) / 255 * intensity;
    b = (hit.color & 0xFF) * (light.color & 0xFF) / 255 * intensity;
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
				if (shadow.hit)
					color = scale_color(prog->file->ambient_light.color, prog->file->ambient_light.ratio);
				else
					color = phong_lighting(hit, prog->file->light, prog);
				// int diffuse = lambert_color(hit, prog->file->light);
				// int ambient = scale_color(prog->file->ambient_light.color, prog->file->ambient_light.ratio);
				//color = add_colors(ambient, diffuse);
			}
			*(int *)(prog->img->addr + ((x + (y * WIDTH)) * (prog->img->bpp / 8))) = color;
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(prog->mlx, prog->win, prog->img->img_ptr, 0, 0);
}
