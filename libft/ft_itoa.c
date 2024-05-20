/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdogadin <mdogadin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:03:50 by mdogadin          #+#    #+#             */
/*   Updated: 2023/10/19 14:52:05 by mdogadin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_number_length(int num)
{
	unsigned int	len;

	len = 0;
	if (num == 0)
		return (1);
	if (num < 0)
		len += 1;
	while (num != 0)
	{
		num /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	unsigned int	num;
	unsigned int	len;
	char			*string;

	len = ft_number_length(n);
	string = (char *)malloc(sizeof(char) * (len + 1));
	if (string == NULL)
		return (NULL);
	if (n < 0)
	{
		string[0] = '-';
		num = -n;
	}
	else
		num = n;
	if (num == 0)
		string[0] = '0';
	string[len] = '\0';
	while (num != 0)
	{
		string[len - 1] = (num % 10) + '0';
		num /= 10;
		len--;
	}
	return (string);
}
/*
int main()
{
    int num = -12345;
    char *str = ft_itoa(num);

    printf("Integer: %d\n", num);
    printf("String: %s\n", str);
    free(str);
    return 0;
}
*/
