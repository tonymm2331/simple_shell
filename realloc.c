#include "shell.h"

/**
 * _memset - fills memory with a constant byte
 * @s: the pointer to the memory area
 * @b: the  byte to fill *s with
 * @n: the amount of bytes to be filled
 * Return: a pointer to the memory area s
 */

char *_memset(char *s, char b, unsigned int n)
{

	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;

	return s;

}

/**
 * freeStringArray - frees an array of strings
 * @arr: array of strings
 */

void freeStringArray(char **arr)
{
	char **temp = arr;

	if (!arr)
		return;

	while (*arr)
		free(*arr++);

	free(temp);

}

/**
 * _realloc - reallocates a block of memory.
 * @ptr: pointer to the previous malloc'ated block
 * @old_size: byte size of the previous block
 * @new_size: byte size of the new block
 * Return: pointer to the old block if realloc fails, else a pointer to the new block
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char p;

	if (!ptr)
		return malloc(new_size);

	if (!new_size)
		return (free(ptr), NULL);

	if (new_size == old_size)
		return ptr;


	p = malloc(new_size);
	if (!p)
		return NULL;

	old_size = old_size < new_size ? old_size : new_size;

	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return p;

}
