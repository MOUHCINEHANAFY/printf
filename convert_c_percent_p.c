#include "main.h"

unsigned int conv_c(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int conv_pr(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int conv_p(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);

/**
 * conv_c - Converts the provided argument to an unsigned char and
 *          stores it in a buffer within a struct.
 *
 * @args: A va_list pointing to the argument to be converted.
 * @flags: Modifiers for flags.
 * @wid: Width specifier.
 * @prec: Precision specifier.
 * @len: Length specifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored in the buffer.
 */

unsigned int conv_c(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	char c;
	unsigned int rtn = 0;

	(void)prec;
	(void)len;

	c = va_arg(args, int);

	rtn += wd_print(output, rtn, flags, wid);
	rtn += _memcpy(output, &c, 1);
	rtn += neg_wid_print(output, rtn, flags, wid);

	return (rtn);
}

/**
 * conv_pr - Appends a percent sign to a buffer
 *                   within a struct.
 * @args: A va_list referring to the argument to be processed.
 * @flags: Modifiers for flags.
 * @wid: Width specifier.
 * @prec: Precision specifier.
 * @len: Length specifier.
 * @output: A buffer_t struct with a character array.
 *
 * Return: The count of bytes stored in the buffer (always 1).
 */

unsigned int conv_pr(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	char percent = '%';
	unsigned int rtn = 0;

	(void)args;
	(void)prec;
	(void)len;

	rtn += wd_print(output, rtn, flags, wid);
	rtn += _memcpy(output, &percent, 1);
	rtn += neg_wid_print(output, rtn, flags, wid);

	return (rtn);
}

/**
 * conv_p - Converts the argument's address to hexadecimal and
 *             stores it in a buffer within a struct.
 * @args: A va_list referring to the argument to be converted.
 * @flags: Modifiers for flags.
 * @wid: Width specifier.
 * @prec: Precision specifier.
 * @len: Length specifier.
 * @output: A buffer_t struct with a character array.
 *
 * Return: The count of bytes stored in the buffer.
 */
unsigned int conv_p(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	char *null = "(nil)";
	unsigned long int address;
	unsigned int rtn = 0;

	(void)len;

	address = va_arg(args, unsigned long int);
	if (address == '\0')
		return (_memcpy(output, null, 5));

	flags |= 32;
	rtn += ubase_conv(output, address, "0123456789abcdef",
			flags, wid, prec);
	rtn += neg_wid_print(output, rtn, flags, wid);

	return (rtn);
}
