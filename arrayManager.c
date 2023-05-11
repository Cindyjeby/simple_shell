#include "main.h"

/**
 * fill_an_array - fill an array with elements
 * @a: the given array
 * @el: the given element
 * @len: the length of the array
 *
 * Return: pointer to filled array
 */
void *fill_an_array(void *a, int el, unsigned int len)
{
	char *p = (char *)a;
	unsigned int i;

	for (i = 0; i < len; i++)
		p[i] = el;

	return (a);
}
