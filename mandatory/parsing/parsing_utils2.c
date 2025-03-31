/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 10:13:35 by christophed       #+#    #+#             */
/*   Updated: 2025/03/31 10:25:56 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

// Function to check if the input file can be opened and read
// Returns 0 if the file can be opened and read
// Returns 1 if an error occured
int	check_input_file(char *input)
{
	int		fd;
	int		byte_read;
	int		ret;
	char	buff[1];

	fd = open(input, O_RDONLY);
	if (fd == -1)
		return (perror("Error\nOpening file"), 1);
	ret = 0;
	byte_read = read(fd, buff, 1);
	if (byte_read == -1)
	{
		perror("Error\nReading file");
		ret = 1;
	}
	if (close(fd) == -1)
		return (perror("Error\nClosing file"), 1);
	return (ret);
}

// Function to find the next argument in a string
// Returns the next argument in the string
// Returns NULL if there is no argument
char	*next_arg(char *line, size_t *start)
{
	char	*arg;
	int		end;

	if (line[*start] == '\0' || line[*start] == '\n')
		return (NULL);
	arg = NULL;
	while (ft_strchr(WHITESPACE, line[*start]))
		(*start)++;
	if (line[*start] == '\0' || line[*start] == '\n')
		return (NULL);
	end = *start + 1;
	while (!ft_strchr(WHITESPACE, line[end])
		&& line[end] != '\0' && line[end] != '\n')
		end++;
	arg = ft_substr(line, *start, end - *start);
	return (arg);
}

// Function to find the next argument in a string
// and advance the start index
// Returns the next argument in the string
// Returns NULL if there is no argument
char	*next_and_advance(char *line, size_t *start, char *old_arg)
{
	if (old_arg)
	{
		*start += ft_strlen(old_arg) + 1;
		ft_free((void **)&old_arg);
	}
	return (next_arg(line, start));
}

// Function to print an error message while parsing
// Returns 1
int	pars_err_msg(char *msg, char *line)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(" in line: ", 2);
	ft_putstr_fd(line, 2);
	return (1);
}
