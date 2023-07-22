#include "main.h"

unsigned int conv_di(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int conv_b(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int conv_u(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int conv_o(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);

/**
 * conv_di - Converts an argument to a signed int and
 *              stores it in a buffer within a struct.
 * @args: A va_list referring to the argument to be converted.
 * @flags: Modifiers for flags.
 * @wid: Width specifier.
 * @prec: Precision specifier.
 * @len: Length specifier.
 * @output: A buffer_t struct with a character array.
 *
 * Return: The count of bytes stored in the buffer.
 */

unsigned int conv_di(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	long int d, copy;
	unsigned int rtn = 0, count = 0;
	char pad, space = ' ', neg = '-', plus = '+';

	if (len == LONG)
		d = va_arg(args, long int);
	else
		d = va_arg(args, int);
	if (len == SHORT)
		d = (short)d;

	if (F_SPC == 1 && d >= 0)
		rtn += _memcpy(output, &space, 1);

	if (prec <= 0 && F_MINUS == 0)
	{
		if (d == LONG_MIN)
			count += 19;
		else
		{
			for (copy = (d < 0) ? -d : d; copy > 0; copy /= 10)
				count++;
		}
		count += (d == 0) ? 1 : 0;
		count += (d < 0) ? 1 : 0;
		count += (F_PLS == 1 && d >= 0) ? 1 : 0;
		count += (F_SPC == 1 && d >= 0) ? 1 : 0;
		if (F_ZR == 1 && F_PLS == 1 && d >= 0)
			rtn += _memcpy(output, &plus, 1);

		if (F_ZR == 1 && d < 0)
			rtn += _memcpy(output, &neg, 1);

		pad = (F_ZR == 1) ? '0' : ' ';
		for (wid -= count; wid > 0; wid--)
			rtn += _memcpy(output, &pad, 1);
	}
	if (F_ZR == 0 && d < 0)
		rtn += _memcpy(output, &neg, 1);

	if (F_ZR == 0 && (F_PLS == 1 && d >= 0))
		rtn += _memcpy(output, &plus, 1);

	if (!(d == 0 && prec == 0))
		rtn += sbase_conv(output, d, "0123456789",
				flags, 0, prec);

	rtn += neg_wid_print(output, rtn, flags, wid);
	return (rtn);
}

/**
 * conv_b - Converts an unsigned int argument to binary
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

unsigned int conv_b(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	unsigned int num;

	num = va_arg(args, unsigned int);

	(void)len;

	return (ubase_conv(output, num, "01", flags, wid, prec));
}

/**
 * conv_o - Converts an unsigned int to octal and
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
unsigned int conv_o(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	unsigned long int num;
	unsigned int rtn = 0;
	char zero = '0';

	if (len == LONG)
		num = va_arg(args, unsigned long int);
	else
		num = va_arg(args, unsigned int);
	if (len == SHORT)
		num = (unsigned short)num;

	if (F_DIAZ == 1 && num != 0)
		rtn += _memcpy(output, &zero, 1);

	if (!(num == 0 && prec == 0))
		rtn += ubase_conv(output, num, "01234567",
				flags, wid, prec);

	rtn += neg_wid_print(output, rtn, flags, wid);
	return (rtn);
}

/**
 * conv_u - Converts an unsigned int argument to decimal and
 *               stores it in a buffer within a struct.
 * @args: A va_list referring to the argument to be converted.
 * @flags: Modifiers for flags.
 * @wid: Width specifier.
 * @prec: Precision specifier.
 * @len: Length specifier.
 * @output: A buffer_t struct with a character array.
 *
 * Return: The count of bytes stored in the buffer.
 */

unsigned int conv_u(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	unsigned long int num;
	unsigned int rtn = 0;

	if (len == LONG)
		num = va_arg(args, unsigned long int);
	else
		num = va_arg(args, unsigned int);
	if (len == SHORT)
		num = (unsigned short)num;

	if (!(num == 0 && prec == 0))
		rtn += ubase_conv(output, num, "0123456789",
				flags, wid, prec);

	rtn += neg_wid_print(output, rtn, flags, wid);
	return (rtn);
}
