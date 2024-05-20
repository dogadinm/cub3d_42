/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdogadin <mdogadin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 12:22:43 by mdogadin          #+#    #+#             */
/*   Updated: 2023/12/19 14:54:32 by mdogadin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	len_s1;
	char	*str;

	str = 0;
	if (s1 != 0 && set != 0)
	{
		i = 0;
		len_s1 = ft_strlen(s1);
		while (s1[i] && ft_strchr(set, s1[i]))
			i++;
		while (s1[len_s1 - 1] && ft_strchr(set, s1[len_s1 - 1]) && len_s1 > i)
			len_s1--;
		str = (char *)malloc(sizeof(char) * (len_s1 - i + 1));
		if (str)
			ft_strlcpy(str, &s1[i], len_s1 - i + 1);
	}
	return (str);
}
/*
int main() {
    const char *original_str = "   Hello, World!   ";
    const char *set = " ";

    char *trimmed_str = ft_strtrim(original_str, set);

    if (trimmed_str) {
        printf("Original string: \"%s\"\n", original_str);
        printf("Trimmed string: \"%s\"\n", trimmed_str);
        free(trimmed_str);
    } else {
        printf("Memory allocation failed.\n");
    }

    return (0);
}
*/
