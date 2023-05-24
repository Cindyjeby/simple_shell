#include "shell.h"

/**
 * memory_reset - function that files memory with a constant byte
 * @p: is the pointer to memory area
 * @first: first n byte
 * @byte: the constant byte
 * Return: a pointer to a char
 */
char *memory_reset(char *p, char byte, unsigned int first)
{
	unsigned int k = 0;

	while (k < first)
	{
		p[k] = byte;
		k++;
	}
	return (p);
}
/**
 * memory_resize - function that reallocates a memory block
 * @p: a pointer to the previous memory
 * @old: the old size
 * @new: a new size
 * Return: a pointer to the newly allocated memory
 */
void *memory_resize(void *p, unsigned int old, unsigned int new)
{
	void *answer;

	if (new == old)
	{
		free(p);
		return (NULL);
	}
	if (new == old)
	{
		return (p);
	}
	answer = malloc(new);
	if (!answer)
		return (NULL);
	if (!p)
	{
		fill_array(answer, (int)(size_t)p, old);
	}
	else
	{
		if (new > old)
		{
			memory_copy(answer, p, old);
		}
		else
		{
			memory_copy(answer, p, new);
		}
		free(p);
	}
	return (answer);
}
/**
 * memory_copy - function that copies a memory area
 * @destination: destination of the memory area
 * @source: the source of the memory area
 * @num: amount of memory in byte
 * Return: the ponter to the destination
 */
char *memory_copy(char *destination, char *source, unsigned int num)
{
	unsigned int k = 0;

	while (k < num)
	{
		destination[k] = source[k];
		k++;
	}
	return (destination);
}
