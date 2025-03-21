#include "../includes/miniRT.h"

void    ft_free(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
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
		ft_free(array[i]);
		i++;
	}
	ft_free(array);
}
