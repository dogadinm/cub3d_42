/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdogadin <mdogadin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:39:02 by mdogadin          #+#    #+#             */
/*   Updated: 2023/10/25 10:41:13 by mdogadin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	size_t	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

/*
int main() {
    t_list *list = NULL;


    ft_lstadd_front(&list, ft_lstnew("Node 3"));
    ft_lstadd_front(&list, ft_lstnew("Node 2"));
    ft_lstadd_front(&list, ft_lstnew("Node 1"));

    int size = ft_lstsize(list);

    printf("Size of the linked list: %d\n", size);

    while (list != NULL)
    {
        t_list *temp = list;
        list = list->next;
        free(temp);
    }
    return 0;
}
*/