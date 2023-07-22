#include "main.h"

void printf_clean(va_list args, buffer_t *output);
int exec_printf(const char *format, va_list args, buffer_t *output);
int _printf(const char *format, ...);

/**
 * printf_clean - Executes cleaning printf operations for the _printf function.
 * @args: A list of arguments passed to the _printf function using va_list
 * @output: A structure named buffer_t.
 */
void printf_clean(va_list args, buffer_t *output)
{
	va_end(args);
	write(1, output->start, output->len);
	buff_free(output);
}

/**
 * exec_printf - Scans or parses the format string of the _printf function.
 * @format: string of characters to be prt, which may include formatting.
 * @output: structure buffer_t includes a buffer as one of its elements.
 * @args: A list of arguments provided using va_list.
 * Return: The count of characters that have been stored for output.
 */
int exec_printf(const char *format, va_list args, buffer_t *output)
{
	int i, wid, prec, rtn = 0;
	char tpr;
	unsigned char flags, lenght;
	unsigned int (*f)(va_list, buffer_t *,
			unsigned char, int, int, unsigned char);

	for (i = 0; *(format + i); i++)
	{
		lenght = 0;
		if (*(format + i) == '%')
		{
			tpr = 0;
			flags = f_handle(format + i + 1, &tpr);
			wid = wid_handle(args, format + i + tpr + 1, &tpr);
			prec = pres_handle(args, format + i + tpr + 1,
					&tpr);
			lenght = len_handle(format + i + tpr + 1, &tpr);

			f = specifiers_handle(format + i + tpr + 1);
			if (f != NULL)
			{
				i += tpr + 1;
				rtn += f(args, output, flags, wid, prec, lenght);
				continue;
			}
			else if (*(format + i + tpr + 1) == '\0')
			{
				rtn = -1;
				break;
			}
		}
		rtn += _memcpy(output, (format + i), 1);
		i += (lenght != 0) ? 1 : 0;
	}
	printf_clean(args, output);
	return (rtn);
}

/**
 * _printf - Formats and prints a string.
 * @format: Formatted string with possible directives.
 * Return: Character count after printing.
 */
int _printf(const char *format, ...)
{
	buffer_t *output;
	va_list args;
	int rtn;

	if (format == NULL)
		return (-1);
	output = init_buffer();
	if (output == NULL)
	{
		return (-1);
	}
	va_start(args, format);
	rtn = exec_printf(format, args, output);

	return (rtn);
}
