#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

int ft_putchar(char c)
{
    return (write (1, &c, 1));
}

void    ft_putstr(char *str, int *size)
{
    if (str == NULL)
        *size += write (1, "(null)", 6);
    while (*str)
    {
        *size += ft_putchar(*str);
        str++;
    }
}

void    ft_putnbr(int n, int *size)
{
    long long nb;

    nb = n;
    if (nb < 0)
    {
        *size += write (1, "-", 1);
        nb *= -1;
    }
    if (nb < 10)
        *size += ft_putchar(nb + 48);
    else
    {
        ft_putnbr(nb / 10, size);
        ft_putnbr(nb % 10, size);
    }
}

void    ft_puthex(unsigned int n, int *size)
{
    char *str = "0123456789abcdef";

    if (n < 16)
        *size += ft_putchar(str[n]);
    else
    {
        ft_puthex(n / 16, size);
        ft_puthex(n % 16, size);
    }
}

int ft_printf (const char *format, ...)
{
    va_list str;
    int size = 0;

    va_start(str, format);
    while (*format)
    {
        if (*format == '%')
        {
            if (*(format + 1) == 's')
                ft_putstr(va_arg(str, char*), &size);
            if (*(format + 1) == 'd')
                ft_putnbr(va_arg(str, int), &size);
            if (*(format + 1) == 'x')
                ft_puthex(va_arg(str, unsigned int), &size);
            format++;
        }
        else 
            size += write (1, format, 1);
        format++;
    }
    return size;
}
