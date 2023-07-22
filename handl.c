#include "main.h"

unsigned char f_handle(const char *flag, char *index);
unsigned char len_handle(const char *modifier, char *index);
int wid_handle(va_list args, const char *modifier, char *index);
int pres_handle(va_list args, const char *modifier, char *index);
unsigned int (*specifiers_handle(const char *specifier))(va_list, buffer_t *,
		unsigned char, int, int, unsigned char);

/**
 * f_handle - Identifies and associates flags with their corresponding values.
 * @flag: A pointer to a potential string of flags.
 * @index: An index counter for the original format string.
 *
 * Return: If matching flag characters are found - the corresponding value.
 *         Otherwise - 0.
 */
unsigned char f_handle(const char *flag, char *index)
{
	int i, j;
	unsigned char rtn = 0;
	flag_t flags[] = {
		{'+', PLS},
		{' ', SPC},
		{'#', DIAZ},
		{'0', ZR},
		{'-', MINUS},
		{0, 0}
	};

	for (i = 0; flag[i]; i++)
	{
		for (j = 0; flags[j].flag != 0; j++)
		{
			if (flag[i] == flags[j].flag)
			{
				(*index)++;
				if (rtn == 0)
					rtn = flags[j].value;
				else
					rtn |= flags[j].value;
				break;
			}
		}
		if (flags[j].value == 0)
			break;
	}

	return (rtn);
}

/**
 * len_handle - Identifies and associates length modifiers
 *					with their corresponding value.
 * @modifier: A pointer to a potential length modifier.
 * @index: An index counter for the original format string.
 * Return: If a length modifier is found - its value.
 *         Otherwise - 0.
 */
unsigned char len_handle(const char *modifier, char *index)
{
	if (*modifier == 'h')
	{
		(*index)++;
		return (SHORT);
	}

	else if (*modifier == 'l')
	{
		(*index)++;
		return (LONG);
	}

	return (0);
}

/**
 * wid_handle - Identifies and associates a width
 * modifier with its corresponding value.
 * @args: A va_list of arguments.
 * @modifier: A pointer to a potential width modifier.
 * @index: An index counter for the original format string.
 *
 * Return: If a width modifier is found - its corresponding value.
 *         Otherwise - 0.
 */
int wid_handle(va_list args, const char *modifier, char *index)
{
	int value = 0;

	while ((*modifier >= '0' && *modifier <= '9') || (*modifier == '*'))
	{
		(*index)++;

		if (*modifier == '*')
		{
			value = va_arg(args, int);
			if (value <= 0)
				return (0);
			return (value);
		}

		value *= 10;
		value += (*modifier - '0');
		modifier++;
	}

	return (value);
}

/**
 * pres_handle - Identifies and associates a precision modifier with
 *                    its corresponding value.
 * @args: A va_list of arguments.
 * @modifier: A pointer to a potential precision modifier.
 * @index: Index counter for the original format string.
 *
 * Return: If a precision modifier is found and valid - itsvalue.
 *         If the precision modifier is empty, zero, or negative - 0.
 *         Otherwise - -1.
 */
int pres_handle(va_list args, const char *modifier, char *index)
{
	int value = 0;

	if (*modifier != '.')
		return (-1);

	modifier++;
	(*index)++;

	if ((*modifier <= '0' || *modifier > '9') &&
	     *modifier != '*')
	{
		if (*modifier == '0')
			(*index)++;
		return (0);
	}

	while ((*modifier >= '0' && *modifier <= '9') ||
	       (*modifier == '*'))
	{
		(*index)++;

		if (*modifier == '*')
		{
			value = va_arg(args, int);
			if (value <= 0)
				return (0);
			return (value);
		}

		value *= 10;
		value += (*modifier - '0');
		modifier++;
	}

	return (value);
}

/**
 * specifiers_handle - Associate a conversion specifier with conv function
 // * @specifier: The Pointer to conversion specifier.
 * Return: If a matching function is found pointer fo fct.
 *         Otherwise NULL.
 */
unsigned int (*specifiers_handle(const char *specifier))(va_list, buffer_t *,
		unsigned char, int, int, unsigned char)
{
	int i;
	converter_t converters[] = {
		{'c', conv_c},
		{'s', conv_s},
		{'d', conv_di},
		{'i', conv_di},
		{'%', conv_pr},
		{'b', conv_b},
		{'u', conv_u},
		{'o', conv_o},
		{'x', conv_x},
		{'X', conv_X},
		{'S', conv_S},
		{'p', conv_p},
		{'r', conv_r},
		{'R', conv_R},
		{0, NULL}
	};

	for (i = 0; converters[i].func; i++)
	{
		if (converters[i].specifier == *specifier)
			return (converters[i].func);
	}

	return (NULL);
}

