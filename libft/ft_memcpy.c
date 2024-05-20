/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdogadin <mdogadin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:01:17 by mdogadin          #+#    #+#             */
/*   Updated: 2023/10/18 14:21:28 by mdogadin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*tmpdst;
	unsigned char	*tmpsrc;

	tmpdst = (unsigned char *)dest;
	tmpsrc = (unsigned char *)src;
	while (n > 0)
	{
		*tmpdst = *tmpsrc;
		tmpdst++;
		tmpsrc++;
		n--;
	}
	return (dest);
}
/*
#include <stdio.h>
int main() {
    char src[] = "Hello, World!";
    char dest[20];

    ft_memcpy(dest, src, 15);
    
    printf("Copy: %s\n", dest);
    
    return 0;
}
*/