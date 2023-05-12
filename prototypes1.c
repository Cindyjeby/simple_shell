#include "main.h"

#define DELIMITER " \n\t\r\a\v"

/**
 * split_line - splits line to tokens
 * @data: a pointer to the struct of data
 *
 * Return: on success - a positive number
 *         on failure - a negative number
 */
int split_line(cmd_data *data)
{
    char *tkn;
    size_t sz = TOKENSIZE, new_sz, i = 0;

    if (_strcmp(data->line, "\n") == 0)
        return (-1);
    data->arguments = malloc(sz * sizeof(char *));
    if (data->arguments == NULL)
        return (-1);
    tkn = strtok(data->line, DELIMITER);
    while (tkn != NULL)
    {
        data->arguments[i++] = tkn;
        if (i + 2 >= sz)
        {
            new_sz = sz * 2;
            data->arguments = _realloc(data->arguments, sz * sizeof(char *),
                                  new_sz * sizeof(char *));
            if (data->arguments == NULL)
                return (-1);
            sz = new_sz;
        }
        tkn = strtok(NULL, DELIMITER);
    }
    data->arguments[i] = NULL;
    return (0);
}

#undef DELIMITER

/**
 * free_data - frees data
 * @data: the data structure
 *
 * Return: on success - positive number
 *         on failure - negative number
 */
int free_data(cmd_data *data)
{
    free(data->line);
    data->line = NULL;
    free(data->arguments);
    data->arguments = NULL;
    free(data->command);
    data->command = NULL;
    free(data->error_msg);
    data->error_msg = NULL;
    return (0);
}

#define DELIMITER ":"

/**
 * parse_line - parses arguments to valid command
 * @data: a pointer to the struct of data
 *
 * Return: on success - a positive number
 *         on failure - a negative number
 */
int parse_line(cmd_data *data)
{
    while (is_path_form(data) > 0)
        return (1);

    while (is_builtin(data) > 0)
    {
        if (handle_builtin(data) < 0)
            return (-1);
        return (0);
    }

    is_short_form(data);
    return (1);
}

#undef DELIMITER

/**
 * _strcat - concatenates two strings in a path form
 * @first: the first given destination
 * @second: the second given source
 *
 * Return: (Success) the newly concatenated string
 *         (Fail) if it fails
 */
char *_strcat(char *first, char *second)
{
    int len1, len2, i = 0, j = 0;
    char *result;

    len1 = _strlen(first);
    len2 = _strlen(second);
    result = malloc((len1 + len2 + 2) * sizeof(char));
    if (!result)
        return (NULL);
    *result = '\0';
    while (first[j])
        result[i++] = first[j++];
    result[i++] = '/';
    j = 0;
    while (second[j])
        result[i++] = second[j++];
    result[i] = '\0';
    return (result);
}

/**
 * _strchr - locates a character in a given string
 * @str: the given string
 * @c: the character
 *
 * Return: on success - a pointer to the first occurrence of c
 *         on failure - a null pointer
 */
char *_strchr(char *str, char c)
{
    char *ptr;

    if (str == NULL)
        return NULL;
    ptr = str;
    while (*ptr)
    {
        if (*ptr == c)
            return ptr;
        ptr++;
    }
    return (NULL);
}

