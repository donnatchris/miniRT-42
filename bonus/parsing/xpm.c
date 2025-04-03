#include "../../includes/miniRT_bonus.h"

void	*xpm_error(char *file)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd("Unable to create image from file: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd("\n", 2);
	return (NULL);
}

t_xpm	*store_xpm(t_program *prog, char *file)
{
	t_xpm	*xpm;

	if (!file)
		return (NULL);
	printf("Loading XPM file: %s\n", file);
	xpm = (t_xpm *) malloc(sizeof(t_xpm));
	if (!xpm)
		return (perror("Error\nXPM Malloc failed"), NULL);
	ft_memset(xpm, 0, sizeof(t_xpm));
	xpm->mlx = prog->mlx;
	xpm->img_ptr = mlx_xpm_file_to_image(
		xpm->mlx,
		file,
		&xpm->width,
		&xpm->height);
	if (!xpm->img_ptr)
		return (free(xpm), xpm_error(file));
	xpm->addr = mlx_get_data_addr(
		xpm->img_ptr,
		&xpm->bpp,
		&xpm->line_len,
		&xpm->endian);
	if (!xpm->addr)
	{
		mlx_destroy_image(xpm->mlx, xpm->img_ptr);
		free(xpm);
		return (xpm_error(file));
	}
	printf("addr: %p, bpp: %d, line_len: %d, endian: %d\n",
		xpm->addr, xpm->bpp, xpm->line_len, xpm->endian);
	printf("XPM file loaded successfully\n");
	return (xpm);
}


void	delete_xpm(t_xpm *xpm)
{
	if (!xpm)
		return ;
	if (xpm->img_ptr)
		mlx_destroy_image(xpm->mlx, xpm->img_ptr);
	free(xpm);
}

int	get_xpm_color(t_xpm *xpm, int x, int y)
{
	if (!xpm || x < 0 || x >= xpm->width || y < 0 || y >= xpm->height)
		return (0);
	char *pixel = xpm->addr + (y * xpm->line_len + x * (xpm->bpp / 8));
	return (*(unsigned int *)pixel);
}

int get_gray(t_xpm *xpm, double u, double v)
{
	int		x;
	int		y;
	int		color;
	t_rgb	rgb;

	u = u - floor(u);  // Wrap dans [0,1)
	v = v - floor(v);

	x = (int)(u * xpm->width);
	y = (int)(v * xpm->height);

	color = get_xpm_color(xpm, x, y);
	rgb.r = (color >> 16) & 0xFF;
	rgb.g = (color >> 8) & 0xFF;
	rgb.b = color & 0xFF;

	return ((rgb.r + rgb.g + rgb.b) / 3);  // niveau de gris
}


void apply_bump_map(t_hit *hit, t_plane *plane)
{
	const double	eps = 1.0 / 1024.0;
	t_vector		local;
	double			u, v;
	double			hu, hv, h, du, dv;
	t_vector		tangent_u, tangent_v, perturbed;

	if (!plane->xpm || plane->xpm_scale <= 0)
		return;

	// Coordonnées locales (dans le repère du plan)
	local = sub_vector(hit->point, plane->position);
	u = dot_vector(local, plane->u) / plane->xpm_scale;
	v = dot_vector(local, plane->v) / plane->xpm_scale;

	// Répéter entre 0 et 1
	u = u - floor(u);
	v = v - floor(v);

	// Obtenir la "hauteur" (niveaux de gris)
	h  = get_gray(plane->xpm, u, v) / 255.0;
	hu = get_gray(plane->xpm, u + eps, v) / 255.0;
	hv = get_gray(plane->xpm, u, v + eps) / 255.0;

	// Gradient
	du = (hu - h) / eps;
	dv = (hv - h) / eps;

	// Perturbation de la normale
	tangent_u = mul_vector(plane->u, du);
	tangent_v = mul_vector(plane->v, dv);
	perturbed = sub_vector(sub_vector(hit->normal, tangent_u), tangent_v);
	normalize_vector(&perturbed);

	hit->normal = perturbed;
}
