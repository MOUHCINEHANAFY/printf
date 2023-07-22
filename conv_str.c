#include "main.h"

unsigned int conv_s(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int conv_S(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int conv_r(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int conv_R(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);

/**
 * conv_s - Converts an argument to a string and
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
unsigned int conv_s(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	char *str, *null = "(null)";
	int size;
	unsigned int rtn = 0;

	(void)flags;
	(void)len;

	str = va_arg(args, char *);
	if (str == NULL)
		return (_memcpy(output, null, 6));

	for (size = 0; *(str + size);)
		size++;

	rtn += str_wid_print(output, flags, wid, prec, size);

	prec = (prec == -1) ? size : prec;
	while (*str != '\0' && prec > 0)
	{
		rtn += _memcpy(output, str, 1);
		prec--;
		str++;
	}

	rtn += neg_wid_print(output, rtn, flags, wid);

	return (rtn);
}

/**
 * conv_S - Converts an argument to a string and
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

unsigned int conv_S(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	char *str, *null = "(null)", *hex = "\\x", zero = '0';
	int size, index;
	unsigned int rtn = 0;

	(void)len;
	str = va_arg(args, char *);
	if (str == NULL)
		return (_memcpy(output, null, 6));

	for (size = 0; str[size];)
		size++;

	rtn += str_wid_print(output, flags, wid, prec, size);

	prec = (prec == -1) ? size : prec;
	for (index = 0; *(str + index) != '\0' && index < prec; index++)
	{
		if (*(str + index) < 32 || *(str + index) >= 127)
		{
			rtn += _memcpy(output, hex, 2);
			if (*(str + index) < 16)
				rtn += _memcpy(output, &zero, 1);
			rtn += ubase_conv(output, *(str + index),
					     "0123456789ABCDEF", flags, 0, 0);
			continue;
		}
		rtn += _memcpy(output, (str + index), 1);
	}

	rtn += neg_wid_print(output, rtn, flags, wid);

	return (rtn);
}

/**
 * conv_r - Reverses a string and stores it
 *             in a buffer within a struct.
 * @args: A va_list referring to the string to be reversed.
 * @flags: Modifiers for flags.
 * @wid: Width specifier.
 * @prec: Precision specifier.
 * @len: Length specifier.
 * @output: A buffer_t struct with a character array.
 *
 * Return: The count of bytes stored in the buffer.
 */

unsigned int conv_r(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	char *str, *null = "(null)";
	int size, end, i;
	unsigned int rtn = 0;

	(void)flags;
	(void)len;

	str = va_arg(args, char *);
	if (str == NULL)
		return (_memcpy(output, null, 6));

	for (size = 0; *(str + size);)
		size++;

	rtn += str_wid_print(output, flags, wid, prec, size);

	end = size - 1;
	prec = (prec == -1) ? size : prec;
	for (i = 0; end >= 0 && i < prec; i++)
	{
		rtn += _memcpy(output, (str + end), 1);
		end--;
	}

	rtn += neg_wid_print(output, rtn, flags, wid);

	return (rtn);
}

/**
 * conv_R - Converts a string to ROT13 and stores
 *             it in a buffer within a struct.
 * @args: A va_list referring to the string to be converted.
 * @flags: Modifiers for flags.
 * @wid: Width specifier.
 * @prec: Precision specifier.
 * @len: Length specifier.
 * @output: A buffer_t struct with a character array.
 *
 * Return: The count of bytes stored in the buffer.
 */
unsigned int conv_R(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	char *alpha = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char *rot13 = "nopqrstuvwxyzabcdefghijklmNOPQRSTUVWXYZABCDEFGHIJKLM";
	char *str, *null = "(null)";
	int i, j, size;
	unsigned int rtn = 0;

	(void)flags;
	(void)len;

	str = va_arg(args, char *);
	if (str == NULL)
		return (_memcpy(output, null, 6));

	for (size = 0; *(str + size);)
		size++;

	rtn += str_wid_print(output, flags, wid, prec, size);

	prec = (prec == -1) ? size : prec;
	for (i = 0; *(str + i) != '\0' && i < prec; i++)
	{
		for (j = 0; j < 52; j++)
		{
			if (*(str + i) == *(alpha + j))
			{
				rtn += _memcpy(output, (rot13 + j), 1);
				break;
			}
		}
		if (j == 52)
			rtn += _memcpy(output, (str + i), 1);
	}

	rtn += neg_wid_print(output, rtn, flags, wid);

	return (rtn);
}

