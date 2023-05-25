#include "shell.h"

/**
 * print_error - prints error message
 * @d: the data structure pointer
 * Return: (Success) a positive number
 *(Fail) a negative number
 */
int print_error(command_data *d);

/**
 * convert_to_string - convert integer to string
 * @num: the given number
 * Return: a pointer to the null-terminated string
 */
char *convert_to_string(unsigned int num);

/**
 * calculate_length - calculate the number of digits in an integer
 * @num: the given number
 * Return: the length of the integer
 */
int calculate_length(int num);

/**
 * signal_handler - handle the process interrupt signal
 * @signo: the signal identifier
 * Return: void
 */
void signal_handler(int signo);

/**
 * print_error - prints error message
 * @d: the data structure pointer
 * Return: (Success) a positive number
 * (Fail) a negative number
 */
int print_error(command_data *d)
{
	char *index_str = convert_to_string(d->index);

	print_out("hsh: ");
	print_out(index_str);
	print_out(": ");
	print_out(d->arguments[0]);
	print_out(": ");
	print_out(d->error_msg);
	free(index_str);
	return (0);
}

/**
 * convert_to_string - convert integer to string
 * @num: the given number
 * Return: a pointer to the null-terminated string
 */
char *convert_to_string(unsigned int num)
{
	int len = calculate_length(num);
	char *str = malloc(len + 1);

	int i;

	if (!str)
		return (NULL);

	str[len] = '\0';
	for (i = len - 1; i >= 0; i--)
	{
		str[i] = (num % 10) + '0';
		num /= 10;
	}
	return (str);
}

/**
 * calculate_length - calculate the number of digits in an integer
 * @num: the given number
 * Return: the length of the integer
 */
int calculate_length(int num)
{
	int length = 0;
	int temp;

	if (num == 0)
		return (1);
	for (temp = num; temp != 0; temp /= 10)
		length++;
	
	return (length);
}

/**
 * signal_handler - handle the process interrupt signal
 * @signo: the signal identifier
 * Return: void
 */
void signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		print_out("\n");
		print_out(PROMPT);
	}
}
