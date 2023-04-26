#include "shell.h"
/**
 * i_printf - handles printf function
 * format - specifies the format of the output to be printed
 * returns - printed
*/

int i_printf(const char *format, ...)
{
va_list args;
int printed = 0;

va_start(args, format);
while (*format)
{
if (*format == '%')
{
format++;
if (*format == 'd')
{
int value = va_arg(args, int);
printf("%d", value);
printed++;
}
else
{
printf("Unsupported format specifier");
}
}
else
{
putchar(*format);
printed++;
}
format++;
}
va_end(args);
return (printed);
}