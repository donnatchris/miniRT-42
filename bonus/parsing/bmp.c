#include "../../includes/miniRT_bonus.h"

// int open_bmp_file(char *file, char *line)
// {
// 	int		fd;
// 	char	*extension;

// 	if (!file)
// 		return (pars_err_msg("No bmp file", line), -1);
// 	extension = ft_strchr(extension, '.');
// 	if (!extension)
// 		return (pars_err_msg("Invalid bmp file format", line), -1);
// 	if (ft_strncmp(extension, ".bmp") || ft_strlen(extension) != 4)
// 		return (pars_err_msg("Invalid bmp file format", line), -1);
// 	fd = open(file, O_RDONLY);
// 	if (fd == -1)
// 		return (perror("Error\nUnable to read bmp file"), -1);
// 	return (fd);
// }

// int	read_bmp_header(int fd)
// {
// 	unsigned char	header[54];

// }
