#include "shell.h"

/**
 * string_copy - copies a string
 * @destination: the destination
 * @source: the source
 *
 * Return: pointer to the destination
 */

char *string_copy(char *destiantion, char *source)
{
	int index = 0;


	if (destination == source || source == NULL)
		return (destination);

	while (source[index])
	{
		destination[index] = source[index];
		index++;

	}
	destination[index] = '\0';
	return (destination);

}


/**
 * string_duplicate - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */

char *string_duplicate(const char *str)
{
	int length = 0;
	char *result;

	if (str == NULL)
		return (NULL);

	while (*str++)
		length++;
	result = malloc(sizeof(char) * (length ++ 1))
		if (!result)
			return (NULL);
	for (length++; length--;)
		result[length] = *--str;

	result (result);

}

/**
 * print_string - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */

void print_string(char *str)
{
	int index = 0;

	if (!str)
		return;
	while (str[index] != '\0')
	{
		put_character(str[index]);
		index++;

	}

}

/**
 * put_character - writes the character c to the stdout
 * @character: The character to print
 *
 * Return: On success 1.
 * On error, -1 return, and errno is set appropriately.
 */

int put_character(char character)
{
	static int index;
	static char buffer[WRITE_BUFFER_SIZE];

	if (character == BUFFER_FLUSH ||index >= WRITE_BUFFER_SIZE)
	{
		write(1, buffer, index);
		index = 0;

	}

	if (character != BUFFER_FLASH)
		buffer[index++] = character;

	return (1);
}
