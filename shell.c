#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "main.h"

/**
 * main - entry to the program
 * Return: 0 for success and -1 for failure
 */
int main(void)
{
	cmd_data data;
	int pl;

	_resetMemory((void *)&data, 0, sizeof(data));
	signal(SIGINT, signal_handler);
	while (1)
	{
		data.index++;
		/* Read user input */
		while (readInput(&data) >= 0)
		{
			/* Split the input into separate arguments */
			while (split_line(&data) >= 0)
			{
				/* Parse the cmd line and check for errors */
				pl = parse_line(&data);
				if (pl == 0)
				{
					free_data(&data);
					break;
				}
				if (pl < 0)
				{
					print_error(&data);
					continue;
				}
				/* Process the command and execute it */
				if (process_cmd(&data) < 0)
				{
					print_error(&data);
					break;
				}
				free_data(&data);
			}
		}
		if (isatty(STDIN_FILENO))
			_print("\n");
		break; }
	free_data(&data);
	return (0);
}

/**
 * readInput - Reads user input and stores data in 'data'
 * @data: Memory location of our storage container
 * Return: 0 if success and -1 if error
 */
int readInput(cmd_data *data)
{
	char *csr_ptr, *end_ptr, c;
	size_t size = BUFSIZE, read_st, length, new_size;

	data->line = malloc(size * sizeof(char));
	if (data->line == NULL)
		return (-1);

	if (isatty(STDIN_FILENO))
		_print(PROMPT);

	for (csr_ptr = data->line, end_ptr = data->line + size;;)
	{
		read_st = read(STDIN_FILENO, &c, 1);
		if (read_st == 0)
			return (-1);

		*csr_ptr++ = c;

		if (c == '\n')
		{
			*csr_ptr = '\0';
			return (0);
		}

		if (csr_ptr + 2 >= end_ptr)
		{
			new_size = size * 2;
			length = csr_ptr - data->line;
			data->line = _realloc(data->line, size * sizeof(char),
					new_size * sizeof(char));
			if (data->line == NULL)
				return (-1);

			size = new_size;
			end_ptr = data->line + size;
			csr_ptr = data->line + length;
		}
	}
}

/**
 * process_cmd - Process command and execute process
 * @data: Pointer to the struct of data
 *
 * Return: (Success) a positive number
 * ------- (Fail) a negative number
 */
int process_cmd(cmd_data *data)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);

		/* Execute the command */
		if (execve(data->cmd, data->args, environ) < 0)
		{
			data->error_msg = _strdup("not found\n");
			return (-1);
		}
	}
	else
	{
		/* Wait for the child process to finish */
		waitpid(pid, &status, WUNTRACED);
	}
	return (0);
}
