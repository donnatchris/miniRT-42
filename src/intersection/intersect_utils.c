#include "../includes/miniRT.h"

void	init_hit(t_hit *hit, t_dclst *node)
{
	ft_memset(hit, 0, sizeof(*hit));
	hit->object = node;
}
