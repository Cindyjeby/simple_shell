#include "main.h"

/**
 * fill_array - fill an array with elements
 * @array: the given array
 * @element: the given element
 * @length: the length of the array
 *
 * Return: pointer to filled array
 */
void *fill_array(void *array, int element, unsigned int length)
{

	char *ptr = array;

	for (unsigned int i = 0; i < length; i++)
	{
		*ptr = element;
		ptr++;
	}
	return (array);
}

