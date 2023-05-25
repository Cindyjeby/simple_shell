#include "shell.h"
/**
 * _pathfinder - checks if the given filename is a path
 * @d: pointer to struct data
 * Return: (success) or (failure)
 */
int _pathfinder(command_data *d)
{
	if (_strchr(d->arguments[0], '/') != NULL)
	{
		d->command = string_dup(d->arguments[0]);
		return (1);
	}
	return (-1);
}
#define DELIMITER ":"
/**
 * _short - function that checks if the given filename is in short form
 * @d: pointer to struct data
 * Return: (success) or (failure)
 */
void _short(command_data *d)
{
	char *start, *ticket, *end;
	int exit = 0;

	start = get_environment_variables("PATH");
	end = string_dup(start);
	ticket = strtok(end, DELIMITER);

	while (ticket)
	{
		if (compare_string(ticket, d->arguments[0]) == 0)
		{
			exit = 1;
			break;
		}
		free(ticket);
		ticket = strtok(NULL, DELIMITER);
	}
	if (!exit)
	{
		d->command = string_dup(d->arguments[0]);
	}
	free(end);
}
#undef DELIMITER
/**
 * _builtin - function that checks if the command is builtin
 * @d: is a pointer to the data structure
 * Return: 0 (success) -1 (failure)
 */
int _builtin(command_data *d)
{
	char *builtins[] = {
		"exit",
		"cd",
		"help",
		NULL
	};
	int k = 0;

	while (builtins[k] != NULL)
	{
		if (compare_string(d->arguments[0], builtins[k]) == 0)
			return (1);
		k++;
	}
	return (0);
}
/**
 * string_integer - function that converts chars to ints
 * @cha: the char to be changed
 * Return: an interger
 */
int string_integer(char *cha)
{
	int value = 0;
	int sign = 1;
	int k;

	if (!cha)
		return (0);

	for (k = 0; cha[k] != '\0'; k++)
	{
		if (cha[k] == '-')
		{
			sign *= -1;
		}
		else if (cha[k] >= '0' && cha[k] <= '9')
		{
			value = (value * 10) + (cha[k] - '0');
		}
		else
		{
			break;
		}
	}
		return (sign * value);
}
