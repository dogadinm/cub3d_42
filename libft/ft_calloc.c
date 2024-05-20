/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdogadin <mdogadin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:27:52 by mdogadin          #+#    #+#             */
/*   Updated: 2023/10/30 15:59:52 by mdogadin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total_size;
	size_t	i;
	void	*ptr;

	total_size = count * size;
	if (count && total_size / count != size)
		return (NULL);
	ptr = malloc(total_size);
	i = 0;
	if (ptr == NULL)
		return (NULL);
	else
	{
		while (total_size-- > 0)
		{
			((char *)ptr)[i++] = 0;
		}
		return (ptr);
	}
}
/*
int main() {
    int *arr;
    size_t num_elements = 4;
    

    arr = (int *)calloc(num_elements, sizeof(int));
    
    if (arr == NULL) {
        printf("Flase.\n");
        return 1;
    }

    for (size_t i = 0; i < num_elements; i++) {
        printf("arr[%zu] = %d\n", i, arr[i]);
    }

    free(arr);

    return 0;
}
*/
