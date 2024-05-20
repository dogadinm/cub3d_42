/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdogadin <mdogadin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 10:26:20 by mdogadin          #+#    #+#             */
/*   Updated: 2023/10/18 14:18:07 by mdogadin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			i;

	str = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (str[i] == (unsigned char)c)
			return (&str[i]);
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>

int main() {
    const char* str = "Hello, World!";
    char target = 'W';
    const char* result = (const char*)ft_memchr(str, target, strlen(str));

    if (result != NULL) {
        printf("Found '%c' at position %ld\n", target, result - str);
    } else {
        printf("'%c' not found in the string.\n", target);
    }

    return 0;
}
*/