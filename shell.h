#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>

#define BUFSIZE (256)
#define PROMPT "#cisfun$ "
#define TOKENSIZE 64

/**
 * struct data_struct - a custom  data structure to store command details
 * @old: previous working directory
 * @command: actual command
 * @index: index of the command run by shell
 * @args: the arguments of the command
 * @env: the environment
 * @line: is the address of the input data
 * @error_msg: stores the error messages
 * Description: contains all the variables needed to manage the program
 * ,accessability and memory
 */
typedef struct data_struct
{
	char *old;
	char *command;
	unsigned long int index;
	char **arguments;
	char *env;
	char *line;
	char *error_msg;
} command_data;

/**
 * struct builtin - used to manage the builtin functions
 * @command: the command line on the string form
 * @handle: the function
 * Description: struct made to manage builtin commands
 */
typedef struct builtin
{
	char *command;
	int (*handle)(command_data *d);
} builtin_t;

extern char **environ;

int string_length(char *str);
void print_out(char *outputstr, ...);
char *string_dup(char *str);
void reverse_array(char *array, int length);
char *string_copy(char *destination, char *source);
char *memory_reset(char *p, char byte, unsigned int first);
void *memory_resize(void *ptr, unsigned int old, unsigned int new);
char *memory_copy(char *destination, char *source, unsigned int num);
int _pathfinder(command_data *d);
void _short(command_data *d);
int _bultin(command_data *d);
int string_integer(char *cha);
int builtin_handler(command_data *d);
int help_displayer(command_data *d);
int program_abort(command_data *d __attribute__((unused)));
int directory_changer(command_data *d);

void *fill_array(void *array, int element, unsigned int length);
<<<<<<< HEAD:main.h
int split_line(command_data *data);
int free_data(command_data *data);
int parse_line(command_data *data);
=======
int split_line(command_data *d);
int free_data(command_data *d);
int parse_line(command_data *d);
>>>>>>> bc021ea058083abfa0e2980919e58e173c9d034c:shell.h
char *_strcat(char *first, char *second);
char *_strchr(char *str, char c);
int _strcmp(char *s1, char *s2);
int compare_string(char *string1, char *string2);
char *get_environment_variables(char *variable_name);
<<<<<<< HEAD:main.h
void increment_index(command_data *data);
int write_to_history(command_data *data __attribute__((unused)));
int is_alphabetic(int character);
int main(void);
int readInput(command_data *data);
int process_cmd(command_data *data);

int handle_builtin(command_data *data);
int is_builtin(command_data *data);
void is_short_form(command_data *data);
int is_path_form(command_data *data);
=======
void increment_index(command_data *d);
int write_to_history(command_data *d __attribute__((unused)));
int is_alphabetic(int character);
int main(void);
int readInput(command_data *d);
<<<<<<< HEAD
int process_cmd(command_data *d);
>>>>>>> bc021ea058083abfa0e2980919e58e173c9d034c:shell.h
=======
int process_command(command_data *d);
void signal_handler(int signo);
int print_error(command_data *d);
>>>>>>> 0f3cf1153355bd967a8ba385a86910daffb6ad71

#endif
