#include "shell.h"

#define DELIMITER " \n\t\r\a\v"

/**
 * split_line - split line to tokens
 * @d: a pointer to the struct of data
 * Return: on success - a positive number
 *on failure - a negative number
 */
int split_line(command_data *d)
{
	char *tkn;
	size_t sz = TOKENSIZE, new_sz, i = 0;

	if (_strcmp(d->line, "\n") == 0)
		return (-1);
	d->args = malloc(sz * sizeof(char *));
	if (d->args == NULL)
		return (-1);
	tkn = strtok(d->line, DELIMITER);
	while (tkn != NULL)
	{
		d->args[i++] = tkn;
		if (i + 2 >= sz)
		{
			new_sz = sz * 2;
			d->args = _realloc(d->args,
					sz * sizeof(char *), new_sz * sizeof(char *));
			if (d->args == NULL)
				return (-1);
			sz = new_sz;
		}
		tkn = strtok(NULL, DELIMITER);
	}
	d->args[i] = NULL;
	return (0);
}

#undef DELIMITER

/**
 * free_data - frees data
 * @d: the data structure
 * Return: on success - positive number
 * on failure - negative number
 */
int free_data(command_data *d)
{
	free(d->line);
	d->line = NULL;
	free(d->args);
	d->args = NULL;
	free(d->command);
	d->command = NULL;
	free(d->error_msg);
	d->error_msg = NULL;
	return (0);
}

#define DELIMITER ":"

/**
 * parse_line - parses arguments to valid command
 * @d: a pointer to the struct of data
 * Return: on success - a positive number
 * on failure - a negative number
 */
int parse_line(command_data *d)
{
	while (is_path_form(d) > 0)
		return (1);

	while (is_builtin(d) > 0)
	{
		if (handle_builtin(d) < 0)
			return (-1);
		return (0);
	}

	is_short_form(d);
	return (1);
}

#undef DELIMITER

/**
 * _strcat - concatenates two strings in a path form
 * @first: the first given destination
 * @second: the second given source
 * Return: (Success) the newly concatenated string
 * (Fail) if it fails
 */
char *_strcat(char *first, char *second)
{
	int len1, len2, i = 0, j = 0;
	char *result;

	len1 = _strlen(first);
	len2 = _strlen(second);
	result = malloc((len1 + len2 + 2) * sizeof(char));

	if (!result)
		return (NULL);
	*result = '\0';

	while (first[j])
		result[i++] = first[j++];
	result[i++] = '/';
	j = 0;

	while (second[j])
		result[i++] = second[j++];
	result[i] = '\0';
	return (result);
}

/**
 * _strchr - locates a character in a given string
 * @str: the given string
 * @c: the character
 * Return: on success - a pointer to the first occurrence of c
 * on failure - a null pointer
 */
char *_strchr(char *str, char c)
{
	char *ptr;

	if (str == NULL)
		return (NULL);
	ptr = str;
	while (*ptr)
	{
		if (*ptr == c)
			return (ptr);
		ptr++;
	}
	return (NULL);
}
