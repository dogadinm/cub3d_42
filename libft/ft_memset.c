/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdogadin <mdogadin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:28:23 by mdogadin          #+#    #+#             */
/*   Updated: 2023/10/18 10:38:49 by mdogadin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)b;
	while (n > 0)
	{
		ptr[n - 1] = c;
		n--;
	}
	return (b);
}
/*
#include <stdio.h>
#include <stdlib.h>

int main(){
    unsigned char s[10] = "1234567";
    ft_memset(s,'1',4);

    printf("%s", s);
}
*/
