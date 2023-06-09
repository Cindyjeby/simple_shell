#include "shell.h"

/**
 * fill_array - fill an array with elements
 * @array: the given array
 * @element: the given element
 * @length: the length of the array
 * Return: pointer to filled array
 */
void *fill_array(void *array, int element, unsigned int length)
{

	char *ptr = array;
	unsigned int i;

	for (i = 0; i < length; i++)
	{
		*ptr = element;
		ptr++;
	}
	return (array);
}
