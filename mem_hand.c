#include "main.h"

unsigned int _memcpy(buffer_t *output, const char *src, unsigned int n);
void buff_free(buffer_t *output);
buffer_t *init_buffer(void);

/**
 * _memcpy - Copies a specified number of bytes from the memory area src
 *           to the buffer stored in a buffer_t struct.
 * @output: A buffer_t struct containing the destination buffer.
 * @src: A pointer to the source memory area to be copied.
 * @n: The number of bytes to copy.
 *
 * Return: The total number of bytes copied.
 */

unsigned int _memcpy(buffer_t *output, const char *src, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
	{
		*(output->buffer) = *(src + i);
		(output->len)++;

		if (output->len == 1024)
		{
			write(1, output->start, output->len);
			output->buffer = output->start;
			output->len = 0;
		}

		else
			(output->buffer)++;
	}

	return (n);
}

/**
 * buff_free - Deallocates memory used by a buffer_t struct.
 * @output: The buffer_t struct to be released.
 */
void buff_free(buffer_t *output)
{
	free(output->start);
	free(output);
}

/**
 * init_buffer - Creates and initializes a buffer_t struct.
 *
 * Return: Pointer to the newly initialized buffer_t.
 */
buffer_t *init_buffer(void)
{
	buffer_t *output;

	output = malloc(sizeof(buffer_t));
	if (output == NULL)
		return (NULL);

	output->buffer = malloc(sizeof(char) * 1024);
	if (output->buffer == NULL)
	{
		free(output);
		return (NULL);
	}

	output->start = output->buffer;
	output->len = 0;

	return (output);
}

