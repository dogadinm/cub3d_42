/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdogadin <mdogadin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:34:32 by mdogadin          #+#    #+#             */
/*   Updated: 2023/10/25 10:38:35 by mdogadin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst)
	{
		if (*lst)
			new->next = *lst;
		*lst = new;
	}
}
/*
int main() {
    t_list *list = NULL;

    ft_lstadd_front(&list, ft_lstnew("Element 1"));
    ft_lstadd_front(&list, ft_lstnew("Element 2"));

    t_list *current = list;
    while (current != NULL) {
        printf("Element: %s\n", (char *)current->content);
        current = current->next;
    }

    while (list != NULL) {
        t_list *temp = list;
        list = list->next;
        free(temp);
    }
    return 0;
}
*/
