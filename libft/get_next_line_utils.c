/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdogadin <mdogadin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 10:42:26 by mdogadin          #+#    #+#             */
/*   Updated: 2024/01/24 11:42:44 by mdogadin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_next_line(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr_next_line(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen_next_line(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

char	*ft_strjoin_next_line(char *s1, char *s2)
{
	char	*string;
	size_t	i;
	size_t	j;

	i = -1;
	j = 0;
	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	if (s1 == 0 || s2 == 0)
		return (NULL);
	string = (char *)malloc(sizeof(char)
			* (ft_strlen_next_line(s1) + ft_strlen_next_line(s2) + 1));
	if (!string)
		return (NULL);
	while (s1[++i] != '\0')
		string[i] = s1[i];
	while (s2[j] != '\0')
		string[i++] = s2[j++];
	string[i] = '\0';
	free(s1);
	return (string);
}

char	*ft_strdup_next_line(char *str)
{
	char		*res;
	size_t		length;
	size_t		i;

	i = 0;
	length = ft_strlen_next_line(str);
	res = (char *) malloc (sizeof(char) * length + 1);
	if (res == NULL)
		return (NULL);
	while (i < length)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_remove_next_line(char *s1)
{
	char	*res;
	size_t	i;

	i = 0;
	if (!s1)
		return (NULL);
	while (s1[i] && s1[i] != '\n')
		i++;
	if (s1[i] == '\0')
	{
		free(s1);
		return (NULL);
	}
	i++;
	res = ft_strdup_next_line(&s1[i]);
	free(s1);
	return (res);
}
