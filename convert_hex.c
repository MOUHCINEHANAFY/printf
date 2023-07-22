#include "main.h"

unsigned int conv_X(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int conv_x(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);

/**
 * conv_X - Converts an unsigned int argument to hexadecimal using ABCDEF
 *             and stores it in a buffer within a struct.
 * @args: A va_list referring to the argument to be converted.
 * @flags: Modifiers for flags.
 * @wid: Width specifier.
 * @prec: Precision specifier.
 * @len: Length specifier.
 * @output: A buffer_t struct with a character array.
 *
 * Return: The count of bytes stored in the buffer.
 */

unsigned int conv_X(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	unsigned long int num;
	unsigned int rtn = 0;
	char *lead = "0X";

	if (len == LONG)
		num = va_arg(args, unsigned long);
	else
		num = va_arg(args, unsigned int);
	if (len == SHORT)
		num = (unsigned short)num;

	if (F_DIAZ == 1 && num != 0)
		rtn += _memcpy(output, lead, 2);

	if (!(num == 0 && prec == 0))
		rtn += ubase_conv(output, num, "0123456789ABCDEF",
				flags, wid, prec);

	rtn += neg_wid_print(output, rtn, flags, wid);

	return (rtn);
}

/**
 * conv_x - Converts an unsigned int argument to hexadecimal using abcdef
 *             and stores it in a buffer within a struct.
 * @args: A va_list referring to the argument to be converted.
 * @flags: Modifiers for flags.
 * @wid: Width specifier.
 * @prec: Precision specifier.
 * @len: Length specifier.
 * @output: A buffer_t struct with a character array.
 *
 * Return: The count of bytes stored in the buffer.
 */

unsigned int conv_x(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	unsigned long int num;
	unsigned int rtn = 0;
	char *lead = "0x";

	if (len == LONG)
		num = va_arg(args, unsigned long int);
	else
		num = va_arg(args, unsigned int);
	if (len == SHORT)
		num = (unsigned short)num;

	if (F_DIAZ == 1 && num != 0)
		rtn += _memcpy(output, lead, 2);

	if (!(num == 0 && prec == 0))
		rtn += ubase_conv(output, num, "0123456789abcdef",
				flags, wid, prec);

	rtn += neg_wid_print(output, rtn, flags, wid);

	return (rtn);
}
