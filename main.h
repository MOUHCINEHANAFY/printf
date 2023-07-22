#ifndef MAIN_H
#define MAIN_H

#include <limits.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

#define PLS 1
#define SPC 2
#define DIAZ 4
#define ZR 8
#define MINUS 16
#define F_PLS (flags & 1)
#define F_SPC ((flags >> 1) & 1)
#define F_DIAZ ((flags >> 2) & 1)
#define F_ZR ((flags >> 3) & 1)
#define F_MINUS ((flags >> 4) & 1)
#define LONG 2
#define SHORT 1

/**
 * struct buffer_s - struct type for managing a char.
 * @buffer: A pointer to a character array.
 * @start: A pointer to the beginning of the buffer.
 * @len: The length of the string stored in the buffer.
 */
typedef struct buffer_s
{
	char *buffer;
	char *start;
	unsigned int len;
} buffer_t;

/**
 * struct converter_s - A custom struct type for handling conversion functions.
 * @specifier: A character representing a conversion specifier.
 * @func: A pointer to the conversion function associated with the specifier.
 */

typedef struct converter_s
{
	unsigned char specifier;
	unsigned int (*func)(va_list, buffer_t *,
			unsigned char, int, int, unsigned char);
} converter_t;

/**
 * struct flag_s - A new type defining a flags struct.
 * @flag: A character representing a flag.
 * @value: The integer value of the flag.
 */
typedef struct flag_s
{
	unsigned char flag;
	unsigned char value;
} flag_t;

int _printf(const char *format, ...);

/* Conversion Functions used in printf*/
unsigned int conv_c(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int conv_s(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int conv_di(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int conv_pr(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int conv_X(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int conv_S(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int conv_p(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int conv_r(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int conv_R(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int conv_b(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int conv_u(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int conv_o(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int conv_x(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);


/* Used Modifiers in printf function */
unsigned int wd_print(buffer_t *output, unsigned int printed,
		unsigned char flags, int wid);
unsigned int str_wid_print(buffer_t *output,
		unsigned char flags, int wid, int prec, int size);
unsigned int neg_wid_print(buffer_t *output, unsigned int printed,
		unsigned char flags, int wid);

/* Used Handlers in Printf function */
int wid_handle(va_list args, const char *modifier, char *index);
int pres_handle(va_list args, const char *modifier, char *index);
unsigned char len_handle(const char *modifier, char *index);
unsigned char f_handle(const char *flags, char *index);
unsigned int (*specifiers_handle(const char *specifier))(va_list, buffer_t *,
		unsigned char, int, int, unsigned char);

/* Used Helper Functions in printf function */
buffer_t *init_buffer(void);
void buff_free(buffer_t *output);
unsigned int _memcpy(buffer_t *output, const char *src, unsigned int n);
unsigned int sbase_conv(buffer_t *output, long int num, char *base,
		unsigned char flags, int wid, int prec);
unsigned int ubase_conv(buffer_t *output, unsigned long int num, char *base,
		unsigned char flags, int wid, int prec);

#endif /* MAIN_H */

