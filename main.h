#ifndef MAIN_H
#define MAIN_H

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
	char **args;
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

int _strlen(char *str);
void _print(char *outputstr);
char *_strdup(char *str);
void array_rev(char *array, int length);
char *_strcpy(char *destination, char *source);
char *_resetmemory(char *p, char byte, unsigned int first);
void *_realloc(void *ptr, unsigned int old, unsigned int new);
char *_memcpy(char *destination, char *source, unsigned int num);
int _pathfinder(command_data *d);
void _short(command_data *d);
int _bultin(command_data *d);
int _atoi(char *cha);
int builtin_handler(command_data *d);
int help_displayer(command_data *d);
int program_abort(void *d);
int directory_changer(command *d);

void *fill_array(void *array, int element, unsigned int length);
int split_line(command_data *d);
int free_data(command_data *d);
int parse_line(command_data *d);
char *_strcat(char *first, char *second);
char *_strchr(char *str, char c);
int compare_string(char *string1, char *string2);
char *get_environment_variables(char *variable_name);
void increment_index(command_data *d);
int write_to_history(command_data *d __attribute__((unused)));
int is_alphabetic(int character);
int main(void);
int readInput(command_data *d);
int process_cmd(command_data *d);

#endif
