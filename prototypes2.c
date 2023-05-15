#include "main.h"

/**
 * compare_strings - compare two strings
 * @string1: the first given string
 * @string2: the second given string
 *
 * Return: (Success) a positive number
 *         (Fail) a negative number
 */
int compare_strings(char *string1, char *string2)
{
    int cmp = 0, i;

    if (string1 == NULL || string2 == NULL)
        return (1);
    for (i = 0; string1[i]; i++)
    {
        if (string1[i] != string2[i])
        {
            cmp = string1[i] - string2[i];
            break;
        }
        else
            continue;
    }
    return (cmp);
}

/**
 * get_environment_variable - gets the value of an environment variable
 * @variable_name: the name of the environment variable
 *
 * Return: (Success) a pointer to the value of the variable
 *         (Fail) NULL
 */
char *get_environment_variable(char *variable_name)
{
    char **environment_cursor, *env_ptr, *name_ptr;

    environment_cursor = environ;
    while (*environment_cursor)
    {
        env_ptr = *environment_cursor;
        name_ptr = variable_name;
        while (*env_ptr == *name_ptr)
        {
            if (*env_ptr == '=')
                break;
            env_ptr++;
            name_ptr++;
        }
        if ((*env_ptr == '=') && (*name_ptr == '\0'))
            return (env_ptr + 1);
        environment_cursor++;
    }
    return (NULL);
}

/**
 * increment_index - increment the index
 * @data: a pointer to the data structure
 *
 * Return: void
 */
void increment_index(cmd_data *data)
{
    data->index += 1;
}

/**
 * write_to_history - writes a line to the history file
 * @data: the data structure pointer
 *
 * Return: (Success) 1
 *         (Fail) -1
 */
int write_to_history(cmd_data *data __attribute__((unused)))
{
    char *filename = "history";
    char *line = "this is a line of history";
    ssize_t file_descriptor, write_status;
    int length = 0;

    if (!filename)
        return (-1);
    file_descriptor = open(filename, O_RDWR | O_APPEND);
    if (file_descriptor < 0)
        return (-1);
    if (line)
    {
        while (line[length])
            length++;
        write_status = write(file_descriptor, line, length);
        if (write_status < 0)
            return (-1);
    }
    return (1);
}

/**
 * is_alphabetic - check if the input is a letter r
 * @character: the character to be checked
 *
 * Return: 1 if letter, 0 otherwise
 */
int is_alphabetic(int character)
{
    if ((character >= 65 && character <= 90) || (character >= 97 && character <= 122))
    {
        return (1);
    }
    return (-1);
}

