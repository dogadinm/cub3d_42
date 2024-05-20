/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdogadin <mdogadin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:50:12 by mdogadin          #+#    #+#             */
/*   Updated: 2023/11/01 11:11:58 by mdogadin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_number_length(unsigned	int num)
{
	int	len;

	len = 0;
	while (num != 0)
	{
		len++;
		num = num / 10;
	}
	return (len);
}

char	*ft_itoa_unsigned(unsigned int num)
{
	char	*string;
	int		len;

	len = ft_number_length(num);
	string = (char *)malloc(sizeof(char) * (len + 1));
	if (!string)
		return (0);
	string[len] = '\0';
	while (num != 0)
	{
		string[len - 1] = num % 10 + '0';
		num /= 10;
		len--;
	}
	return (string);
}

int	ft_putnbr_unsigned(unsigned int num)
{
	char	*n;
	int		len;

	len = 0;
	if (num == 0)
		len += write(1, "0", 1);
	else
	{
		n = ft_itoa_unsigned(num);
		len += ft_putstr(n);
		free(n);
	}
	return (len);
}
