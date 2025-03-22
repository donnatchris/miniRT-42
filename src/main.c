#include "../includes/miniRT.h"

// int	main(int ac, char **av)
// {
// 	(void)av;
// 	(void)ac;
// 	t_program	*program;

// 	program = ft_calloc(1, sizeof(t_program));
// 	if (!program)
// 		return (perror("malloc failed"), 1);
// 	// ft_memset(program->file, 0, sizeof(program->file));
// 	program->file = parse_input(av[1]);
// 	if (!program->file)
// 		return (ft_putstr_fd("Invalid input\n", 2), ft_free((void **)&program), 1);
// 	print_file(program->file);
// 	program->mlx = mlx_init();
// 	program->win = mlx_new_window(program->mlx, WIDTH, HEIGHT, NAME_WINDOWS);
// 	if (!program->mlx)
// 	{
// 		ft_print_error(3);
// 		return (free(program), 1);
// 	}
// 	if (!program->win)
// 	{
// 		ft_print_error(5);
// 		mlx_destroy_display(program->mlx);
// 		free(program->mlx);
// 		free(program);
// 		return (1);
// 	}
// 	mlx_hook(program->win, 17, 0, ft_close_windows, program);
// 	mlx_key_hook(program->win, ft_key_hook, program);
// 	mlx_loop(program->mlx);
// 	return (0);
// }
