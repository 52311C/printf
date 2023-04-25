#include "main.h"

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - Producs ooutput according to a format
 * @format: character string
 * Return: Number of characters printed
 */

int _printf(const char *format, ...)
{
	int i;
	int printed = 0;
	int printed_chars = 0;
	int flags, width, precision, size;
	int buff_ind = 0;
	va_list list;
	char buffer[BUFFER];

	if (format == NULL)
	{
		return (-1);
	}
	va_start(list, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[buff_ind++] = format[i];
			if (buff_ind == BUFFER)
			{
				print_buffer(buffer, &buff_ind);
				printed_chars++;
			}
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			flags = get_flags(format, &i);
			width = get_width(format, &i, list);
			precision = get_precision(format, &i, list);
			size = get_size(format, &i);
			++i;
			printed = handle_print(format, &i, list, buffer,
					flags, width, precision, size);
			if (printed == -1)
			{
				return (-1);
				printed_chars += printed;
			}
		}
	}
	print_buffer(buffer, &buff_ind);
	va_end(list);
	return (printed_chars);
}

/**
 * print_buffer - Prints buffer content if it exists
 * @buffer: Array of characters
 * @buff_ind: index at which to add next character and reprecents length
 */

void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
	{
		write(1, &buffer[0], *buff_ind);
	}
	*buff_ind = 0;
}
