#include "shell.h"

/**
 * string_length - function that calculates the length of a given string
 * @str: the string to be calculated
 * Return: the length of the string or -1 (failure)
 */
int string_length(char *str)
{
	int length = 0;

	while (str[length] != '\0')
	{
		length++;
	}
	return (length);
}
/**
 * print_out - function that prints a string to stdout
 * @outputstr: string to be printed
 * Return: 0 (sucess) -1 (failure)
 */
void print_out(char *outputstr, ...)
{
	int length = 0;

	while (outputstr[length] != '\0')
	{
		length++;
	}

	write(STDOUT_FILENO, outputstr, length);
}
/**
 * string_dup - function that duplicates a given string
 * @str: string
 * Return: the address of the given string or NULL
 */
char *string_dup(char *str)
{
	char *dup;
	int length, k;

	if (!str)
		return (NULL);

	length = string_length(str);
	dup = malloc(length + 1);

	if (!dup)
		return (NULL);

	for (k = 0; k < length; k++)
	{
		dup[k] = str[k];
	}
	dup[k] = '\0';
	return (dup);
}
/**
 * reverse_array - function that reverses array
 * @array: the given array
 * @length: lenght of the array
 * Return: void
 */
void reverse_array(char *array, int length)
{
	int k = 0;
	int j = length - 1;
	char rev;

	while (k < j)
	{
		rev = array[k];
		array[k] = array[j];
		array[j] = rev;
		k++;
		j--;
	}
}
/**
 * string_copy - function that copies a string
 * @source: the source of the stirng
 * @destination: destination of the string
 * Return: pointer to the destination
 */
char *string_copy(char *destination, char *source)
{
	int k = 0;

	while (source[k] != '\0')
	{
		destination[k] = source[k];
		k++;
	}
	destination[k] = '\0';
	return (destination);
}
