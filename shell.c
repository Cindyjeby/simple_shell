#include "shell.h"

/**
 * main - entry to the program
 * Return: 0 for success and -1 for failure
 */
int main(void)
{
	command_data d;
	int pl;

	memory_reset((void *)&d, 0, sizeof(d));
	signal(SIGINT, signal_handler);
	while (1)
	{
		data.index++;
		/* Read user input */
		while (readInput(&d) >= 0)
		{
			/* Split the input into separate arguments */
			while (split_line(&d) >= 0)
			{
				/* Parse the cmd line and check for errors */
				pl = parse_line(&d);
				if (pl == 0)
				{
					free_data(&d);
					break;
				}
				if (pl < 0)
				{
					print_error(&d);
					continue;
				}
				/* Process the command and execute it */
				if (process_command(&d) < 0)
				{
					print_error(&d);
					break;
				}
				free_data(&d);
			}
		}
		if (isatty(STDIN_FILENO))
			print_out("\n");
		break; }
	free_data(&d);
	return (0);
}

/**
 * readInput - Reads user input and stores data in 'data'
 * @d: Memory location of our storage container
 * Return: 0 if success and -1 if error
 */
int readInput(command_data *d)
{
	char *csr_ptr, *end_ptr, c;
	size_t size = BUFSIZE, read_st, length, new_size;

	d->line = malloc(size * sizeof(char));
	if (d->line == NULL)
		return (-1);

	if (isatty(STDIN_FILENO))
		print_out(PROMPT);

	for (csr_ptr = d->line, end_ptr = d->line + size;;)
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
			length = csr_ptr - d->line;
			d->line = memory_resize(d->line, size * sizeof(char),
					new_size * sizeof(char));
			if (d->line == NULL)
				return (-1);

			size = new_size;
			end_ptr = d->line + size;
			csr_ptr = d->line + length;
		}
	}
}

/**
 * process_command - Process command and execute process
 * @d: Pointer to the struct of data
 * Return: (Success) a positive number
 * (Fail) a negative number
 */
int process_command(command_data *d)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);

		/* Execute the command */
		if (execve(d->command, d->args, environ) < 0)
		{
			d->error_msg = string_dup("not found\n");
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
