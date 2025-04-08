/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 16:30:25 by olthorel          #+#    #+#             */
/*   Updated: 2025/04/08 13:34:02 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static t_program	*init_program(char **av)
{
	t_program	*program;

	program = NULL;
	program = ft_calloc(1, sizeof(t_program));
	if (!program)
		return (ft_print_error(3), NULL);
	program->file = parse_input(av[1]);
	if (!program->file)
	{
		ft_free((void **)&program);
		return (NULL);
	}
	return (program);
}

static int	init_mlx(t_program *program)
{
	program->mlx = mlx_init();
	if (!program->mlx)
		return (ft_print_error(3), free(program), 0);
	program->win = mlx_new_window(program->mlx, WIDTH, HEIGHT, NAME_WINDOWS);
	if (!program->win)
	{
		ft_print_error(5);
		mlx_destroy_display(program->mlx);
		free(program->mlx);
		free(program);
		return (0);
	}
	return (1);
}

static int	is_valid_extension(char *filename)
{
	char	*ext;

	ext = ft_strrchr(filename, '.');
	if (!ext || ft_strlen(ext) != 3 || ft_strncmp(ext, ".rt", 4) != 0)
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_program	*program;

	if (ac != 2)
		return (ft_print_error(1), 1);
	if (!is_valid_extension(av[1]))
		return (ft_print_error(9), 1);
	program = init_program(av);
	if (!program)
		return (1);
	if (!init_mlx(program))
		return (1);
	render(program);
	mlx_hook(program->win, 17, 0, ft_close_windows, program);
	mlx_key_hook(program->win, ft_key_hook, program);
	mlx_loop(program->mlx);
	return (0);
}
