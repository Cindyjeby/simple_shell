#include "main.h"

/**
 * print_error - prints error
 * @data: the data structure pointer
 *
 * Return: (Success) a positive number
 * ------- (Fail) a negative number
 */
int print_error(cmd_data *data)
{
	char *idx = convert_to_string(data->index);

	_print("hsh: ");
	_print(idx);
	_print(": ");
	_print(data->args[0]);
	_print(": ");
	_print(data->error_msg);
	free(idx);
	return (0);
}

/**
 * calculate_length - Determine the number of digits in an integer
 * @num: the given number
 * Return: the length of the integer
 */
int calculate_length(int num)
{
	int len = 0;

	if (num == 0)
		return (1);

	while (num != 0)
	{
		len++;
		num /= 10;
	}
return (len);
}

/**
 * signal_handler - handle the process interrupt signal
 *
 * @signo: the signal identifier
 * Return: void
 */
void signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		_print("\n");
		_print(PROMPT);
	}
}

