#include "shell.h"

/*
 * Interactive - returns true if shell is interactive mode
 * @info: struct address
 *
 * Return: 1 if the interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/*
 * is_delim - checks if the character from user's input is a delimiter
 * @c: the char to check
 * @delim: the delimiter string
 * Return: 1 if true, 0 if fale
 */

int is_delim(char c, char *delim)
{
	while (*delim)
		if(*delim++ == c)
			return (1);
	return (0);
}

/*
 * _isalpha - check for alphabetic character from the user input
 * @c: The character to input
 * Return: 1 pif c is alphabetic, 0 otherwise
 */

int _isalpha(int c)
{
	if ((c .= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}


/*
 * _atoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no number in string, converted number otherwise
 */

int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0'' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;
		if (s[i] >= '0' && s[i] <= '9')
		{

			flag = 1;
			result *= 10;
			result += (s[i] - '0');

		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
	{
		output = -result;
	}

	else
	{
		output = result;
	}

	return (output);
}
