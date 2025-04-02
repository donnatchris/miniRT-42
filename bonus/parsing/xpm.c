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
	// printf("Pixel address: %p\n", pixel);
	return (*(unsigned int *)pixel);
}
