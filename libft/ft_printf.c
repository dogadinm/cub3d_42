/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdogadin <mdogadin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:11:06 by mdogadin          #+#    #+#             */
/*   Updated: 2023/11/07 13:58:28 by mdogadin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_put_percent(void)
{
	write(1, "%", 1);
	return (1);
}

int	ft_putchr(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_format(va_list arg, const char format)
{
	int	len;

	len = 0;
	if (format == 'c')
		len += ft_putchr(va_arg(arg, int));
	else if (format == 's')
		len += ft_putstr(va_arg(arg, char *));
	else if (format == 'p')
		len += ft_putptr(va_arg(arg, unsigned long long));
	else if (format == 'd' || format == 'i')
		len += ft_putnbr(va_arg(arg, int));
	else if (format == 'u')
		len += ft_putnbr_unsigned(va_arg(arg, unsigned int));
	else if (format == 'x' || format == 'X')
		len += ft_putnbr_hexad(va_arg(arg, unsigned int), format);
	else if (format == '%')
		len += ft_put_percent();
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list	arg;
	int		i;
	int		len;

	i = 0;
	len = 0;
	va_start(arg, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			len += ft_format(arg, format[i + 1]);
			i++;
		}
		else
			len += ft_putchr(format[i]);
		i++;
	}
	va_end(arg);
	return (len);
}
/*
# include <stdio.h>
int main()
{
	char c = 'r';
	char s[] = "world";
	char *p;
	p = 0;
	int g = 0x1A;;
	int y = 6;
	int k = -9;
	int l = 0123;

	// int n = printf("hello %c Hello %s Hello %p, %c, 
	// %d, %d, %u, %x, %X, %%\n", c, s , 
	// p, *p, g, y, k, g, g);
	// int n2 = ft_printf("hello %c Hello %s Hello %p, 
	// %c, %d, %d, %u, %x, %X, %%\n", c, s, 
	// p, *p, g, y, k, g, g);
	
	
	int n = printf("%p\n",p);
	int n2 = ft_printf("%p\n",p);
	ft_printf("%d\n",n2);

	// cc libft/ft_putchar_fd.c libft/ft_putstr_fd.c libft/ft_itoa.c 
	libft/ft_strlen.c ft_printf.c ft_putstr.c ft_putptr.c ft_putnbr.c 
	ft_putnbr_unsigned.c ft_putnbr_hexad.c
}
*/
