#include "../includes/miniRT.h"

void    ft_free(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}
