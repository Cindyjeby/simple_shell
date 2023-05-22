#include "shell.h"
/**
 * help_displayer - function used to display the help menu
 * @d: is a pointer to the data structure
 * Return: 0 (success) or negative number (failure)
 */
int help_displayer(command_data *d)
{
	int reading, writting, fd = 1;
	char k;

	fd = open(d->args[1], O_RDONLY);
	if (fd < 0)
	{
		d->error_msg = _strdup("No Match\n");
		return (-1);
	}
	for (reading = read(fd, &k, 1); reading > 0; reading = read(fd, &k, 1))
	{
		writting = write(STDOUT_FILENO, &k, reading);
		if (writting < 0)
		{
			d->error_msg = _strup("permission denied\n");
			return (-1);
		}
	}
	_print("\n");
	return (0);
}
/**
 * program_abort - function that exits the program
 * @d: is a pointer to the data structure
 * Return: 0 (success) or -1 (failure)
 */
int program_abort(void *d)
{
	int input, k;

	if (!(d->args[1]))
	{
		free_data(d);
		exit(errno);
	}
	for (k = 0; d->args[1][k]; k++)
	{
		if (!isalpha(d->args[1][k]))
		{
			d->error_msg = _strdup("wrong number\n");
			return (-1);
		}
	}
	input = _atoi(d->args[1]);
	free_data(d);
	exit(input);
}
/**
 * directory_changer - function that changes the directory
 * @d: is a pointer to the data
 * Return: 0 (success) or -1 (failure)
 */
int directory_changer(command *d)
{
	char *main;
	char *old;

	home = _getenv("MAIN");
	old = NULL;

	if (!(d->args[1]))
	{
		_print("change current directory to main directory\n");
		if (chdir(main) < 0)
		{
			_print("failed to change directory"\n);
			return (-1);
		}
	}
	else if (_strcmp(d->args[1], "-") == 0)
	{
		if (!old)
		{
			_print("Error: previous directory not set\n");
			return (-1);
		}
		_print("changing directory to previous directory\n");
		if (chdir(old) < 0)
		{
			_print("Error: cannot change\n");
			return (-1);
		}
	}
		else
		{
			_print("changing directory to %s\n", d->args[1]);
			if (chdir(d->args[1]) < 0)
			{
				_print("Error: changing directory%s\n", d->args[1]);
				return (-1);
			}
		}
		return (0);
}
/**
 * builtin_handler - function that manages the builtind
 * @d: a pointer to the data structure
 * Return: 0 (success) -1 (failure)
 */
int builtin_handler(command_data *d)
{
	built_t built[] = {
		{"exit", program_abort},
		{"cd", directory_changer},
		{"help", help_displayer},
		{NULL, NULL}
	};

	for (int k = 0; built[k].cmd != NULL; k++)
	{
		if (_strcmp(d->args[0], built[k].cmd == 0)
				return (built[k].handle(d));
	}
				return (-1);
}
