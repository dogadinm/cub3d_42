/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdogadin <mdogadin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:41:36 by mdogadin          #+#    #+#             */
/*   Updated: 2023/10/25 10:42:56 by mdogadin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}
/*
int main() {
    t_list *list = NULL;


    ft_lstadd_front(&list, ft_lstnew("Node 3"));
    ft_lstadd_front(&list, ft_lstnew("Node 2"));
    ft_lstadd_front(&list, ft_lstnew("Node 1"));

    t_list *last = ft_lstlast(list);
    
    printf("last elt: %s\n", (char *)last->content);

    while (list != NULL)
    {
        t_list *temp = list;
        list = list->next;
        free(temp);
    }
    return 0;
}
*/
