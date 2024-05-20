/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdogadin <mdogadin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:56:28 by mdogadin          #+#    #+#             */
/*   Updated: 2023/10/25 12:14:10 by mdogadin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	if (!del || !lst || !*lst)
		return ;
	while (lst && *lst)
	{
		tmp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = tmp;
	}
}
/*
void del_1(void *content) {
    free(content);
}

int main()
{
    t_list *list = NULL;

    ft_lstadd_back(&list, ft_lstnew(ft_strdup("World")));
    ft_lstadd_back(&list, ft_lstnew(ft_strdup("Hello")));

    // Print the list
    // ft_lstclear(&list, del);

    t_list *current = list;
    while (current)
    {
        printf("%s \n", (char *)current->content);
        current = current->next;
    }
    ft_lstclear(&list, del_1);

    return 0;
	// cc -Wall -Wextra -Werror ft_lstadd_back.c ft_lstnew.c 
	// ft_strdup.c ft_lstdelone.c ft_strlen.c ft_lstlast.c ft_lstclear.c
}
*/
