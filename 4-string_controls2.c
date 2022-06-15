#include "shell.h"

/**
 * _strtok - tokenizes strings at delimiter
 * @str: input string
 * @delim: delimiter
 * Return: pointer to start of string
 */

char *_strtok(char *str, char *delim)
{
	static char *lastptr;
	char ch;

	if (str == NULL)
	{
		str = lastptr;
	}
	do {
		ch = *str++;
		if (!ch)
		{
			return (NULL);
		}
	} while (_strchr(delim, ch));
	str--;
	lastptr = str + _strcspn(str, delim);
	if (*lastptr)
	{
		*lastptr++ = 0;
	}
	return (str);
}

/**
 * _strcspn - returns first occurence of any char in
 * second string in first string
 * @string: input string to search
 * @chars: input chars to check
 * Return: pointer to first match
 */
int _strcspn(char *string, char *chars)
{
	char ch;
	char *ptr, *_str;

	for (_str = string, ch = *_str; ch; _str++, ch = *_str)
	{
		for (ptr = chars; *ptr; ptr++)
		{
			if (ch == *ptr)
			{
				return (_str - string);
			}
		}
	}

	return (_str - string);
}

/**
 * _strchr - locates a character in a string
 * @s: string to be searched
 * @c: target char
 * Return: pointer to first occurrence of c or
 * NULL if char not found
 */
char *_strchr(char *s, char c)
{
	char x;

	while (true)
	{
		x = *s++;
		if (x == c)
		{
			return (s - 1);
		}
		if (!x)
		{
			return (NULL);
		}
	}
}
#include "holberton.h"

/**
 * find_built_ins - validates if command is builtin and executes
 * @build: input build
 *
 * Description: uses build  functions to validate user commands
 * Return: true if found, false if not
 */
_Bool find_built_ins(config *build)
{
	register int i = 0;

	type_b get_built_ins[] = {
		{"exit", exit_function},
		{"env", env_function},
		{"history", history_function},
		{"alias", alias_function},
		{"cd", implement_cd},
		{"setenv", set_env_func},
		{"unsetenv", unset_env_func},
		{"help", help_function},
		{NULL, NULL}};

	while (get_built_ins[i].command)
	{
		if (_strcmp(build->args[0], get_built_ins[i].command) == 0)
		{
			get_built_ins[i].func(build);
			free_args_and_buffer(build);
			return (true);
		}
		i++;
	}
	return (false);
}

/**
 * exit_function - exits the application
 * @build: input build
 * Return: 1 on success, 0 on failure
 */
int exit_function(config *build)
{
	register int arg_count, exit_status;

	arg_count = count_args(build->args);
	if (arg_count == 1)
	{
		free_member(build);
		if (build->error_status)
		{
			exit(build->error_status);
		}
		exit(EXIT_SUCCESS);
	}
	else if (arg_count > 1)
	{
		exit_status = _atoi(build->args[1]);
		if (exit_status == -1)
		{
			errno = EILLEGAL;
			build->error_status = 2;
			handle_errors(build);
			return (0);
		}
		free_member(build);
		exit(exit_status);
	}
	return (1);
}

/**
 * history_function - displays command history
 * @build: input build
 * Return: 1 on success, 0 on failure
 */
int history_function(config *build)
{
	char *str = "Currently in development\n";

	(void)build;
	write(STDOUT_FILENO, str, _strlen(str));
	return (1);
}

/**
 * alias_function - displays local aliases
 * @build: input build
 * Return: 1 on success, 0 on failure
 */
int alias_function(config *build)
{
	char *str = "Currently in development\n";

	(void)build;
	write(STDOUT_FILENO, str, _strlen(str));
	return (1);
}

