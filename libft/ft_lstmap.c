/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdogadin <mdogadin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 11:10:41 by mdogadin          #+#    #+#             */
/*   Updated: 2023/10/25 12:10:34 by mdogadin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_elem;

	new_lst = NULL;
	while (lst)
	{
		new_elem = ft_lstnew(f(lst->content));
		if (!new_elem)
		{
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, new_elem);
		lst = lst->next;
	}
	return (new_lst);
}
/*
void *double_value(void *value)
{
    int *num = (int *)value;
    int *doubled = (int *)malloc(sizeof(int));
    if (!doubled)
        return (NULL);
    *doubled = (*num) * 2;
    return (void *)doubled;
}

void free_value(void *value)
{
    free(value);
}

int main()
{
    t_list *lst = NULL;
    int values[] = {1, 2, 3, 4, 5};

    for (int i = 0; i < 5; i++)
    {
        ft_lstadd_back(&lst, ft_lstnew(&values[i]));
    }

    t_list *doubled_lst = ft_lstmap(lst, double_value, free_value);

    printf("Original List: ");
    t_list *current = lst;
    while (current)
    {
        printf("%d ", *((int *)(current->content)));
        current = current->next;
    }
    printf("\n");

    printf("Doubled List: ");
    current = doubled_lst;
    while (current)
    {
        printf("%d ", *((int *)(current->content)));
        current = current->next;
    }
    printf("\n");

    ft_lstclear(&lst, free_value);
    ft_lstclear(&doubled_lst, free_value);

    return 0;
}
*/
