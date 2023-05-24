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
		d->error_msg = string_dup("No Match\n");
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
	print_out("\n");
	return (0);
}
/**
 * program_abort - function that exits the program
 * @d: is a pointer to the data structure
 * Return: 0 (success) or -1 (failure)
 */
int program_abort(command_data *d __attribute__ ((unused)))
{
	int input, k;

	if (!(d->args[1]))
	{
		free_data(d);
		exit(errno);
	}
	for (k = 0; d->args[1][k]; k++)
	{
		if (!is_alphabetic(d->args[1][k]))
		{
			d->error_msg = string_dup("wrong number\n");
			return (-1);
		}
	}
	input = string_integer(d->args[1]);
	free_data(d);
	exit(input);
}
/**
 * directory_changer - function that changes the directory
 * @d: is a pointer to the data
 * Return: 0 (success) or -1 (failure)
 */
int directory_changer(command_data *d)
{
	char *main;
	char *old;

	home = get_environment_variable("MAIN");
	old = NULL;

	if (!(d->args[1]))
	{
		print_out("change current directory to main directory\n");
		if (chdir(main) < 0)
		{
			print_out("failed to change directory\n");
			return (-1);
		}
	}
	else if (compare_string(d->args[1], "-") == 0)
	{
		if (!old)
		{
			print_out("Error: previous directory not set\n");
			return (-1);
		}
		print_out("changing directory to previous directory\n");
		if (chdir(old) < 0)
		{
			print_out("Error: cannot change\n");
			return (-1);
		}
	}
		else
		{
			print_out("changing directory to %s\n", d->args[1]);
			if (chdir(d->args[1]) < 0)
			{
				print_out("Error: changing directory%s\n", d->args[1]);
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

	for (int k = 0; built[k].command != NULL; k++)
	{
		if (compare_string(d->args[0], built[k].command == 0)
				return (built[k].handle(d));
	}
				return (-1);
}
