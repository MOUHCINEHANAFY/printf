#include "main.h"


unsigned int ubase_conv(buffer_t *output,
		unsigned long int num, char *base,
		unsigned char flags, int wid, int prec);
unsigned int sbase_conv(buffer_t *output, long int num, char *base,
		unsigned char flags, int wid, int prec);

/**
 * ubase_conv - Converts an unsigned long to a specified base
 *                 stores the result in a buffer within a struct.
 * @output: buffer_t struct with a char array.
 * @num: Unsigned long integer for conversion.
 * @base: Pointer to a string with the target conversion base.
 * @flags: Modifiers for flags.
 * @wid: Width specifier.
 * @prec: Precision specifier.
 * Return: Byte count stored in the buffer.
 */
unsigned int ubase_conv(buffer_t *output, unsigned long int num, char *base,
		unsigned char flags, int wid, int prec)
{
	unsigned int taille, rtn = 1;
	char s_dig, padding = '0', *lead = "0x";

	for (taille = 0; *(base + taille);)
		taille++;

	if (num >= taille)
		rtn += ubase_conv(output, num / taille, base,
				flags, wid - 1, prec - 1);

	else
	{
		if (((flags >> 5) & 1) == 1)
		{
			wid -= 2;
			prec -= 2;
		}
		for (; prec > 1; prec--, wid--)
			rtn += _memcpy(output, &padding, 1);

		if (F_MINUS == 0)
		{
			padding = (F_ZR == 1) ? '0' : ' ';
			for (; wid > 1; wid--)
				rtn += _memcpy(output, &padding, 1);
		}
		if (((flags >> 5) & 1) == 1)
			rtn += _memcpy(output, lead, 2);
	}

	s_dig = base[(num % taille)];
	_memcpy(output, &s_dig, 1);

	return (rtn);
}

/**
 * sbase_conv - Converts a signed long to a specified base and
 *                 stores the result in a buffer within a struct.
 * @output: buffer_t struct with a char array.
 * @num: Signed long integer for conversion.
 * @base: Pointer to a string with the target conversion base.
 * @flags: Modifiers for flags.
 * @wid: Width specifier.
 * @prec: Precision specifier.
 * Return: Byte count stored in the buffer.
 */
unsigned int sbase_conv(buffer_t *output, long int num, char *base,
		unsigned char flags, int wid, int prec)
{
	int taille;
	char s_dig, padding = '0';
	unsigned int rtn = 1;

	for (taille = 0; *(base + taille);)
		taille++;

	if (num >= taille || num <= -taille)
		rtn += sbase_conv(output, num / taille, base,
				flags, wid - 1, prec - 1);

	else
	{
		for (; prec > 1; prec--, wid--)
			rtn += _memcpy(output, &padding, 1);

		if (F_MINUS == 0)
		{
			padding = (F_ZR == 1) ? '0' : ' ';
			for (; wid > 1; wid--)
				rtn += _memcpy(output, &padding, 1);
		}
	}

	s_dig = base[(num < 0 ? -1 : 1) * (num % taille)];
	_memcpy(output, &s_dig, 1);

	return (rtn);
}
