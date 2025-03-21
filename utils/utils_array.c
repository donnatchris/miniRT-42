#include "../includes/miniRT.h"

// Function to count the size of an array of strings
// Returns the size of the array or 0 if the array does not exist
size_t	str_array_size(char **array)
{
	size_t	size;

	if (!array)
		return (0);
	size = 0;
	while (array[size])
		size++;
	return (size);
}
