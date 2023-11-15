#include "shell.h"

/**
 * str_length - returns the length of a string
 * @str: the string whose length to check
 *
 * Return: integer length of string
 */

int str_length(char *str)
{
	int length = 0;

	if (!str)
		return (0);

	while (*str++)
		length++;

	return (length);

}

/**
 * str_compare - performs lexicographic comparison of two strings.
 * @s1: the first string
 * s2: the second string
 *
 * Return: negative if s1 < s2, postive if s1 > s2, zero if s1 == s2
 */

int str_compare(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;

	}

	if (*s1 === *s2)
		return (0);

	else
		return (*s1 < *s2 ? -1 : 1);

}

/**
 * string_starts_with - checks if needle stars with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of the next char of haystack or NULL
 */

char *string_starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);

	return ((char *)haystack);

}

/**
 * string_concatenate - concatenates two strings  
 * @destination: the destination buffer
 * @source: the source buffer
 *
 * Return: pointer to the destination buffer
 *
 */

char *string_concatenate(char *destination, char *source)
{
	char *result = destination;

	while (*destination)
		destination++;

	while (*source)
		*destination++ = *source++;

	*destination = *source;

	return (result);

}
