#include "../includes/miniRT.h"

int	ft_close_windows(t_program *program)
{
	// if (program->win)
	// 	mlx_destroy_window(program->mlx, program->win);
	// mlx_destroy_display(program->mlx);
	// free(program->mlx);
	// free(program);
	delete_program(program);
	exit(0);
	return (0);
}

int	ft_key_hook(int keycode, t_program *program)
{
	if (keycode == 65307)
		ft_close_windows(program);
	return (0);
}
