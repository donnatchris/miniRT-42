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

// int read_le_int(unsigned char *p)
// {
//     return ((int)p[0] + (p[1]<<8) + (p[2]<<16) + (p[3]<<24));
// }

// int	read_bmp_header(int fd, char *line)
// {
// 	unsigned char	header[54];
// 	int				bpp;
// 	int				width;
// 	int				height;
// 	int				line_bytes;
// 	int				padding;
// 	int				offset;
// 	if (read(fd, header, 54) == -1)
// 		return (pars_err_msg("Invalid bmp header", line));
// 	if (header[0] != 'B' || header[1] != 'M')
// 		return (pars_err_msg("Invalid bmp header", line));
// 	bpp = header[28] + (header[29] << 8);
// 	if (bpp != 24)
// 		return (pars_err_msg("Invalid bmp bpp", line));
// 	width = read_le_int(&header[18]);
// 	height = read_le_int(&header[22]);
// 	line_bytes = width * 3;
// 	padding = (4 - (line_bytes % 4)) % 4;
// 	offset = read_le_int(&header[10]);
// }
