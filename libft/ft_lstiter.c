/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdogadin <mdogadin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 12:20:27 by mdogadin          #+#    #+#             */
/*   Updated: 2023/10/25 12:27:58 by mdogadin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void*))
{
	if (!f)
		return ;
	while (lst)
	{
		(*f)(lst->content);
		lst = lst->next;
	}
}
/*
void print_string(void *str)
{
    printf("%s\n", (char *)str);
}

int main()
{
    t_list *list = NULL;

  
    ft_lstadd_back(&list, ft_lstnew(ft_strdup("Hello")));
    ft_lstadd_back(&list, ft_lstnew(ft_strdup("World")));
    ft_lstadd_back(&list, ft_lstnew(ft_strdup("from")));
    ft_lstadd_back(&list, ft_lstnew(ft_strdup("your")));
    ft_lstadd_back(&list, ft_lstnew(ft_strdup("library")));

    ft_lstiter(list, print_string);

    while (list)
    {
        t_list *temp = list;
        list = list->next;
        free(temp->content);
        free(temp);
    }
	// cc -Wall -Wextra -Werror ft_lstiter.c 
	// ft_lstadd_back.c ft_lstnew.c ft_strdup.c ft_strlen.c ft_lstlast.c
    return 0;
}
*/
