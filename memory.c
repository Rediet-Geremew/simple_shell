#include "simple_shell.h"

/**
 * _reallocate - reallocates
 * @ptr: pointer
 * @size: number of elements
 *
 * Return: pointer to the new array
 */
char **_reallocate(char **ptr, size_t *size)
{
	char **n;
	size_t i;

	n = malloc(sizeof(char *) * ((*size) + 10));
	if (n == NULL)
	{
		free(ptr);
		return (NULL);
	}
	for (i = 0; i < (*size); i++)
	{
		n[i] = ptr[i];
	}
	*size += 10;
	free(ptr);
	return (n);
}
