/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdogadin <mdogadin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:07:22 by mdogadin          #+#    #+#             */
/*   Updated: 2023/10/17 14:29:32 by mdogadin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*str;

	str = (char *)s;
	i = ft_strlen (s);
	if (c == '\0')
		return (str + i);
	while (i != 0)
	{
		if (str[i] == (char)c)
			return (str + i);
		i--;
	}
	if (s[0] == (char)c)
		return (str);
	return (0);
}
/*
#include <stdio.h>
#include <string.h>

size_t		ft_strlen(const char *s)
{
	size_t		i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int main() {
    const char *str = "Hello, World!";
    char searchChar = 'o';

 
    char *result = strrchr(str, searchChar);
    char *result2 = ft_strrchr(str, searchChar);

    if (result != NULL) {
        printf("Symbol '%c' in position %ld\n", searchChar, result - str);
        printf("Symbol '%c' in position %ld\n", searchChar, result2 - str);
    } else {
        printf("Symbol '%c' not in string\n", searchChar);
    }

    return 0;
}
*/
