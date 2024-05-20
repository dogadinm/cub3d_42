/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdogadin <mdogadin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:27:02 by mdogadin          #+#    #+#             */
/*   Updated: 2023/10/18 11:27:05 by mdogadin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	neg;
	int	res;

	i = 0;
	neg = 1;
	res = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (str[i] - '0') + (res * 10);
		i++;
	}
	return (res * neg);
}
/*
int main() {
    printf("%d\n", ft_atoi("   	\n\t\r\v\f---+--+14432ab567")); 
    // printf("%d\n", ft_atoi("   -456xyz"));  
    // printf("%d\n", ft_atoi("   --789def")); 
    // printf("%d\n", ft_atoi("   +987"));     

    return 0;
}
*/
