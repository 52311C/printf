#include "main.h"

/**
 * print_char - Princts a character
 * @types: Arguments list
 * @buffer: Buffer array
 * @flags: Calculates active flags
 * @width: Width
 * @precision: Precision specification
 * @size: Size specification
 * Return: Number od character printed
 */

int print_char(va_list types, char buffer[], int flags, int width,
		int precision, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char (c, buffer, flags, width, precision, size));
}

/**
 * print_string - Prints a string
 * @types: Arguments list
 * @buffer: Buffer array
 * @flags: Calculates active flags
 * @width: width
 * @precision: Precision specification
 * @size: Size specification
 * Return: Number of characters printed
 */

int print_string(va_list types, char buffer[], int flags, int width,
		int precision, int size)
{
	int length = 0, i;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = " ";
	}
	while (str[length] != '\0')
	{
		length++;
	}
	if (precision >= 0 && precision < length)
	{
		length = precision;
	}
	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (i = width - length; i > 0; i--)
				write(1, "", 1);
			return (width);
		}
		else
		{
			for (i = width - length; i > 0; i--)
				write(1, "", 1);
			write(1, &str[0], length);
			return (width);
		}
	}
	return (write(1, str, length));
}

/**
 * print_percent - Prints percent sign
 * @types: Arguments list
 * @buffer: Buffer array
 * @flags: Calculates active flags:
 * @width: width
 * @precision: Precision specification
 * @size: Size specification
 * Return: NUmber of characters printed
 */

int print_percent(va_list types, char buffer[], int flags, int width,
		int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/**
 * print_int - Print integers
 * @types: Arguments list
 * @buffer: buffer array:
 * @flags: Calculates active flags
 * @width: width
 * @precision: Precision specification
 * @size: size specification
 * Return: Number of characters printed
 */

int print_int(va_list types, char buffer[], int flags, int width,
		int precision, int size)
{
	int i = BUFFER - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = convert_size_number(n, size);
	if (n == 0)
	{
		buffer[i--] = '0';
	}
	buffer[BUFFER - 1] = '\0';
	num = (unsigned long int)n;
	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}
	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}
	i++;
	return (write_number(is_negative, i, buffer, flags, width, precision, size));
}

