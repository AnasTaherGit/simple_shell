#include "shell.h"

/**
 * free_array - frees an array and its components
 * @array: the array
 * @size: the size of the array
 */

void free_array(char **array, int size)
{
	int i = 0;
	for (i = 0; i < size; i++)
		free(array[i]);
	free(array);
}
