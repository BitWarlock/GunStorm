/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 04:07:15 by mrezki            #+#    #+#             */
/*   Updated: 2023/12/22 11:39:42 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (!new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	tmp = ft_lstlast(*lst);
	tmp->next = new;
}
//
// void	print_list(t_list *lst)
// {
// 	t_list	*tmp;
//
// 	tmp = lst;
// 	while (tmp)
// 	{
// 		printf("%d\n", *(int *)tmp->content);
// 		tmp = tmp->next;
// 	}
// }
//
// void	del(void *data)
// {
// 	ft_bzero(data, 4);
// }
//
// void	f(void *data)
// {
// 	*(int *)data += 2;
// }
//
// void	*fi(void *data)
// {
// 	int *n = (int *)data;
// 	(*n)++;
// 	return (n);
// }
//
// int main(void)
// {
// 	int	i = 5;
// 	int	j = 10;
// 	int	k = 15;
// 	int	d = 20;
//
//
// 	t_list	*head = ft_lstnew(&j);
// 	ft_lstadd_front(&head, ft_lstnew(&i));
// 	ft_lstadd_back(&head, ft_lstnew(&k));
// 	ft_lstadd_back(&head, ft_lstnew(&d));
//
//
// 	print_list(head);
// 	t_list	*new = ft_lstmap(head, fi, del);
// 	printf("New list\n\n");
// 	
// 	// ft_lstclear(&new, del);
// 	
// 	print_list(new);
// 	printf("Size: %d\n\n", ft_lstsize(head));
// 	t_list	*last = ft_lstlast(head);
// 	printf("Last: %d\n\n", *(int*)last->content);
//
//
// 	ft_lstdelone(last, del);
// 	printf("After Del one: \n\n");
// 	print_list(head);
//
//
// 	printf("Iter\n");
// 	ft_lstiter(head, f);
// 	print_list(head);
//
// 	return EXIT_SUCCESS;
// }
