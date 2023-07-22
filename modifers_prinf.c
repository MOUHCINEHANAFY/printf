#include "main.h"

unsigned int wd_print(buffer_t *output, unsigned int printed,
		unsigned char flags, int wid);
unsigned int str_wid_print(buffer_t *output,
		unsigned char flags, int wid, int prec, int size);
unsigned int neg_wid_print(buffer_t *output, unsigned int printed,
		unsigned char flags, int wid);

/**
 * wd_print - Appends leading spaces to a buffer for a width modifier.
 * @output: A buffer_t struct with a character array.
 * @printed: The current count of characters already printed to output
 *           for a given number specifier.
 * @flags: Modifiers for flags.
 * @wid: Width specifier.
 * Return: The total number of bytes stored in the buffer.
 */
unsigned int wd_print(buffer_t *output, unsigned int printed,
		unsigned char flags, int wid)
{
	unsigned int rtn = 0;
	char width = ' ';

	if (F_MINUS == 0)
	{
		for (wid -= printed; wid > 0;)
			rtn += _memcpy(output, &width, 1);
	}

	return (rtn);
}

/**
 * str_wid_print - Appends leading spaces to a buffer for a width modifier.
 * @output: A buffer_t struct with a character array.
 * @flags: Modifiers for flags.
 * @wid: Width specifier.
 * @prec: Precision specifier.
 * @size: The size of the string.
 * Return: The total number of bytes stored in the buffer.
 */

unsigned int str_wid_print(buffer_t *output,
		unsigned char flags, int wid, int prec, int size)
{
	unsigned int rtn = 0;
	char width = ' ';

	if (F_MINUS == 0)
	{
		wid -= (prec == -1) ? size : prec;
		for (; wid > 0; wid--)
			rtn += _memcpy(output, &width, 1);
	}

	return (rtn);
}

/**
 * neg_wid_print - Appends trailing spaces to a buffer for a '-' flag.
 * @output: A buffer_t struct with a character array.
 * @printed: The current count of bytes already stored to output
 *           for a given specifier.
 * @flags: Modifiers for flags.
 * @wid: Width specifier.
 *
 * Return: The total number of bytes stored in the buffer.
 */
unsigned int neg_wid_print(buffer_t *output, unsigned int printed,
		unsigned char flags, int wid)
{
	unsigned int rtn = 0;
	char width = ' ';

	if (F_MINUS == 1)
	{
		for (wid -= printed; wid > 0; wid--)
			rtn += _memcpy(output, &width, 1);
	}

	return (rtn);
}

