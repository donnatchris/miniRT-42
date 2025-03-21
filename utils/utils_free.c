#include "../includes/miniRT.h"

// Function to free a pointer and set it to NULL
void    ft_free(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

// Function to free an array of strings and put all its pointers to NULL
void	delete_str_array(char **array)
{
	size_t	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		ft_free((void **)&array[i]);
		i++;
	}
	ft_free((void **)&array);
}

// Function to free the file structure and all of its conponents
// and set all pointers to NULL
void	delete_file(t_file *file)
{
	if (!file)
		return ;
	if (file->obj_list)
		dclst_clear(file->obj_list);
	ft_free((void **)&file);
}

// Function to free the program structure and all of its conponents
// and set all pointers to NULL
void	delete_program(t_program *program)
{
	if (!program)
		return ;
	if (program->win)
		mlx_destroy_window(program->mlx, program->win);
	mlx_destroy_display(program->mlx);
	ft_free((void **)&program->mlx);
	delete_file(program->file);
	ft_free((void **)&program);
}
